/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#ifndef __PLIST_H
#define __PLIST_H

#define PLIST_DTYPE_STRING "string"
#define PLIST_DTYPE_DATAB64 "data"
#define PLIST_DTYPE_JSON "json"
#define PLIST_FORMAT_XML "xml1"
#define PLIST_FORMAT_BINARY "binary1"

int plist_convert(const char* path, const char* format);
int plist_replace_xml(const char* path, const char* k, const char* xmlData);
int plist_insert(const char* path, const char* k, const char* type, const char* data);

#endif