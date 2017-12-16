#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include "game_map.h"


void restoreScreen();

int main()
{
	char cInput;

	initScreen();
	while((cInput = getchar()) != 'Q')
	{
		;
	}

	restoreScreen();
}
