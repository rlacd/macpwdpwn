/*
MPWDPWN (Mac Password Pwn) Account Unlocking Tool
For Mojave and above.

Copyright (C) techspider 2019. All rights reserved.
*/

#ifndef __CONSOLE_H
#define __CONSOLE_H

/*
Console ANSI Codes Definitions for styling
A = ANSI, CL = COLOR, FN = FUNCTION, BG = BACKGROUND, FG = FOREGROUND, CT = CONTROL
*/

//Foreground colors (Basic 8 color set)

#define ACL_FG_BLACK "\x1b[30m"
#define ACL_FG_RED "\x1b[31m"
#define ACL_FG_GREEN "\x1b[32m"
#define ACL_FG_YELLOW "\x1b[33m"
#define ACL_FG_BLUE "\x1b[34m"
#define ACL_FG_MAGENTA "\x1b[35m"
#define ACL_FG_CYAN "\x1b[36m"
#define ACL_FG_WHITE "\x1b[37m"

//Background colors (Also 8 colors)

#define ACL_BG_BLACK "\x1b[40m"
#define ACL_BG_RED "\x1b[41m"
#define ACL_BG_GREEN "\x1b[42m"
#define ACL_BG_YELLOW "\x1b[43m"
#define ACL_BG_BLUE "\x1b[44m"
#define ACL_BG_MAGENTA "\x1b[45m"
#define ACL_BG_CYAN "\x1b[46m"
#define ACL_BG_WHITE "\x1b[47m"

//Color Modifiers

#define ACL_MD_BRIGHT ";1m"

//Decorations
#define ACL_DC_BOLD "\x1b[1m"
#define ACL_DC_UNDL "\x1b[4m"
#define ACL_DC_REV "\x1b[7m"

//Reset style

#define ACT_RESET "\x1b[0m"

/* Additional ANSI Codes/Function Macros */

#define ACT_FN_CUR_UP(x) "\x1b[#xA"
#define ACT_FN_CUR_DOWN(x) "\x1b[#xB"
#define ACT_FN_CUR_RIGHT(x) "\x1b[#xC"
#define ACT_FN_CUR_LEFT(x) "\x1b[#xD"


#endif