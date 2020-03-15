/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

typedef struct terminal_dimensions
{
  int maxx;
  int maxy;
} terminal_dimensions_t;

// Delay timers for the main game loop.
#ifndef DELAY_US
#define DELAY_US 100000
#define BASE_TIMEOUT 600 //changed from 600 to 150
#endif

// Game States
enum {START,INIT, STEP, EXIT};

void init_game(void);
void end(void);
int game(void);

/* game.h ends here */
