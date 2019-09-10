/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include "strutils.h"

int string_empty(const char* input) {
    for(int i=0; input[i]!='\0'; i++)
        if((input[i] != ' ') && (input[i] != '\n') && (input[i] != '\r') && (input[i] != '\0'))
            return -1;
    return 0;
}