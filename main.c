/* Copyright (c) 2004-2007 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

/* Code: */
#include <stdio.h>
#include <ncurses.h>
#include "cell.h"
#include "game.h"

int main(void)
{/*
printf("********************Welcome to Game of Life!********************\n");
printf("                  Refactored By Chip Simmerman\n");
printf("                     Press S or s to Start!\n");
printf("    Remember this program DOES NOT use ANSI Escape Sequences!\n");
char c;
	while(c!='S'&&c!='s'){
		scanf("%c", &c);
		if(c!='S'&&c!='s'){
			printf("Please enter S or s.\n");
		}
	}
*/
  game();
/*
printf("All life has ended. Why did you have to do this? (Press any key to exit.)");
scanf("%c", &c);
*/
  return (0);
}
