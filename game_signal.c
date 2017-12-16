/*
 * file : game_signal.c
 * description : 타이머 설정 및 시그널 핸들러 함수 구현
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <sys/time.h>

char g_smap[100][100];


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
	//
	int i;
	int j;
	proceed_map();
	clear();
	for(i=0;i<LINES;i++)
	{
		
		for(j=0;j<COLS;j++){
			move(i,j);
			addch(g_smap[i][j]);
		}
	}
	refresh();

}

void init_map(){
	int i;
	int j;
	
	for(i=0; i<=COLS;i++){
		g_smap[0][i]='-';
		g_smap[LINES-1][i]='-';
		g_smap[LINES-2][i]='-';
		for(j=1;j<LINES-2;j++)
			g_smap[j][i]=' ';
	}
	srand((unsigned)time(NULL));
}	

void proceed_map(){
	int i;
	int j;
	int next_item;
	int next_position;
	char next_char;
	for(i=0;i<COLS;i++){
		for(j=0;j<LINES;j++){
			g_smap[j][i]=g_smap[j][i+1];
		}
	}
	if((next_item=rand()%4)==0){
		next_char = 'o'; //코인
	}
	else if(next_item==1){
		next_char = '='; //벽
	}
	else
		next_char=' ';
	
	next_position=rand()%3;
	
	if(next_position==0){
		next_position = LINES-3;
	}
	else if(next_position==1){
		next_position = LINES -5;
	}
	else{
		next_position = LINES-6;
	}
	
	for(i=1;i<LINES-1;i++)
	{	
		g_smap[i][COLS]=' ';
	}
	g_smap[0][COLS]='-';
	g_smap[LINES-1][COLS]='-';
	g_smap[LINES-2][COLS]='-';
	g_smap[next_position][COLS]=next_char;
}
