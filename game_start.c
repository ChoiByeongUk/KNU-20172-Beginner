#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "game_signal.h"
#include "game_map.h"
void game_start(){
	
	clear();
	refresh();
	init_map();
	signal(SIGALRM,proceed);
	set_ticker(300);
	move(10,10);
	refresh();
	while(1){
		char c= getchar();
	}
	endwin();
}	

	
