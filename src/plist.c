/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

int plist_convert(const char* path, const char* format) {
    char command[256];
    sprintf(command, "plutil -convert %s \"%s\"", format, path);
    return system(command);
}

int plist_replace_xml(const char* path, const char* k, const char* xmlData) {
    char command[256];
    sprintf(command, "plutil -replace %s -xml \"%s\" \"%s\"", k, xmlData, path);
    return system(command);
}

int plist_insert(const char* path, const char* k, const char* type, const char* data) {
    char command[1536];
    sprintf(command, "plutil -insert %s -%s \"%s\" \"%s\"", k, type, data, path);
    return system(command);
}