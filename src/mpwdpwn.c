/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    fprintf(stdout, "%s", "mpwdpwn version 1.0. Copyright (C) mr_chainman (techspider) 2019.\n\n");
    if(geteuid() != 0) {
        fprintf(stderr, "%s", "Error: Missing permissions, rerun as root.\n");
        return 1;
    }
}