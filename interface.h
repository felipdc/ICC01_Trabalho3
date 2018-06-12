#ifndef _INTERFACE_H_
#define _INTERFACE_H_


#if defined (_WIN32) || defined (_WIN64)
#define clrscr() system ("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif	


void display_splash_screen ();
void option_handle ();

#endif // _INTERFACE_H_