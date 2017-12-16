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

void tty_mode(int);
void set_cr_noecho_mode();
void set_nodelay_mode();
void ctrl_c_handler(int);
void input_handler(int);
void setup_aio_buffer();

struct aiocb kbcbuf;
int done = 0;
int main()
{
	int c;
	
	tty_mode(0);
	set_cr_noecho_mode();
	set_nodelay_mode();

	init_character_info();
	initscr();
	clear();
	refresh();

	signal(SIGINT, ctrl_c_handler);

	signal(SIGIO, input_handler);
	setup_aio_buffer();
	aio_read(&kbcbuf);


	signal(SIGALRM, move_character);
	set_ticker(100);

	while(!done)
		pause();

	tty_mode(1);
	endwin();
}

void input_handler(int snum)
{
	int c;
	char * cp = (char *)kbcbuf.aio_buf;

	if(aio_error(&kbcbuf) == 0)	
		if(aio_return(&kbcbuf) == 1)
		{
			c = *cp;
			if(c == 'Q' || c == EOF)
				done = 1;
			else if(c == ' ')
				characterInfo.state = JUMPING;
			else if(c == 'z')
				characterInfo.state = SLIDING;
		}
	aio_read(&kbcbuf);
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

void setup_aio_buffer()
{
	static char input[1];

	kbcbuf.aio_fildes = 0;
	kbcbuf.aio_buf = input;
	kbcbuf.aio_nbytes = 1;
	kbcbuf.aio_offset = 0;

	kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	kbcbuf.aio_sigevent.sigev_signo = SIGIO;
}
