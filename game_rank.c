#include <curses.h>
#include <stdio.h>
#include "rank.h"
user ranking[10];

void print_back_menu(void)
{
	char  input;
	clear();
	do{
		move(10,10);
		addstr("back to manu(press '1')");
		move(11,10);
		addstr("reset ranking(press '2') : ");
		refresh();

		input = getch();
		switch(input)
		{
			case '1':
				return;
			case '2':
				reset_rank();
				clear();
				move(10,10);
				addstr("reset completed");
				refresh();
				return;
			default: 
				clear();
				move(10,10);
				addstr(" press '1' or '2' please ");
				refresh();
		}
	}while(input != '1' || input != '2');
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
			addch(i+'0');
			addch('.');
		}
		else
		{
			move(10+i, 10);
			addch(' ');
			addch(i+'0'+1);
			addstr(". ");
			addstr(ranking[i].name);
			addstr(" (");
			addch(ranking[i].score + '0');
			addstr(" ) ");
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

void save_rank()
{
	int i;
	FILE *f1;
	f1 = fopen("user_rank.txt","w");
	for(i=0;i<10;i++)
	{
		fprintf("%d. %s %d\n",i+1,ranking[i].name,ranking[i].score);
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
		fscanf("%d. %s %d",&ranking[i].rank,ranking[i].name,&ranking[i].score);
	}
}

