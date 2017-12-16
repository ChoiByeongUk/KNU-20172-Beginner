#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "character.h"
#include "game_signal.h"

void show_character(int dist)
{
	int cnt = 0;
	int i, j;
	int k;
	for(k=0; k<2; k++)
	{
		characterInfo.ypos -= dist;
			for(i=0; i<3; i++)
			{
				for(j=0; j<3; j++)
				{
					move(characterInfo.ypos - 2 + i, 5 + j);
					addch(characterInfo.character[i][j]);
				}
			}

			move(0, COLS-1);
			refresh();
			for(i=0; i<3; i++)
			{
				move(characterInfo.ypos-2+i, 5);
				addstr("   ");
			}
		characterInfo.ypos += dist;
		usleep(5000);
	}
}

void move_character()
{
	void input_handler(int);
	int movedir = 0;
	signal(SIGALRM, SIG_IGN);
	switch(characterInfo.state)
	{
		case JUMPING:
			movedir = 3;
			break;
		case SLIDING:
			characterInfo.character[0][1] = ' ';
			characterInfo.character[1][0] = ' ';
			characterInfo.character[1][1] = ' ';
			characterInfo.character[1][2] = ' ';
			characterInfo.character[2][0] = '-';
			characterInfo.character[2][1] = '-';
			characterInfo.character[2][2] = 'O';
			break;
	}

	show_character(movedir);
	init_character_info();
	signal(SIGALRM, move_character);
}

void init_character_info()
{
	characterInfo.character[0][0] = ' ';
	characterInfo.character[0][1] = 'O';
	characterInfo.character[0][2] = ' ';
	characterInfo.character[1][0] = '-';
	characterInfo.character[1][1] = '|';
	characterInfo.character[1][2] = '-';
	characterInfo.character[2][0] = '/';
	characterInfo.character[2][1] = ' ';
	characterInfo.character[2][2] = '\\';

	characterInfo.ypos = LINES-3;
	characterInfo.state = STANDING;
}
