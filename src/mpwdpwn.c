/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "util.h"
#include "mpwdpwn.h"
#include "strutils.h"
#include "res.h"
#include "plist.h"

int main(int argc, char* argv[]) { //TODO add command line arguments
    //Display copyrights and APP_LOGO

    fprintf(stdout, "\033[0;35m%s\033[0m", APP_LOGO);
    fprintf(stdout, "%s", "\033[1;36mmpwdpwn version 1.0. Copyright (C) mr_chainman (techspider) 2019.\033[0m\n\n");

    //Check if root access is available

    if(geteuid() != 0) {
        fprintf(stderr, "%s", "\033[0;31mError: Missing permissions, rerun as root.\033[0m\n");
        return 1;
    }

    //Look through /Volumes for volumes to use

    fprintf(stdout, "%s", "Scanning volumes...\n");
    struct dirent *dEntry;
    DIR *vDir = opendir("/Volumes");
    if(vDir == NULL) {
        fprintf(stderr, "%s", "\033[0;31mError: /Volumes directory does not exist, is this a Mac or is the file system corrupt?\033[0m\n");
        return 1;
    }

    //Prompt user for volume name
    fprintf(stdout, "\033[0;33mPlease enter the name of a system volume from which you want to unlock an account from.\033[0m\nAvailable Volumes are:\n");
    while((dEntry = readdir(vDir)) != NULL) {
        if(strncmp(dEntry->d_name, "..", strlen(dEntry->d_name)) == 0) continue;
        else if(strncmp(dEntry->d_name, ".", strlen(dEntry->d_name)) == 0) continue;
        else fprintf(stdout, "  %s\n", dEntry->d_name);
    }

    fprintf(stdout, "\n");
    closedir(vDir);
    PTARGET * target = malloc(sizeof(PTARGET));
    int validVolumeDetected = -1;
    while(validVolumeDetected != 0) { //Perform checks whether specified volume is valid
        fprintf(stdout, "%s ", ">");
        fgets(target->volumeName, sizeof(target->volumeName), stdin);
        strtok(target->volumeName, "\n"); // Remove trailing new line
        if(string_empty(target->volumeName) == 0) {
            fprintf(stderr, "%s", "\033[0;31mError: Volume name cannot be empty!\033[0m\n");
            continue;
        }
        char fullPath[256];
        strcpy(fullPath, "/Volumes/");
        strncat(fullPath, target->volumeName, 9 + strlen(target->volumeName));
        fprintf(stdout, "Selecting volume %s...\n", fullPath);
        strcpy(target->volumePath, fullPath);
        if(dir_exists(fullPath) != 0) {
            fprintf(stderr, "%s", "\033[0;31mError: Volume does not exist!\033[0m\n");
            continue;
        }
        validVolumeDetected = 0;
    }

    //Go though all user plists in database and prompt user for username

    char userDirPath[256];
    char dbPathInFS[256];
    strcpy(dbPathInFS, "/var/db/dslocal/nodes/Default/users");
    strcpy(userDirPath, target->volumePath);
    strncat(userDirPath, dbPathInFS, strlen(dbPathInFS) + strlen(userDirPath));
    fprintf(stdout, "Checking %s for user plists...\n", userDirPath);
    struct dirent * pluEntry;
    DIR * pluDir = opendir(userDirPath);

    if(pluDir == NULL) {
        fprintf(stderr, "%s", "\033[0;31mError: User database is corrupt, inaccessible, or this is not a valid volume.\033[0m\n");
        return 1;
    }

    fprintf(stdout, "\033[0;33mEnter the name of the user account you would like to unlock:\033[0m\nAvailable Users:\n");

    while((pluEntry = readdir(pluDir)) != NULL) {
        if(strncmp(pluEntry->d_name, "..", strlen(pluEntry->d_name)) == 0) continue;
        else if(strncmp(pluEntry->d_name, ".", strlen(pluEntry->d_name)) == 0) continue;
        else if(pluEntry->d_name[0] == '_') continue; //These are hidden users, do not list them.
        else {
            char username[128];
            strcpy(username, pluEntry->d_name);
            strtok(username, ".");
            fprintf(stdout, "  %s\n", username);
        }
    }

    fprintf(stdout, "\n");
    closedir(pluDir);

    // Prompt the user for a user name now

    int validUserSelected = -1;
    while(validUserSelected != 0) {
        fprintf(stdout, "%s ", ">");
        fgets(target->userName, sizeof(target->userName), stdin);
        strtok(target->userName, "\n"); // Remove trailing new line
        if(string_empty(target->userName) == 0) {
            fprintf(stderr, "%s", "\033[0;31mError: User name cannot be empty!\033[0m\n");
            continue;
        }
        char userPlistPath[256];
        strcpy(userPlistPath, userDirPath);
        strncat(userPlistPath, "/", 1);
        char userPlistFileName[128];
        strcpy(userPlistFileName, target->userName);
        strncat(userPlistFileName, ".plist", strlen(target->userName) + 6);
        strncat(userPlistPath, userPlistFileName, strlen(userPlistPath) + strlen(userPlistFileName));
        if(access(userPlistPath, F_OK) == -1) {
            fprintf(stderr, "\033[0;31mError: User \"%s\" does not exist!\033[0m\n", target->userName);
            continue;
        }
        fprintf(stdout, "Found plist %s\n", userPlistPath);
        strcpy(target->userPlist, userPlistPath);
        validUserSelected = 0;
    }

    // Ask user to confirm changes

    fprintf(stdout, "\n\033[0;33mPlease review the following to check if it is correct.\033[0m\n\033[0;31m>> WARNING: This is a potentially destructive action if not performed correctly! <<\033[0m\n[Summary]\n");
    fprintf(stdout, "  Target Volume: %s\n  Target User: %s\n\n", target->volumeName, target->userName);
    fprintf(stdout, "Are you sure you want to continue? [y/N]: ");
    if(prompt_confirm('N') == -1) {
        fprintf(stderr, "\033[0;31mUser abort operation, exiting...\033[0m\n");
        return 1;
    }

    //Backup user file just in case something goes wrong - (if at any point the program fails, it will restore from backup)

    fprintf(stdout, "\nBacking up user file...\n");
    char backupPath[256];
    strcpy(backupPath, target->volumePath);
    strncat(backupPath, "/var/mpwd_backup.plist", strlen(target->volumePath) + strlen(backupPath));
    if(fcopy_bin(target->userPlist, backupPath) != 0) {
        fprintf(stderr, "\033[0;31mError: Failed to create file \"%s\"\033[0m\n", backupPath);
        return 1;
    } else fprintf(stdout, "Created user plist backup at %s\n", backupPath);

    //Create temporary copy of user plist for editing

    char tempPlistPath[256];
    strcpy(tempPlistPath, target->volumePath);
    strncat(tempPlistPath, "/Temp.plist", strlen(target->volumePath) + strlen(tempPlistPath));
    if(fcopy_bin(target->userPlist, tempPlistPath) != 0) {
        fprintf(stderr, "\033[0;31mError: Failed to create file \"%s\"\033[0m\n", tempPlistPath);
        return 1;
    } else fprintf(stdout, "Created temporary plist for editing at %s\n", tempPlistPath);

    //Convert bplist to user readable XML

    fprintf(stdout, "Converting user plist into format \"%s\"...\n", PLIST_FORMAT_XML);
    if(plist_convert(tempPlistPath, PLIST_FORMAT_XML) != 0) {
        fprintf(stderr, "\033[0;31mError: Could not convert user plist into appropriate format.\033[0m\n");
        return 1;
    } else fprintf(stdout, "Conversion successful!\n");

    //Read the plist and insert the new ShadowHashData

    fprintf(stdout, "Modifying ShadowHashData...\n");
    if(plist_replace_xml(tempPlistPath, "ShadowHashData", "<array></array>") != 0) {
        fprintf(stderr, "\033[0;31mError: Could not replace ShadowHashData with empty array!\033[0m\n");
        return 1;
    }

    if(plist_insert(tempPlistPath, "ShadowHashData.0", PLIST_DTYPE_DATAB64, SHADOW_HASH_DATA_UNLOCK) != 0) {
        fprintf(stderr, "\033[0;31mError: Failed to update ShadowHashData with new password!\033[0m\n");
        return 1;
    }
    fprintf(stdout, "Successfully injected new password into ShadowHashData!\n");

    //ShadowHashData has been modified, now copy back the plist and let the user know their new password is 12345
    
    fprintf(stdout, "Reformatting plist to binary...\n");
    if(plist_convert(tempPlistPath, PLIST_FORMAT_BINARY) != 0) {
        fprintf(stderr, "\033[0;31mError: Could not convert user plist into appropriate format.\033[0m\n");
        return 1;
    } else fprintf(stdout, "Plist succesfully converted to binary!\n");

    fprintf(stdout, "Copying back user plist...\n");
    if(fcopy_bin(tempPlistPath, target->userPlist) != 0) {
        fprintf(stderr, "\033[0;31mError: Failed to create file \"%s\"\033[0m\n", tempPlistPath);
        return 1;
    } else fprintf(stdout, "Plist successfully copied back! A backup of the old plist is kept at VolumeRoot/var/mpwd_backup.plist\n");

    fprintf(stdout, "Deleting temporary file...\n");
    int status = remove(tempPlistPath);
    if(status != 0) {
        fprintf(stderr, "\033[0;31mError NON FATAL: Could not delete file \"%s\"! Could the file be in use?\033[0m\n", tempPlistPath);
    }

    fprintf(stdout, "\n\nThe account unlocking procedure has completed successfully!\nTo log in, reboot your Mac and enter password '12345' as password.\n\nNote: Please change your password as soon as possible to avoid glitches!");

    return 0;
}