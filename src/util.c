/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include "util.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int dir_exists(const char* path) {
    struct stat st;
    if(stat(path,&st) == 0 && S_ISDIR(st.st_mode))
        return 0;
    else return 1;
}

int prompt_confirm(char defChar) {
    char response;
    char input[2];
    do {
        fgets(input, sizeof(1), stdin);
        response = input[0];
        if(response == '\n') response = defChar;
        if((response == 'N') || (response == 'n')) return -1;
        else if((response == 'Y') || (response == 'y')) return 0;
        else {
            fprintf(stdout, "\033[0;31mError: Selected choice is not valid, try again.\033[0m\n");
            continue;
        }
    } while((response != 'Y') || (response != 'y'));
    return 0;
}