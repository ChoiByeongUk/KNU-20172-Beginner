/*
 * file : game_signal.c
 * description : 타이머 설정 및 시그널 핸들러 함수 구현
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <sys/time.h>

extern char** g_smap; 


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

void proceed(int signum)//각 시간초마다 맵움직임 및 처리호출 및 죽음확인
{
	//여기서 맵 갱신 호출
	//
	
}	
