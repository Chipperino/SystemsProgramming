/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "cell.h"
#include "game.h"
#include "well.h"
#include "key.h"

void init_game(void)
{
	int x,y;
}
//saves to file
int saveFile(FILE* fp, cell_t * cells[][24], int width, int height){
        int i, j, counter;
        for(i = 0; i < (height-1); i++){
                //fprintf(fp, "New line:");
                for(j = 0; j < (width-1); j++){
                        if(cells[j][i]-> state[CURRENT] == LIVE){
                                fprintf(fp, "+");
                        }
                        else{
                                fprintf(fp, " ");
                        }
                }
                fprintf(fp, "\n");
        }
        return 0;
}



int game(void)
{
	static int state = INIT;
	struct timespec tim = {0,150000};  // Each execution of while(1) is approximately 150mS changed from (0, 1000000) to 150000
	struct timespec tim_ret;
	struct timespec* timPtr=&tim;
	cell_t * cells[WELL_WIDTH-1][WELL_HEIGHT-1];
	int BOARDSIZE=0;
	int user_shape_x=0;
	int user_shape_y=0;
	well_t *w;
	int reset=0;
	int x_offset, y_offset;
	int x_max, y_max;
	int arrow;
	int move_counter = 0;
	int move_timeout = BASE_TIMEOUT;
	char save1[]="saves/save_1.life";
	char save2[]="saves/save_2.life";
	char save3[]="saves/save_3.life";
	char save4[]="saves/save_4.life";
	char save5[]="saves/save_5.life";
	char save6[]="saves/save_6.life";
	char save7[]="saves/save_7.life";
	char save8[]="saves/save_8.life";
	char save9[]="saves/save_9.life";
	char save10[]="saves/save_10.life";
	int save_counter=1;	
	int didINC=0;
	int didDEC=0;
	int test = 0;
	int resetMenu=0;
	while(1) {
		switch(state) {
		case INIT:                   // Initialize the game, only run one time
			initscr();
			save_counter=1;
			FILE * f1p;		//uses a one not an L
                        mkdir("saves", 0777);
                        f1p = fopen(save1, "w");
			
			nodelay(stdscr, TRUE);   // Do not wait for characters using getch.
			noecho();                // Do not echo input characters
			getmaxyx(stdscr, y_max, x_max);  // Get the screen dimensions
			x_offset=(x_max/2)-(WELL_WIDTH/2);
			y_offset=(y_max/2)-(WELL_HEIGHT/2);
			int tempx=x_offset-1;
			int tempy=y_offset-1;
			int tempWellWidth=WELL_WIDTH;
			int tempWellHeight=WELL_HEIGHT;
			cell_t * cells2[WELL_WIDTH+1][WELL_HEIGHT+1];
			cell_t * cells3[WELL_WIDTH+3][WELL_HEIGHT+3];
			cell_t * cells4[WELL_WIDTH+5][WELL_HEIGHT+5];
			int i,j;
			//create cells for for 2d arrays of different size
			for(i=0; i<(WELL_WIDTH-1);i++){
				for(j=0; j<(WELL_HEIGHT-1); j++){
					cells[i][j] = create_cell(x_offset + i, y_offset + j);
				}
			}
			for(i=0;i<(WELL_WIDTH+1);i++){
				for(j=0;j<(WELL_HEIGHT+1);j++){
					cells2[i][j]=create_cell(x_offset+i,y_offset+j);
				}
			}
			for(i=0;i<(WELL_WIDTH+3);i++){
				for(j=0;j<(WELL_HEIGHT+3);j++){
					cells3[i][j]=create_cell(x_offset+i,y_offset+j);
				}
			}
			for(i=0;i<(WELL_WIDTH+5);i++){
				for(j=0;j<(WELL_HEIGHT+5);j++){
					cells4[i][j]=create_cell(x_offset+i,y_offset+j);
				}
			}
			
			for(i=0;i<WELL_WIDTH+5;i++){
				for(j=0;j<WELL_HEIGHT+5;j++){
					undisplay_cell(cells4[i][j]);
				}
			}
			for(i=0;i<WELL_WIDTH+3;i++){
				for(j=0;j<WELL_HEIGHT+3;j++){
					undisplay_cell(cells3[i][j]);
				}
			}
			for(i=0;i<WELL_WIDTH+1;i++){
				for(j=0;j<WELL_HEIGHT+1;j++){
					undisplay_cell(cells2[i][j]);
				}
			}
			for(i=0; i<50;i++){
				for(j=0; j<30;j++){
					mvprintw(i,j,"                                                                                                                           ");
				}
			}
		            // still life
			cells[5][5]->state[CURRENT] = LIVE;
			cells[5][6]->state[CURRENT] = LIVE;
			cells[6][5]->state[CURRENT] = LIVE;
			cells[6][6]->state[CURRENT] = LIVE;

		            // glider
			cells[24][5]->state[CURRENT] = LIVE;
			cells[24][6]->state[CURRENT] = LIVE;
			cells[24][7]->state[CURRENT] = LIVE;
			cells[25][7]->state[CURRENT] = LIVE;
			cells[26][6]->state[CURRENT] = LIVE;

		            // oscillator
			cells[20][20]->state[CURRENT] = LIVE;
			cells[20][21]->state[CURRENT] = LIVE;
			cells[20][22]->state[CURRENT] = LIVE;

			//cells[22][20]->state[CURRENT] = LIVE;
			//cells[23][20]->state[CURRENT] = LIVE;
			//cells[23][18]->state[CURRENT] = LIVE;
			//cells[25][19]->state[CURRENT] = LIVE;
			//cells[26][20]->state[CURRENT] = LIVE;
			//cells[27][20]->state[CURRENT] = LIVE;
			//cells[28][20]->state[CURRENT] = LIVE;
			char input;
				mvprintw(0,30,"Welcome to Game of Life! Press S or s to start!");
				if(reset==0){
				mvprintw(1,30,"Would you like to add a shape?");
				nodelay(stdscr,FALSE);
				char choice=getch();
				nodelay(stdscr,TRUE);
				if(choice=='Y'||choice=='y'){
				mvprintw(1,30,"                              ");
				mvprintw(1,30,"Which Shape? 1 for Still-Life, 2 for Oscillator, 3 for Glider, 4 for random");
					nodelay(stdscr,FALSE);
					choice='a';
					choice=getch();
				//allow user to pick shape or random shape to place
					nodelay(stdscr,TRUE);
					if(choice=='1'){
						cells[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+1+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+1+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+1+10][user_shape_y+1+10]->state[CURRENT]=LIVE;
						mvprintw(1,30,"                                                                                                   ");
						mvprintw(1,30,"Choose an x ");
						nodelay(stdscr, FALSE);
						user_shape_x=getch();
						nodelay(stdscr, TRUE);
						nodelay(stdscr,FALSE);
						mvprintw(1,30,"Choose a y  ");
						user_shape_y=getch();
						nodelay(stdscr,TRUE);
						mvprintw(1,30,"Now Press S or s");
					}else if(choice=='2'){
						cells[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+11]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+12]->state[CURRENT]=LIVE;
						mvprintw(1,30,"                                                                                                   ");
						mvprintw(1,30,"Choose an x ");
						nodelay(stdscr,FALSE);
						user_shape_x=getch();
						nodelay(stdscr,TRUE);
						mvprintw(1,30,"Choose a y  ");
						nodelay(stdscr,FALSE);
						user_shape_y=getch();
						nodelay(stdscr,TRUE);
						mvprintw(1,30,"Now Press S or s");
					}else if(choice=='3'){
						cells[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+11]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+12]->state[CURRENT]=LIVE;
						cells[user_shape_x+11][user_shape_y+12]->state[CURRENT]=LIVE;
						cells[user_shape_x+12][user_shape_y+11]->state[CURRENT]=LIVE;
						mvprintw(1,30,"                                                                                                   ");
						mvprintw(1,30,"Choose an x ");
						nodelay(stdscr,FALSE);
						user_shape_x=getch();
						nodelay(stdscr,TRUE);
						mvprintw(1,30,"Choose a y  ");
						nodelay(stdscr,FALSE);
						user_shape_y=getch();
						nodelay(stdscr,TRUE);
						mvprintw(1,30,"Now Press S or s");
					}else if(choice=='4'){
						mvprintw(1,30,"                                                                                        ");
						mvprintw(1,30,"Now Press S or s");
						srand(time(NULL));
						int shape=rand()%3+1;
							shape=rand()%3+1;
							shape=rand()%3+1;
							if(shape==1){
							//mvprintw(0,0,"Still");
							srand(time(NULL));
							int sx=(rand()%48);
							int sy=(rand()%25);
							cells[sx][sy]->state[CURRENT]=LIVE;
							cells[sx][sy+1]->state[CURRENT]=LIVE;
							cells[sx+1][sy]->state[CURRENT]=LIVE;
							cells[sx+1][sy+1]->state[CURRENT]=LIVE;
							}else if(shape==2){
							//mvprintw(0,0,"Oscillator");
							srand(time(NULL));
							int ox=(rand()%48);
							int oy=(rand()%25);
							cells[ox][oy]->state[CURRENT]=LIVE;
							cells[ox][oy+1]->state[CURRENT]=LIVE;
							cells[ox][oy+2]->state[CURRENT]=LIVE;
							}else if(shape==3){
							//mvprintw(0,0,"Glider");
							srand(time(NULL));
							int gx=(rand()%48);
							int gy=(rand()%25);
							cells[gx][gy]->state[CURRENT]=LIVE;
							cells[gx][gy+1]->state[CURRENT]=LIVE;
							cells[gx][gy+2]->state[CURRENT]=LIVE;
							cells[gx+1][gy+2]->state[CURRENT]=LIVE;
							cells[gx+2][gy+1]->state[CURRENT]=LIVE;
							}
					}
				}
			}
		
					while(input!='s'&&input!='S'){
						input=getch();
					}
				
				mvprintw(0,30,"                                                                                                 ");
				mvprintw(1,30,"                                                             ");
			w = init_well(x_offset - 1, y_offset - 1, WELL_WIDTH, WELL_HEIGHT);
			draw_well(w);
			state = STEP;
			break;
		case STEP:
			//initialize cells2
			for(i=0;i<(WELL_WIDTH-1);i++){
				for(j=0;j<(WELL_HEIGHT-1);j++){
					cells2[i][j]=cells[i][j];
				}
			}
			for(i=WELL_WIDTH-1;i<WELL_WIDTH+1;i++){
				cells2[i][j]->state[CURRENT]=DIE;
			}
			//initialize cells3
			for(i=0;i<(WELL_WIDTH+1);i++){
				for(j=0;j<(WELL_HEIGHT+1);j++){
					cells3[i][j]=cells2[i][j];
				}
			}
			for(i=WELL_WIDTH+1;i<WELL_WIDTH+3;i++){
				cells3[i][j]->state[CURRENT]=DIE;
			}
			//initialize cells4
			for(i=0;i<(WELL_WIDTH+3);i++){
				for(j=0;j<(WELL_HEIGHT+3);j++){
					cells4[i][j]=cells3[i][j];
				}
			}
			for(i=WELL_WIDTH+3;i<WELL_WIDTH+5;i++){
				cells4[i][j]->state[CURRENT]=DIE;
			}
		if(BOARDSIZE==0){
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells[6][6]->state[NEW]);
				update_cells(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells);
				display_cells(WELL_WIDTH - 1, WELL_HEIGHT - 1, cells,BOARDSIZE);
				//cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			draw_well(w);
		}else if(BOARDSIZE==1){
			for(i=0;i<WELL_WIDTH+5;i++){
				for(j=0;j<WELL_HEIGHT+5;j++){
					undisplay_cell(cells4[i][j]);
				}
			}
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells2[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells2[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH + 1, WELL_HEIGHT + 1, cells2);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells2[6][6]->state[NEW]);
				update_cells(WELL_WIDTH +1, WELL_HEIGHT + 1, cells2);
				display_cells(WELL_WIDTH +1, WELL_HEIGHT +1, cells2,BOARDSIZE);
				//cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			draw_well(w);
			display_cells(WELL_WIDTH+1,WELL_HEIGHT+1,cells2,BOARDSIZE);
		}else if(BOARDSIZE==2){
			for(i=0;i<WELL_WIDTH+5;i++){
				for(j=0;j<WELL_HEIGHT+5;j++){
					undisplay_cell(cells4[i][j]);
				}
			}
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells3[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells3[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH + 3, WELL_HEIGHT + 3, cells3);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells3[6][6]->state[NEW]);
				update_cells(WELL_WIDTH + 3, WELL_HEIGHT + 3, cells3);
				display_cells(WELL_WIDTH + 3, WELL_HEIGHT + 3, cells3,BOARDSIZE);
				//cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			draw_well(w);
			display_cells(WELL_WIDTH+3,WELL_HEIGHT+3,cells3,BOARDSIZE);
		}else if(BOARDSIZE==3){
			for(i=0;i<WELL_WIDTH+3;i++){
				for(j=0;j<WELL_HEIGHT+3;j++){
					undisplay_cell(cells3[i][j]);
				}
			}
			if (move_counter > move_timeout) {
				mvprintw(1, 50, "cells[6][6] state[old]:%d\n", cells4[6][6]->state[OLD]);
				mvprintw(2, 50, "cells[6][6] state[current]:%d\n", cells4[6][6]->state[CURRENT]);
				update_neighbours(WELL_WIDTH + 5, WELL_HEIGHT + 5, cells4);
				mvprintw(3, 50, "cells[6][6] state[new]:%d\n", cells4[6][6]->state[NEW]);
				update_cells(WELL_WIDTH + 5, WELL_HEIGHT + 5, cells4);
				display_cells(WELL_WIDTH + 5, WELL_HEIGHT + 5, cells4,BOARDSIZE);
				//cells[8+test][8+test]->state[CURRENT] = LIVE;
				move_counter = 0;
			}
			draw_well(w);
			display_cells(WELL_WIDTH+5,WELL_HEIGHT+5,cells4,BOARDSIZE);
		}
			move_counter++;

			//added if statement to process user input
			int p=0;
			int freq_var=1;			
			int* pointer=&p;
			int read_esc=read_escape(pointer);
			//hit q to quit
                        if(read_esc==QUIT){
				//sets state to EXIT so game will end
					//printf("Exit");
				state=EXIT;
			//hit p to pause
			}else if(read_esc==PAUSE){
			//creates menu, highlighted element has yellow background with black foreground
			//unhighlighted elements have blue background with white foreground
				int cursor=0;
				start_color;
				init_pair(5, COLOR_WHITE, COLOR_BLUE);
				init_pair(6, COLOR_BLACK, COLOR_YELLOW);
				//pauses the game by starting a while loop
					//printf("YOU PRESSED P");
				//read_esc=52;
				mvprintw(0,5,"Menu: Press '1' to go UP or '2' to go DOWN");
				attron(COLOR_PAIR(6));
				mvprintw(1, 5,"Resume");
				attroff(COLOR_PAIR(6));
				attron(COLOR_PAIR(5));
				mvprintw(2,5,"Reset");
				mvprintw(3,5,"Load");
				mvprintw(4,5,"Help");
				mvprintw(5,5,"Quit");
				mvprintw(6,5,"Pick and Place");
				attroff(COLOR_PAIR(5));
				read_esc=read_escape(pointer);
				if(read_esc==SELECT){
					read_esc=PAUSE;
				}else{
					read_esc=52;
				}
				while(read_esc!=PAUSE){
					read_esc=read_escape(pointer);
					if(read_esc==DOWN){
						if(cursor<5){
							cursor++;
						}
						switch(cursor){
							case 1:
							//resets game
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(2,5,"Reset");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
								read_esc=read_escape(pointer);
								if(read_esc==SELECT){
									BOARDSIZE=0;
									tempWellWidth=WELL_WIDTH;
									tempWellHeight+WELL_HEIGHT;
									undraw_well(w);
									for(i=0;i<WELL_WIDTH-1;i++){
										for(j=0;j<WELL_HEIGHT-1;j++){
											undisplay_cell(cells[i][j]);
										}
									}
									reset=1;
									mvprintw(1,50,"                               ");
									mvprintw(2,50,"                               ");
									mvprintw(3,50,"                               ");
									state=INIT;
									mvprintw(1, 50, "Press p or P to restart");
									for(i=7;i<50;i++){
										for(j=0;j<40;j++){
											mvprintw(i,j,"                                                                                                                           ");
										}
									}
								}
								}
								//mvprintw(1,50,"                                ");
								mvprintw(6,19,"");
								break;
							case 2:
							//loads game
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(3,5,"Load");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
								read_esc=read_escape(pointer);
								if(read_esc==SELECT){
									BOARDSIZE=0;
									tempWellWidth=WELL_WIDTH;
									tempWellHeight+WELL_HEIGHT;
									undraw_well(w);
									for(i=0;i<WELL_WIDTH-1;i++){
										for(j=0;j<WELL_HEIGHT-1;j++){
											undisplay_cell(cells[i][j]);
										}
									}
									reset=1;
									mvprintw(1,50,"                               ");
									mvprintw(2,50,"                               ");
									mvprintw(3,50,"                               ");
									state=INIT;
									mvprintw(1, 50, "Press p or P to load");
									for(i=7;i<50;i++){
										for(j=0;j<40;j++){
											mvprintw(i,j,"                                                                                                                           ");
										}
									}
								}
								}
								break;
							case 3:
							//presents help menu
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(4,5,"Help");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
									read_esc=read_escape(pointer);
									if(read_esc==SELECT){
										mvprintw(9, 5, "This is your help guide. Each character needs to be pressed twice to activate.");
										mvprintw(10,5, "Keybinds:");
										mvprintw(11,5,"P/p: pauses the game");
										mvprintw(12,5,"+/-: increases/decreases play area size");
										mvprintw(13,5,"S/s: saves current game state");
										mvprintw(14,5,"R/r: resets the game");
										mvprintw(15,5,"Q/q: quits the game");
										mvprintw(16,5,"Up/Down arrows: navigate menu");
										mvprintw(17,5,"Enter: select menu option");
										mvprintw(18,5,"*: Speeds game frequency by 1.2");
										mvprintw(19,5,"C/c: Press and enter an integer to increase game frequency by that much");
										mvprintw(20,5,"V/v: Place a single cell or an randomly generated shape on the board");
										mvprintw(21,5,"I/i: Form the Shape of C291 with cells on the board");	
									}	
								}
								for(i=9;i<22;i++){
									mvprintw(i,5,"                                                                                      ");
								}
								mvprintw(6,19,"");
								break;
							case 4:
							//allows user to quit
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(5,5,"Quit");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
									read_esc=read_escape(pointer);
									if(read_esc==SELECT){
										state=EXIT;
										read_esc=PAUSE;	
									}
								}
								break;
							case 5:
							//allows user to pick and place a shape or cell
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(6));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
									read_esc=read_escape(pointer);
									if(read_esc==SELECT){
									mvprintw(8,5,"Which Shape? 1 for Still-Life, 2 for Oscillator, 3 for Glider");
									nodelay(stdscr,FALSE);
									int choice='a';
									choice=getch();
									nodelay(stdscr,TRUE);
					if(choice=='1'){
						cells[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+10][user_shape_y+1+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+1+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells[user_shape_x+1+10][user_shape_y+1+10]->state[CURRENT]=LIVE;
						mvprintw(8,5,"                                                                                 ");
						mvprintw(8,5,"Choose an x ");
						nodelay(stdscr,FALSE);
						user_shape_x=(int)getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						mvprintw(8,5,"Choose a y ");
						nodelay(stdscr,FALSE);
						user_shape_y=(int)getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						mvprintw(8,5,"Now Press P or p");
					}else if(choice=='2'){
						mvprintw(8,5,"                                                                                 ");
						mvprintw(8,5,"Choose an x ");
						nodelay(stdscr,FALSE);
						user_shape_x=(int)getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						mvprintw(8,5,"Choose a y ");
						nodelay(stdscr,FALSE);
						user_shape_y=(int)getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						cells2[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells2[user_shape_x+10][user_shape_y+11]->state[CURRENT]=LIVE;
						cells2[user_shape_x+10][user_shape_y+12]->state[CURRENT]=LIVE;
						mvprintw(8,5,"Now Press P or p");
					}else if(choice=='3'){
						mvprintw(8,5,"                                                                                ");
						mvprintw(8,5,"Choose an x ");
						nodelay(stdscr,FALSE);
						user_shape_x=getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						mvprintw(8,5,"Choose a y ");
						nodelay(stdscr,FALSE);
						user_shape_y=getch();
						nodelay(stdscr,TRUE);
						//mvprintw(8,5,"                           ");
						cells2[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
						cells2[user_shape_x+10][user_shape_y+11]->state[CURRENT]=LIVE;
						cells2[user_shape_x+10][user_shape_y+12]->state[CURRENT]=LIVE;
						cells2[user_shape_x+11][user_shape_y+12]->state[CURRENT]=LIVE;
						cells2[user_shape_x+12][user_shape_y+11]->state[CURRENT]=LIVE;
						mvprintw(8,5,"Now Press P or p");
					}	
						}
							}
						mvprintw(8,5,"                ");
								break;
								
					}
						//printf("down");
					}else if(read_esc==UP){
						if(cursor>0){
						cursor--;
						}
						switch(cursor){
							case 4:
							//allows user to quit
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(5,5,"Quit");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
									read_esc=read_escape(pointer);
									if(read_esc==SELECT){
										state=EXIT;
										read_esc=PAUSE;	
									}
								}
								break;
							case 3:
							//presents help menu
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(4,5,"Help");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
									read_esc=read_escape(pointer);
									if(read_esc==SELECT){
										mvprintw(9, 5, "This is your help guide. Each character needs to be pressed twice to activate.");
										mvprintw(10,5, "Keybinds:");
										mvprintw(11,5,"P/p: pauses the game");
										mvprintw(12,5,"+/-: increases/decreases play area size");
										mvprintw(13,5,"S/s: saves current game state");
										mvprintw(14,5,"R/r: resets the game");
										mvprintw(15,5,"Q/q: quits the game");
										mvprintw(16,5,"Up/Down arrows: navigate menu");
										mvprintw(17,5,"Enter: select menu option");
										mvprintw(18,5,"*: Speeds game frequency by 1.2");
										mvprintw(19,5,"C/c: Press and enter an integer to increase game frequency by that much.");
										mvprintw(20,5,"V/v: Place a single cell or an randomly generated shape on the board");
										mvprintw(21,5,"I/i: Form the Shape of C291 with cells on the board");	
									}	
								}
								for(i=9;i<22;i++){
									mvprintw(i,5,"                                                                                 ");
								}
								mvprintw(6,19,"");
								break;
							case 2:
							//loads game
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								mvprintw(2,5,"Reset");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(3,5,"Load");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
								read_esc=read_escape(pointer);
								if(read_esc==SELECT){
									BOARDSIZE=0;
									tempWellWidth=WELL_WIDTH;
									tempWellHeight+WELL_HEIGHT;
									undraw_well(w);
									for(i=0;i<WELL_WIDTH-1;i++){
										for(j=0;j<WELL_HEIGHT-1;j++){
											undisplay_cell(cells[i][j]);
										}
									}
									reset=1;
									mvprintw(1,50,"                               ");
									mvprintw(2,50,"                               ");
									mvprintw(3,50,"                               ");
									state=INIT;
									mvprintw(1, 50, "Press p or P to load");
									for(i=7;i<50;i++){
										for(j=0;j<40;j++){
											mvprintw(i,j,"                                                                                                                           ");
										}
									}
								}
								}
								break;
							case 1:
							//resets game
								attron(COLOR_PAIR(5));
								mvprintw(1, 5,"Resume");
								attroff(COLOR_PAIR(5));
								attron(COLOR_PAIR(6));
								mvprintw(2,5,"Reset");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=52;
								while(read_esc!=DOWN&&read_esc!=UP&&read_esc!=PAUSE){
								read_esc=read_escape(pointer);
								if(read_esc==SELECT){
									BOARDSIZE=0;
									tempWellWidth=WELL_WIDTH;
									tempWellHeight+WELL_HEIGHT;
									undraw_well(w);
									for(i=0;i<WELL_WIDTH-1;i++){
										for(j=0;j<WELL_HEIGHT-1;j++){
											undisplay_cell(cells[i][j]);
										}
									}
									reset=1;
									mvprintw(1,50,"                               ");
									mvprintw(2,50,"                               ");
									mvprintw(3,50,"                               ");
									state=INIT;
									mvprintw(1, 50, "Press p or P to restart");
								}
								}
								//mvprintw(1,50,"                                ");
								mvprintw(6,19,"");
								break;
							case 0:
							//resumes game
								attron(COLOR_PAIR(6));
								mvprintw(1, 5,"Resume");
								attroff(COLOR_PAIR(6));
								attron(COLOR_PAIR(5));
								mvprintw(2,5,"Reset");
								mvprintw(3,5,"Load");
								mvprintw(4,5,"Help");
								mvprintw(5,5,"Quit");
								mvprintw(6,5,"Pick and Place");
								attroff(COLOR_PAIR(5));
								read_esc=read_escape(pointer);
								if(read_esc==SELECT){
									read_esc=PAUSE;
								}
								break;
						}
					}
				}
					mvprintw(0,5, "                                             ");
					mvprintw(1, 5, "             ");
					mvprintw(2, 5, "     ");
					mvprintw(3, 5, "    ");
					mvprintw(4, 5, "    ");
					mvprintw(5, 5, "    ");
					mvprintw(6, 5, "              ");
			//hit r to reset					
			}else if(read_esc==RESET){
				BOARDSIZE=0;
				tempWellWidth=WELL_WIDTH;
				tempWellHeight+WELL_HEIGHT;
				//resets the game
					//printf("YOU PRESSED R");
				undraw_well(w);
				for(i=0;i<WELL_WIDTH-1;i++){
					for(j=0;j<WELL_HEIGHT-1;j++){
						undisplay_cell(cells[i][j]);
					}
				}
				reset=1;
				mvprintw(1,50,"                               ");
				mvprintw(2,50,"                               ");
				mvprintw(3,50,"                               ");
				state=INIT;
			//hit * to change speed by 1.2
			}else if(read_esc==FREQ){
			//changes the frequency
			struct timespec tim2={0, (150000/1.2)};
			timPtr=&tim2;
			//hit c to change the frequency	
			}else if(read_esc==FREQC){
				//changes the frequency of the game
				//printf("Enter the variable frequency");
				freq_var=0;
				//sleep(1);
				while(freq_var==0){
				//getch();
				scanf(" %d", &freq_var);
				}
				if(freq_var>0){
					struct timespec tim3={0, (150000/freq_var)};
					timPtr=&tim3;
				}
			}else if(read_esc==INC){
				if(BOARDSIZE<3){
					didINC=1;
					tempWellWidth+=2;
					tempWellHeight+=2;
					undraw_well(w);
					tempx-=1;
					tempy-=1;
					changeWellSize(tempx,tempy,tempWellWidth,tempWellHeight,w);
					draw_well(w); 
					BOARDSIZE++;	
				}	
			}else if(read_esc==DEC){
				if(BOARDSIZE>0){
					didDEC=1;
					tempWellWidth-=2;
					tempWellHeight-=2;
					undraw_well(w);
					tempx+=1;
					tempy+=1;
					changeWellSize(tempx,tempy,tempWellWidth,tempWellHeight,w);
					draw_well(w);
					BOARDSIZE--;
				}
			}else if(read_esc==SAVE){
			if(BOARDSIZE==0){
				if(save_counter==1){
					remove(save1);
					f1p = fopen(save1, "w");
					save_counter++;
				}else if(save_counter==2){
					remove(save2);
					f1p=fopen(save2,"w");
					save_counter++;
				}else if(save_counter==3){
					remove(save3);
					f1p=fopen(save3,"w");
					save_counter++;
				}else if(save_counter==4){
					remove(save4);
					f1p=fopen(save4,"w");
					save_counter++;
				}else if(save_counter==5){
					remove(save5);
					f1p=fopen(save5,"w");
					save_counter++;
				}else if(save_counter==6){
					remove(save6);
					f1p=fopen(save6,"w");
					save_counter++;
				}else if(save_counter==7){
					remove(save7);
					f1p=fopen(save7,"w");
					save_counter++;
				}else if(save_counter==8){
					remove(save8);
					f1p=fopen(save8,"w");
					save_counter++;
				}else if(save_counter==9){
					remove(save9);
					f1p=fopen(save9,"w");
					save_counter++;
				}else if(save_counter==10){
					remove(save10);
					f1p=fopen(save10,"w");
				}
				if(save_counter<11){
				//fprintf(f1p, "X Size:    Y Size:\n");
				saveFile(f1p, cells, WELL_WIDTH, WELL_HEIGHT);
				//fprintf(f1p, "One part done\n");
				fclose(f1p);
			}
				}
				}else if(read_esc==CLASS){
				//spells C291 depending on the size of the board
					int p=0;
					int q=0;
					if(BOARDSIZE==0){
						//clear board
						
						for(i=0;i<WELL_WIDTH-1;i++){
							for(j=0;j<WELL_HEIGHT-1;j++){
								cells[i][j]->state[CURRENT]=DIE;
								
							}
						}
						/*for(i=0;i<WELL_WIDTH+5;i++){
							for(j=0;j<WELL_HEIGHT+5;j++){
								undisplay_cell(cells4[i][j]);
							}
						}*/
						//spells C
						cells[1][1]->state[CURRENT]=LIVE;
						cells[2][1]->state[CURRENT]=LIVE;
						cells[3][1]->state[CURRENT]=LIVE;
						cells[1][2]->state[CURRENT]=LIVE;
						cells[1][3]->state[CURRENT]=LIVE;
						cells[1][4]->state[CURRENT]=LIVE;
						cells[1][5]->state[CURRENT]=LIVE;
						cells[2][5]->state[CURRENT]=LIVE;
						cells[3][5]->state[CURRENT]=LIVE;
						
						//spells 2
						cells[5][1]->state[CURRENT]=LIVE;
						cells[6][1]->state[CURRENT]=LIVE;
						cells[7][1]->state[CURRENT]=LIVE;
						cells[7][2]->state[CURRENT]=LIVE;
						cells[7][3]->state[CURRENT]=LIVE;
						cells[6][3]->state[CURRENT]=LIVE;
						cells[5][3]->state[CURRENT]=LIVE;
						cells[5][4]->state[CURRENT]=LIVE;
						cells[5][5]->state[CURRENT]=LIVE;
						cells[6][5]->state[CURRENT]=LIVE;
						cells[7][5]->state[CURRENT]=LIVE;

						//spells 9
						cells[9][1]->state[CURRENT]=LIVE;
						cells[10][1]->state[CURRENT]=LIVE;
						cells[11][1]->state[CURRENT]=LIVE;
						cells[11][2]->state[CURRENT]=LIVE;
						cells[11][3]->state[CURRENT]=LIVE;
						cells[11][4]->state[CURRENT]=LIVE;
						cells[11][5]->state[CURRENT]=LIVE;
						cells[9][2]->state[CURRENT]=LIVE;
						cells[9][3]->state[CURRENT]=LIVE;
						cells[10][3]->state[CURRENT]=LIVE;
						
						//spells 1
						cells[13][1]->state[CURRENT]=LIVE;
						cells[14][1]->state[CURRENT]=LIVE;
						//cells[15][1]->state[CURRENT]=LIVE;
						cells[14][2]->state[CURRENT]=LIVE;
						cells[14][3]->state[CURRENT]=LIVE;
						cells[14][4]->state[CURRENT]=LIVE;
						cells[15][5]->state[CURRENT]=LIVE;
						cells[13][5]->state[CURRENT]=LIVE;
						cells[15][5]->state[CURRENT]=LIVE;
						cells[14][5]->state[CURRENT]=LIVE;
					draw_well(w);
					display_cells(WELL_WIDTH-1,WELL_HEIGHT-1,cells,BOARDSIZE);
						read_esc=52;
					while(read_esc!=PAUSE){
						read_esc=read_escape(pointer);
					}
					}else if(BOARDSIZE==1){
						//clear board
						
						for(i=0;i<WELL_WIDTH+1;i++){
							for(j=0;j<WELL_HEIGHT+1;j++){
								cells2[i][j]->state[CURRENT]=DIE;
								
							}
						}
						/*for(i=0;i<WELL_WIDTH+5;i++){
							for(j=0;j<WELL_HEIGHT+5;j++){
								undisplay_cell(cells4[i][j]);
							}
						}*/
						//spells C
						cells2[1][1]->state[CURRENT]=LIVE;
						cells2[2][1]->state[CURRENT]=LIVE;
						cells2[3][1]->state[CURRENT]=LIVE;
						cells2[1][2]->state[CURRENT]=LIVE;
						cells2[1][3]->state[CURRENT]=LIVE;
						cells2[1][4]->state[CURRENT]=LIVE;
						cells2[1][5]->state[CURRENT]=LIVE;
						cells2[2][5]->state[CURRENT]=LIVE;
						cells2[3][5]->state[CURRENT]=LIVE;
						
						//spells 2
						cells2[5][1]->state[CURRENT]=LIVE;
						cells2[6][1]->state[CURRENT]=LIVE;
						cells2[7][1]->state[CURRENT]=LIVE;
						cells2[7][2]->state[CURRENT]=LIVE;
						cells2[7][3]->state[CURRENT]=LIVE;
						cells2[6][3]->state[CURRENT]=LIVE;
						cells2[5][3]->state[CURRENT]=LIVE;
						cells2[5][4]->state[CURRENT]=LIVE;
						cells2[5][5]->state[CURRENT]=LIVE;
						cells2[6][5]->state[CURRENT]=LIVE;
						cells2[7][5]->state[CURRENT]=LIVE;

						//spells 9
						cells2[9][1]->state[CURRENT]=LIVE;
						cells2[10][1]->state[CURRENT]=LIVE;
						cells2[11][1]->state[CURRENT]=LIVE;
						cells2[11][2]->state[CURRENT]=LIVE;
						cells2[11][3]->state[CURRENT]=LIVE;
						cells2[11][4]->state[CURRENT]=LIVE;
						cells2[11][5]->state[CURRENT]=LIVE;
						cells2[9][2]->state[CURRENT]=LIVE;
						cells2[9][3]->state[CURRENT]=LIVE;
						cells2[10][3]->state[CURRENT]=LIVE;
						
						//spells 1
						cells2[13][1]->state[CURRENT]=LIVE;
						cells2[14][1]->state[CURRENT]=LIVE;
						//cells[15][1]->state[CURRENT]=LIVE;
						cells2[14][2]->state[CURRENT]=LIVE;
						cells2[14][3]->state[CURRENT]=LIVE;
						cells2[14][4]->state[CURRENT]=LIVE;
						cells2[15][5]->state[CURRENT]=LIVE;
						cells2[13][5]->state[CURRENT]=LIVE;
						cells2[15][5]->state[CURRENT]=LIVE;
						cells2[14][5]->state[CURRENT]=LIVE;
					draw_well(w);
					display_cells(WELL_WIDTH+1,WELL_HEIGHT+1,cells2,BOARDSIZE);
						read_esc=52;
					while(read_esc!=PAUSE){
						read_esc=read_escape(pointer);
					}
					}else if(BOARDSIZE==2){
						//clear board
						
						for(i=0;i<WELL_WIDTH+3;i++){
							for(j=0;j<WELL_HEIGHT+3;j++){
								cells3[i][j]->state[CURRENT]=DIE;
								
							}
						}
						/*for(i=0;i<WELL_WIDTH+5;i++){
							for(j=0;j<WELL_HEIGHT+5;j++){
								undisplay_cell(cells4[i][j]);
							}
						}*/
						//spells C
						cells3[1][1]->state[CURRENT]=LIVE;
						cells3[2][1]->state[CURRENT]=LIVE;
						cells3[3][1]->state[CURRENT]=LIVE;
						cells3[1][2]->state[CURRENT]=LIVE;
						cells3[1][3]->state[CURRENT]=LIVE;
						cells3[1][4]->state[CURRENT]=LIVE;
						cells3[1][5]->state[CURRENT]=LIVE;
						cells3[2][5]->state[CURRENT]=LIVE;
						cells3[3][5]->state[CURRENT]=LIVE;
						
						//spells 2
						cells3[5][1]->state[CURRENT]=LIVE;
						cells3[6][1]->state[CURRENT]=LIVE;
						cells3[7][1]->state[CURRENT]=LIVE;
						cells3[7][2]->state[CURRENT]=LIVE;
						cells3[7][3]->state[CURRENT]=LIVE;
						cells3[6][3]->state[CURRENT]=LIVE;
						cells3[5][3]->state[CURRENT]=LIVE;
						cells3[5][4]->state[CURRENT]=LIVE;
						cells3[5][5]->state[CURRENT]=LIVE;
						cells3[6][5]->state[CURRENT]=LIVE;
						cells3[7][5]->state[CURRENT]=LIVE;

						//spells 9
						cells3[9][1]->state[CURRENT]=LIVE;
						cells3[10][1]->state[CURRENT]=LIVE;
						cells3[11][1]->state[CURRENT]=LIVE;
						cells3[11][2]->state[CURRENT]=LIVE;
						cells3[11][3]->state[CURRENT]=LIVE;
						cells3[11][4]->state[CURRENT]=LIVE;
						cells3[11][5]->state[CURRENT]=LIVE;
						cells3[9][2]->state[CURRENT]=LIVE;
						cells3[9][3]->state[CURRENT]=LIVE;
						cells3[10][3]->state[CURRENT]=LIVE;
						
						//spells 1
						cells3[13][1]->state[CURRENT]=LIVE;
						cells3[14][1]->state[CURRENT]=LIVE;
						//cells[15][1]->state[CURRENT]=LIVE;
						cells3[14][2]->state[CURRENT]=LIVE;
						cells3[14][3]->state[CURRENT]=LIVE;
						cells3[14][4]->state[CURRENT]=LIVE;
						cells3[15][5]->state[CURRENT]=LIVE;
						cells3[13][5]->state[CURRENT]=LIVE;
						cells3[15][5]->state[CURRENT]=LIVE;
						cells3[14][5]->state[CURRENT]=LIVE;
					draw_well(w);
					display_cells(WELL_WIDTH+3,WELL_HEIGHT+3,cells3,BOARDSIZE);
						read_esc=52;
					while(read_esc!=PAUSE){
						read_esc=read_escape(pointer);
					}
					}else if(BOARDSIZE==3){
						//clear board
						
						for(i=0;i<WELL_WIDTH+5;i++){
							for(j=0;j<WELL_HEIGHT+5;j++){
								cells4[i][j]->state[CURRENT]=DIE;
								
							}
						}
						/*for(i=0;i<WELL_WIDTH+5;i++){
							for(j=0;j<WELL_HEIGHT+5;j++){
								undisplay_cell(cells4[i][j]);
							}
						}*/
						//spells C
						cells4[1][1]->state[CURRENT]=LIVE;
						cells4[2][1]->state[CURRENT]=LIVE;
						cells4[3][1]->state[CURRENT]=LIVE;
						cells4[1][2]->state[CURRENT]=LIVE;
						cells4[1][3]->state[CURRENT]=LIVE;
						cells4[1][4]->state[CURRENT]=LIVE;
						cells4[1][5]->state[CURRENT]=LIVE;
						cells4[2][5]->state[CURRENT]=LIVE;
						cells4[3][5]->state[CURRENT]=LIVE;
						
						//spells 2
						cells4[5][1]->state[CURRENT]=LIVE;
						cells4[6][1]->state[CURRENT]=LIVE;
						cells4[7][1]->state[CURRENT]=LIVE;
						cells4[7][2]->state[CURRENT]=LIVE;
						cells4[7][3]->state[CURRENT]=LIVE;
						cells4[6][3]->state[CURRENT]=LIVE;
						cells4[5][3]->state[CURRENT]=LIVE;
						cells4[5][4]->state[CURRENT]=LIVE;
						cells4[5][5]->state[CURRENT]=LIVE;
						cells4[6][5]->state[CURRENT]=LIVE;
						cells4[7][5]->state[CURRENT]=LIVE;

						//spells 9
						cells4[9][1]->state[CURRENT]=LIVE;
						cells4[10][1]->state[CURRENT]=LIVE;
						cells4[11][1]->state[CURRENT]=LIVE;
						cells4[11][2]->state[CURRENT]=LIVE;
						cells4[11][3]->state[CURRENT]=LIVE;
						cells4[11][4]->state[CURRENT]=LIVE;
						cells4[11][5]->state[CURRENT]=LIVE;
						cells4[9][2]->state[CURRENT]=LIVE;
						cells4[9][3]->state[CURRENT]=LIVE;
						cells4[10][3]->state[CURRENT]=LIVE;
						
						//spells 1
						cells4[13][1]->state[CURRENT]=LIVE;
						cells4[14][1]->state[CURRENT]=LIVE;
						//cells[15][1]->state[CURRENT]=LIVE;
						cells4[14][2]->state[CURRENT]=LIVE;
						cells4[14][3]->state[CURRENT]=LIVE;
						cells4[14][4]->state[CURRENT]=LIVE;
						cells4[15][5]->state[CURRENT]=LIVE;
						cells4[13][5]->state[CURRENT]=LIVE;
						cells4[15][5]->state[CURRENT]=LIVE;
						cells4[14][5]->state[CURRENT]=LIVE;
					draw_well(w);
					display_cells(WELL_WIDTH+5,WELL_HEIGHT+5,cells4,BOARDSIZE);
						read_esc=52;
					while(read_esc!=PAUSE){
						read_esc=read_escape(pointer);
					}
					}
				
				break;
			}else if(read_esc==PLACE){
			//allows user to place a single cell or a random shape
				mvprintw(1,5,"Press 1 to place a single cell"); 
				mvprintw(2,5,"or 2 for a random shape");
				char choice3='a';
				nodelay(stdscr,FALSE);
				choice3=getch();
				nodelay(stdscr,TRUE);
				if(choice3=='1'){
					mvprintw(1,5,"                                          ");
					mvprintw(2,5,"                                          ");
					mvprintw(1,5,"Enter an x ");
					nodelay(stdscr,FALSE);
					user_shape_x=getch();
					nodelay(stdscr,TRUE);
					mvprintw(1,5,"Enter a y  ");
					nodelay(stdscr,FALSE);
					user_shape_y=getch();
					nodelay(stdscr,TRUE);
					cells3[user_shape_x+10][user_shape_y+10]->state[CURRENT]=LIVE;
					mvprintw(1,5,"                                      ");
					mvprintw(2,5,"                                      ");	
				}else if(choice3=='2'){
						mvprintw(1,5,"                                          ");
						mvprintw(2,5,"                                          ");
						srand(time(NULL));
						int shape=rand()%3+1;
							shape=rand()%3+1;
							shape=rand()%3+1;
							if(shape==1){
							//mvprintw(0,0,"Still");
							srand(time(NULL));
							int sx=(rand()%48);
							int sy=(rand()%25);
							cells3[sx][sy]->state[CURRENT]=LIVE;
							cells3[sx][sy+1]->state[CURRENT]=LIVE;
							cells3[sx+1][sy]->state[CURRENT]=LIVE;
							cells3[sx+1][sy+1]->state[CURRENT]=LIVE;
							}else if(shape==2){
							//mvprintw(0,0,"Oscillator");
							srand(time(NULL));
							int ox=(rand()%48);
							int oy=(rand()%25);
							cells3[ox][oy]->state[CURRENT]=LIVE;
							cells3[ox][oy+1]->state[CURRENT]=LIVE;
							cells3[ox][oy+2]->state[CURRENT]=LIVE;
							}else if(shape==3){
							//mvprintw(0,0,"Glider");
							srand(time(NULL));
							int gx=(rand()%48);
							int gy=(rand()%25);
							cells3[gx][gy]->state[CURRENT]=LIVE;
							cells3[gx][gy+1]->state[CURRENT]=LIVE;
							cells3[gx][gy+2]->state[CURRENT]=LIVE;
							cells3[gx+1][gy+2]->state[CURRENT]=LIVE;
							cells3[gx+2][gy+1]->state[CURRENT]=LIVE;
							}
				}else{
				mvprintw(1,5,"                                          ");
				mvprintw(2,5,"                                          ");
				}	
			}
			// TODO: Figure out if this works VVVVV
			//update_cells(WELL_WIDTH - 2, WELL_HEIGHT - 2, cells);
			break;
		case EXIT:
			//printf("Exit2");
			undraw_well(w);//undraws well using function in well.c
			//undisplay_cell(cells);
			for(i=0;i<WELL_WIDTH-1;i++){
				for(j=0;j<WELL_HEIGHT-1;j++){
					undisplay_cell(cells[i][j]);
				}
			}
			for(i=0;i<WELL_WIDTH+1;i++){
				for(j=0;j<WELL_HEIGHT+1;j++){
					undisplay_cell(cells2[i][j]);
				}
			}
			for(i=0;i<WELL_WIDTH+3;i++){
				for(j=0;j<WELL_HEIGHT+3;j++){
					undisplay_cell(cells3[i][j]);
				}
			}
			for(i=0;i<WELL_WIDTH+5;i++){
				for(j=0;j<WELL_HEIGHT+5;j++){
					undisplay_cell(cells4[i][j]);
				}
			}
			mvprintw(1,50,"                                    ");
			mvprintw(2,50,"                                    ");
			mvprintw(3,50,"                                    ");
			for(i=0; i<50;i++){
				mvprintw(i, 50, "                                                                                                     ");
			}
			char input2;
			while(input2!='q'&&input2!='Q'){
			mvprintw(0,55,"All life has ended. Why did you have to do this? Press Q or q to end");
			input2=getch();
			}
			endwin();
			//end();
			//endwin();
			return(0);
			break;
		}
		refresh();
		nanosleep(timPtr,&tim_ret);
	}
}
