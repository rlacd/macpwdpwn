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

int main(int argc, char* argv[]) {
    fprintf(stdout, "%s", APP_LOGO);
    fprintf(stdout, "%s", "mpwdpwn version 1.0. Copyright (C) mr_chainman (techspider) 2019.\n\n");
    if(geteuid() != 0) {
        fprintf(stderr, "%s", "Error: Missing permissions, rerun as root.\n");
        return 1;
    }
    fprintf(stdout, "%s", "Scanning volumes...\n");
    struct dirent *dEntry;
    DIR *vDir = opendir("/Volumes");
    if(vDir == NULL) {
        fprintf(stderr, "%s", "Error: /Volumes directory does not exist, is this a Mac or is the file system corrupt?\n");
        return 1;
    }
    fprintf(stdout, "Please enter the name of a system volume from which you want to unlock an account from.\nAvailable Volumes are:\n");
    while((dEntry = readdir(vDir)) != NULL) {
        if(strncmp(dEntry->d_name, "..", strlen(dEntry->d_name)) == 0) continue;
        else if(strncmp(dEntry->d_name, ".", strlen(dEntry->d_name)) == 0) continue;
        else fprintf(stdout, "  %s\n", dEntry->d_name);
    }
    fprintf(stdout, "\n");
    closedir(vDir);
    PTARGET * target = malloc(sizeof(PTARGET));
    int validVolumeDetected = -1;
    while(validVolumeDetected != 0) {
        fprintf(stdout, "%s ", ">");
        fgets(target->volumeName, sizeof(target->volumeName), stdin);
        strtok(target->volumeName, "\n"); // Remove trailing new line
        if(string_empty(target->volumeName) == 0) {
            fprintf(stderr, "%s", "Error: Volume name cannot be empty!\n");
            continue;
        }
        char fullPath[256];
        strcpy(fullPath, "/Volumes/");
        strncat(fullPath, target->volumeName, 9 + strlen(target->volumeName));
        fprintf(stdout, "Selecting volume %s...\n", fullPath);
        strcpy(target->volumePath, fullPath);
        if(dir_exists(fullPath) != 0) {
            fprintf(stderr, "%s", "Error: Volume does not exist!\n");
            continue;
        }
        validVolumeDetected = 0;
    }
    char userDirPath[256];
    char dbPathInFS[256];
    strcpy(dbPathInFS, "/var/db/dslocal/nodes/Default/users");
    strcpy(userDirPath, target->volumePath);
    strncat(userDirPath, dbPathInFS, strlen(dbPathInFS) + strlen(userDirPath));
    fprintf(stdout, "Checking %s for user plists...\n", userDirPath);
    fprintf(stdout, "Enter the name of the user account you would like to unlock:\nAvailable Users:\n");
    struct dirent * pluEntry;
    DIR * pluDir = opendir(userDirPath);
    if(pluDir == NULL) {
        fprintf(stderr, "%s", "Error: User database is corrupt or this is not a valid volume.\n");
        return 1;
    }
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
    
    return 0;
}