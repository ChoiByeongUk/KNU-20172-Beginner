#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "game_map.h"

/****************************************************************
 * function declaration
 */

void set_ticker(int);
void initScreen();
void restoreScreen();
void addObstacle(int type, int r, int c);

/****************************************************************
 * function definition
 */

void initScreen()
{
	initscr();

	srand(time(NULL));

	// initialize obstacles
	g_iGround = (int)((double)LINES / 10 * 9);
	for(int i = 0; i < MAX_OBSTACLES; i++)
	{
		obs[i].type = rand() % 2 + 1;
		obs[i].row = g_iGround;
		obs[i].col = COLS;

		while(i > 0 && abs(obs[i].col - obs[i - 1].col) < 20)
			obs[i].col = COLS + (20 * (rand() % 5 + 1));
	}
}

// add obstacle to the given coordinate and remove previous obstacle
void addObstacle(int type, int r, int c)
{
	switch(type)
	{
		// vertical obstacle
		case 1:
		{
			move(r - 2, c);
			vline('*', 2);
			move(r - 2, c + 1);
			vline(' ', 2);

			break;
		}
		// horizontal obstacle
		case 2:
		{
			move(r - 3, c);
			hline('*', 2);
			mvaddch(r - 3, c + 2, ' ');

			break;
		}
		default: return;
	}
	move(LINES - 1, COLS - 1);
}

// refresh map at every tick
void hMapRefresher(int signum)
{
	// draw ground
	g_iGround = (int)((double)LINES / 10 * 9);
	move(g_iGround, 0);
	hline('*', COLS);

	// refresh obstacles
	for(int i = 0; i < MAX_OBSTACLES; i++)
	{
		obs[i].row = g_iGround;
		switch(obs[i].type)
		{
			// vertical obstacle
			case 1:
			{
				if(obs[i].col > -1)
				{
					if(obs[i].col < COLS - 1)
						addObstacle(obs[i].type, obs[i].row, obs[i].col);
				}
				else
				{
					if(obs[i].col == -1)
					{
						move(obs[i].row - 2, 0);
						vline(' ', 2);
					}

					if(obs[i].col < -19)
                                                obs[i].col = COLS + (20 * (rand() % 5 + 1));
				}
				obs[i].col--;
				break;
			}
			// horizontal obstacle
			case 2:
			{
				if(obs[i].col > -1)
                                {
                                        if(obs[i].col < COLS - 1)
                                                addObstacle(obs[i].type, obs[i].row, obs[i].col);
                                }
				else
				{
					if(obs[i].col > -3)
						mvaddch(obs[i].row - 3, obs[i].col + 2, ' ');
					if(obs[i].col < -19)
                                                obs[i].col = COLS + (20 * (rand() % 5 + 1));
				}
				obs[i].col--;
				break;
			}
			default: break;
		}
	}

	move(LINES - 1, COLS - 1);
}
