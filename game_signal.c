/*
 * file : game_signal.c
 * description : 타이머 설정 및 시그널 핸들러 함수 구현
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "character.h"

int set_ticker(int);
void alarm_handler(int);

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

void hMapRefresher(int);
void move_character();

void alarm_handler(int signum)
{
	signal(SIGALRM, SIG_IGN);
	initscr();
	hMapRefresher(signum);
	refresh();

	move_character();
	signal(SIGALRM, alarm_handler);
}

