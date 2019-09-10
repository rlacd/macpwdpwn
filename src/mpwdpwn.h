/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#ifndef __MPWDPWN_H
#define __MPWDPWN_H

// A structure defining a target for account unlock
typedef struct PTARGET {
    char volumeName[256];
    char volumePath[256];
    char userPlist[256];
} PTARGET;

#endif