/* file : game_main.c
 * description : 메인 기능 선택 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <aio.h>
#include <unistd.h>
#include "character.h"
#include "game_signal.h"
#define CHECK addch('o');

void game_start();
char print_menu();
void input_handler(int);
void ctrl_c_handler(int);
void setup_aio_buffer();
struct aiocb kbcbuf;
void tty_mode(int);
void set_nodelay_mode();
extern int done;
void alarm_handler(int);

void game_start()
{
	initscr();
	clear();
	refresh();

	signal(SIGINT, ctrl_c_handler);

	signal(SIGIO, input_handler);
	setup_aio_buffer();
	aio_read(&kbcbuf);
	
	init_character_info();
	signal(SIGALRM, alarm_handler);
	set_ticker(100);

	while(!done)
		pause();

	clear();
	endwin();
	tty_mode(1);
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
	clear();
	endwin();
	tty_mode(1);
	exit(1);
}

char print_menu(void){
	char menu;
	while(1){
		clear();
		move(5,4);
		addstr("ooo");
		move(6,4);
		CHECK
		move(6,7);
		CHECK
		move(7,4);
		addstr("ooo");
		move(8,4);
		CHECK
		move(8,7);
		CHECK
		move(9,4);
		CHECK
		move(9,8);
		CHECK
		
		// r 종료
	
		move(5,10);
		CHECK
		move(5,15);
		CHECK
		move(6,10);
		CHECK
		move(6,15);
		CHECK
		move(7,10);
		CHECK
		move(7,15);
		CHECK
		move(8,10);
		CHECK
		move(8,15);
		CHECK
		move(9,11);
		addstr("oooo");
		// u 

		move(5,17);
		CHECK
		move(6,17);
		CHECK
		move(7,17);
		CHECK
		move(8,17);
		CHECK	
		move(9,17);
		CHECK
		move(8,20);
		CHECK
		move(7,19);
		CHECK
		move(6,18);
		CHECK
		move(5,21);
		CHECK
		move(6,21);
		CHECK
		move(7,21);
		CHECK
		move(8,21);
		CHECK
		move(9,21);
		CHECK
		//n
		
		move(5,33);
		CHECK
		move(6,32);
		CHECK
		move(6,34);
		CHECK
		move(7,31);
		addstr("ooooo");
		move(8,30);
		CHECK
		move(8,36);
		CHECK
		move(9,29);
		CHECK
		move(9,37);
		CHECK
		
		//a
		//
	
		move(5,41);
		CHECK
		CHECK
		CHECK
		move(6,40);
		CHECK
		move(7,39);
		CHECK
		move(8,39);
		CHECK
		move(9,40);
		CHECK
		CHECK
		CHECK
		CHECK
		move(8,44);
		CHECK
		move(7,43);
		CHECK
		move(7,42);
		CHECK
		//g

		move(5,50);
		CHECK
		move(6,49);
		CHECK
		move(6,51);
		CHECK
		move(7,48);
		addstr("ooooo");
		move(8,47);
		CHECK
		move(8,53);
		CHECK
		move(9,46);
		CHECK
		move(9,54);
		CHECK
		//a
		
		move(5,57);
		addstr("ooo");
		move(6,58);
		CHECK
		move(7,58);
		CHECK
		move(8,58);
		CHECK
		move(9,57);
		addstr("ooo");
		//i
		//


		move(5,62);
		CHECK
		move(6,62);
		CHECK
		move(7,62);
		CHECK
		move(8,62);
		CHECK	
		move(9,62);
		CHECK
		move(8,65);
		CHECK
		move(7,64);
		CHECK
		move(6,63);
		CHECK
		move(5,66);
		CHECK
		move(6,66);
		CHECK
		move(7,66);
		CHECK
		move(8,66);
		CHECK
		move(9,66);
		CHECK


			
			
		move(13,27);
		addstr("1 : Game Start");
		move(15,27);
		addstr("2 : Select Mode");
		move(17,27);
		addstr("3 : See Rank");
		move(19,27);
		addstr("4 : Help");
		move(21,27);
		addstr("5 : Exit");
		refresh();
		move(16,10);
		menu=getchar();
		
		if(menu >= '1' && menu <= '5')
			return menu;

	}
	return 0;
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

