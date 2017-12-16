#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "rank.h"

int rankLen;
void print_back_menu(void)
{
	char  input;
	clear();
	do{
		move(10,10);
		addstr("back to manu(press '1')");
		refresh();

		input = getch();
	}while(input != '1');
}

void print_rank(void)
{
	int i;
	int result;
	clear();
	for(i=0;i<10;i++)
	{
		if(ranking[i].name=="NULL")
		{
			move(10+i, 10);
			if(i+'0' == ':')
				addstr("10");
			else
				addch(i+'0');
			addch('.');
		}
		else
		{
			move(10+i, 10);
			addch(' ');
			if(i+'0'+1 == ':')
				addstr("10");
			else
				addch(i+'0'+1);
			addstr(". ");
			addstr(ranking[i].name);
			addstr(" (");
			addch(ranking[i].score/100 + '0');
			addch(ranking[i].score%100/10 + '0');
			addch(ranking[i].score%10 + '0');
			addstr(") ");
			refresh();
			//addstr(" %d. %s (%d) \n",i+1,ranking[i].name,ranking[i].score);
		}
		
	}
	sleep(2);
	print_back_menu();
	return;
}

void set_rank(user person)
{
	int i;
	int cnt=0;
	for(i=0;i<10;i++)
	{
		if(person.score <= ranking[i].score)
		{
			cnt++;
		}
	}
		person.rank = cnt;
		ranking[cnt] = person;
}

void reset_rank()
{
	int i;
	for(i=0;i<10;i++)
	{
		memset(ranking[i].name, 0, sizeof(ranking[i].name));
		ranking[i].score = 0;
	}
}

void swap(user * u1, user * u2)
{
	user temp = *u1;
	*u1 = *u2;
	*u2 = temp;	
}

void bsort(int len)
{
	int i, j;
	for(i=0; i<len-1; i++)
		for(j=0; j<len-1-i; j++)
			if(ranking[j].score < ranking[j+1].score)
				swap(&ranking[j], &ranking[j+1]);
}
void save_rank()
{
	int i;
	FILE *f1;
	
	f1 = fopen("user_rank.txt", "w");
	bsort(11);
	for(i=0; i<rankLen; i++)
	{
		fprintf(f1,"%d %s %d\n", i+1, ranking[i].name, ranking[i].score);
	}
	fclose(f1);
}

void load_rank()
{
	int i;
	FILE *f1;
	f1 = fopen("user_rank.txt","r");

	for(i=0;i<10;i++)
	{
		if(feof(f1))
			break;
		fscanf(f1, "%d %s %d",&ranking[i].rank,ranking[i].name,&ranking[i].score);
		rankLen++;
	}
	bsort(10);
	fclose(f1);
}

