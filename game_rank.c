#include "rank.h"

user ranking[10];
extern int main();

void print_back_menu(void)
{
	int input;
	do{
		printf("back to manu(press '1')\n");
		printf("reset ranking(press '2') : ");
		scanf("%d",&input);
		switch(input)
		{
			case 1:main();
			break;
			case 2:reset_rank();
			break;
			default: 
			printf(" press '1' or '2' please \n");
		}
	}while(input!=1 || input!=2);
}

void print_rank(void)
{
	int i;
	for(i=0;i<10;i++)
	{
		if(ranking[i].name=="NULL")
			printf("%d. \n",i++);
		else
			printf(" %d. %s (%d) \n",i+1,ranking[i].name,ranking[i].score);
	}
	print_back_menu();
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
		ranking[i] = NULL;
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

