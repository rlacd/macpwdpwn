/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include "util.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define FCOPY_BIN_BUFSZ 2048

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

int fcopy_bin(const char* src, const char* dest) {
    char buff[FCOPY_BIN_BUFSZ];
    FILE *in, *out;
    size_t n;
    in = fopen(src, "rb");
    if(in == NULL) return -1;
    out = fopen(dest, "wb");
    if(out == NULL) return -1;
    while ((n=fread(buff,1,BUFSIZ,in)) != 0)
        fwrite(buff, 1, n, out);
    fclose(in);
    fclose(out);
    return 0;
}