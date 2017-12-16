#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include "character.h"
#include "game_signal.h"

void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
void ctrl_c_handler(int);

int main()
{
	int c;
	
	tty_mode(0);
	set_cr_noecho_mode();
	set_nodelay_mode();
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);

	init_character_info();
	initscr();
	clear();
	refresh();

	set_ticker(300);
	signal(SIGALRM, move_character);

	while(( c = getchar()) != 'Q')
	{
		usleep(1000000);
		
		switch(c)
		{
			case ' ':
				characterInfo.state = JUMPING;
				break;
			case 'z':
				characterInfo.state = SLIDING;
				break;
		}
	}
	tty_mode(1);
}

void ctrl_c_handler(int signum)
{
	tty_mode(1);
	exit(1);
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
