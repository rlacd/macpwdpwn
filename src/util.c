/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include "util.h"
#include <sys/stat.h>

int dir_exists(const char* path) {
    struct stat st;
    if(stat(path,&st) == 0 && S_ISDIR(st.st_mode))
        return 0;
    else return 1;
}