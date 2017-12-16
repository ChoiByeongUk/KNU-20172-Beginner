#include <stdio.h>
#include <curses.h>


int selectMode(int mode){
	char c;
	clear();
	
	move(5,5);
	addstr("select your game mode");
	move(6,5);
	addstr("Current mode is ");
	if(mode==1)
		addstr("Easy");
	else if(mode==2)
		addstr("Normal");
	else
		addstr("Hard");
	
	move(8,5);
	addstr(" 1. Easy mode");
	move(10,5);
	addstr(" 2. Normal mode");
	move(12,5);
	addstr(" 3. Hard mode");
	refresh();
	while(1){
		c= getchar();
		if(c=='1'||c=='2'||c=='3')
			break;
	}
	return c-'0';
}
