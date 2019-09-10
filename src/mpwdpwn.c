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

int main(int argc, char* argv[]) {
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
    fprintf(stdout, "%s ", ">");
    char volumeName[256];
    fscanf(stdin, "%s", volumeName);
    
    return 0;
}