/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#ifndef __UTIL_H
#define __UTIL_H

int dir_exists(const char* path);
int prompt_confirm(char defChar);
int fcopy_bin(const char* src, const char* dest);

#endif