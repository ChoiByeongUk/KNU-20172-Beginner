#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
#include <signal.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include "character.h"
#include "game_signal.h"
#include "game_map.h"

void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
char print_menu();
void game_start();
void print_rank();

int done = 0;
extern struct aiocb kbcbuf;
int main()
{
	int c;
	char select;
	int mode=2; //기본
	tty_mode(0);
	set_cr_noecho_mode();
	initscr();
	clear();
	refresh();
	while(1){
		select = print_menu();

		initScreen();
		switch(select)
		{
			case '1':
				game_start();
				break;
			case '2':
				mode=selectMode(mode);
				break;
			case '3':
				print_rank();
				break;
			case '4':
				print_help_key();
				break;
			case '5':
				endwin();
				tty_mode(1);
				
				exit(1);
		}
	}
}

void tty_mode(int how)
{
	static struct termios original_mode;
	static int original_flags;
	
	if(how == 0)
	{
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
	}
	else if(how == 1)
	{
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}

void set_cr_noecho_mode()
{
	struct termios ttystate;

	tcgetattr(0, &ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodelay_mode()
{
	int termflags;

	termflags = fcntl(0, F_GETFL);
	termflags |= O_NDELAY;
	fcntl(0, F_SETFL, termflags);
}

