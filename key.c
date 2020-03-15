/* key.c ---------
 *
 * Filename: key.c
 * Description: Controls all key inputs
 * Author: Bryce Himebaugh
 * Maintainer:
 * Created: Thu Sep 15 16:35:07 2017
 * Last-Updated: September 23 15:38 2018
 *           By: Dmitrii Galantsev
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */
#include <stdio.h>
#include <ncurses.h>
#include "key.h"
//changed it so that it doesn't require esc and [ characters
int read_escape(int *read_char)
{
	int c;
	if ((c = getch()) == ERR) {
		//printf("NOCHAR");
		return (NOCHAR);
	}
		//c==0x1b
	else if (getch()==52) {
		if (getch() == '[') {
			switch (getch()) {
			//printf("Switch");
			case 'A':
				return (UP);
				break;
			case 'B':
				return (DOWN);
				break;
			case 'C':
				return (RIGHT);
				break;
			case 'D':
				return (LEFT);
				break;
			default:
				//printf("End");
				return (BADESC);
			}
		}
	}
	else {
		//printf("KEY.c else ");
		       c=getchar();
			switch(c){
			case 'p':
                                return (PAUSE);
                                break;
                        case 'P':
                                return (PAUSE);
                                break;
                        case 'q':
                                return (QUIT);
                                break;
                        case 'Q':
                                return (QUIT);
                                break;
                        case 'r':
                                return (RESET);
                                break;
                        case 'R':
                                return (RESET);
                                break;
                        case '*':
                                return (FREQ);
                                break;
                        case 'C':
                                return (FREQC);
                                break;
                        case 'c':
                                return (FREQC);
                                break;
			case '+':
				return (INC);
				break;
			case'-':
				return (DEC);
				break;
			case's':
				return (SAVE);
				break;
			case'S':
				return (SAVE);
				break;
			case'I':
				//printf("IIIIIIII");
				return (CLASS);
				break;
			case'i':
				//printf("iiiiiiii");
				return (CLASS);
				break;
			case (char)13://enter key
				return (SELECT);
				break;
			case '2':
				return (DOWN);
				break;
			case '1':
				return (UP);
				break;
			case 'v':
				return (PLACE);
			case 'V':
				return (PLACE);
                        default:
                                //printf("End");
                                return (BADESC);
			}
		*read_char = c;
		return (REGCHAR);
	}
}
