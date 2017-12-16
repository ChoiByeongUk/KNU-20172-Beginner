/*
 * file : game_signal.c
 * description : 타이머 설정 및 시그널 핸들러 함수 구현
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "character.h"
#include "game_map.h"
#include "rank.h"

int set_ticker(int);
void alarm_handler(int);
extern int done;
int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec,n_usecs;
	
	n_sec = n_msecs/1000;
	n_usecs = (n_msecs % 1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset,NULL);
}

void tty_mode(int);
void set_cr_noecho_mode();
void hCharacterRefresher();
void hMapRefresher(int);
int collision_check();
extern int end, start;
extern int rankLen;

void alarm_handler(int signum)
{
	char name[30];
	signal(SIGALRM, SIG_IGN);

	initscr();

	if(collision_check())
	{
		mvaddstr(LINES / 2, COLS / 2, "Game Over");
		end = time(NULL);
		mvaddstr(LINES / 2 + 1, COLS / 2 - 6, "Score : ");
	        mvaddch(LINES / 2 + 1, COLS / 2 + 2, (end-start) / 100 + '0');
	        mvaddch(LINES / 2 + 1, COLS / 2 + 3, (end-start) % 100 / 10 +'0');
	        mvaddch(LINES / 2 + 1, COLS / 2 + 4, (end-start) % 10 + '0');
		move(LINES, COLS);


		tty_mode(1);

		move(LINES-1, 5);
		addstr("Your name : ");
		refresh();
		move(LINES-1, 15);
		scanf("%s", name);
	
		set_cr_noecho_mode();
		//set_nodelay_mode();
		strcpy(recent.name, name);
		recent.score = end - start;
		recent.rank = -1;
	
		rankLen++;
		ranking[10] = recent;	
		save_rank();	
		endwin();
		tty_mode(1);
		exit(0);
	}

	hCharacterRefresher();
	hMapRefresher(signum);
	end = time(NULL);
	mvaddch(2, COLS - 10, (end-start) / 100 + '0');
	mvaddch(2, COLS - 9, (end-start) % 100 / 10 +'0');
	mvaddch(2, COLS - 8, (end-start) % 10 + '0');
	move(LINES - 1, COLS - 1);
	refresh();

	
	signal(SIGALRM, alarm_handler);
}

int collision_check()
{
	for(int i = 0; i < MAX_OBSTACLES; i++)
	{
		if(character.state == STANDING)
		{
			if(abs(obs[i].col - character.col) < 2)
				return 1;
		}
		else if(character.state == JUMPING || character.state == FALLING)
		{
			if(abs(character.row - obs[i].row) < 4 && abs(obs[i].col - character.col) < 2)
				return 1;
		}
		else if(character.state == SLIDING)
		{
			if(obs[i].type == 1 && abs(obs[i].col - character.col) < 2)
				return 1;
		}
	}
	return 0;
}
