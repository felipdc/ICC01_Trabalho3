#ifndef _INTERFACE_H_
#define _INTERFACE_H_


#if defined (_WIN32) || defined (_WIN64)
#define clrscr() system ("cls")
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif	


void display_splash_screen ();
void option_handle (bool sample);
uint64_t read_x (uint64_t m);
uint64_t read_y (uint64_t n);


#endif /* _INTERFACE_H_ */