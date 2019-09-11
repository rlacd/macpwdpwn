/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#ifndef __UTIL_H
#define __UTIL_H

#define PLIST_FORMAT_XML "xml1"
#define PLIST_FORMAT_BINARY "binary1"

int dir_exists(const char* path);
int prompt_confirm(char defChar);
int fcopy_bin(const char* src, const char* dest);
int plist_convert(const char* path, const char* format);

#endif