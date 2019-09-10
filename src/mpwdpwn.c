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
        if(dir_exists(fullPath) != 0) {
            fprintf(stderr, "%s", "Error: Volume does not exist!\n");
            continue;
        }
        validVolumeDetected = 0;
    }    
    
    return 0;
}