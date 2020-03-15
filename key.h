/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

enum {NOCHAR, REGCHAR, UP, DOWN, LEFT, RIGHT, BADESC, PAUSE, QUIT, FREQ, RESET, FREQC, INC, DEC, SAVE, CLASS, SELECT, PLACE};

int read_escape(int *);
