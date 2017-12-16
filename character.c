#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "character.h"

extern int g_iGround;

void initCharacter()
{
	character.state = 1;
	character.row = g_iGround - 1;
	character.col = 5;
}

void hCharacterRefresher()
{
	switch(character.state)
	{
		case STANDING:
		{
			mvaddstr(character.row - 2, character.col, " O ");
			mvaddstr(character.row - 1, character.col, "/|\\");
			mvaddstr(character.row, character.col, "/ \\");
			break;
		}
		case JUMPING:
		{
			if(character.row > g_iGround - 6)
			{
				character.row--;
				mvaddstr(character.row - 2, character.col, " O ");
	                        mvaddstr(character.row - 1, character.col, "/|\\");
        	                mvaddstr(character.row, character.col, "/ \\");
				mvaddstr(character.row + 1, character.col, "   ");
			}
			else
				character.state = FALLING;
			break;
		}
		case SLIDING:
		{
			mvaddstr(character.row - 2, character.col, "   ");
			mvaddstr(character.row - 1, character.col, "   ");
			mvaddstr(character.row, character.col, "--O");
			break;
		}
		case FALLING:
		{
			if(character.row < g_iGround - 1)
                        {
                                character.row++;
                                mvaddstr(character.row - 2, character.col, " O ");
                                mvaddstr(character.row - 1, character.col, "/|\\");
                                mvaddstr(character.row, character.col, "/ \\");
                                mvaddstr(character.row - 3, character.col, "   ");
                        }
                        else
			{
				mvaddstr(character.row - 3, character.col, "   ");
				character.state = STANDING;
			}
			break;
		}
	}
	move(LINES - 1, COLS - 1);
}
