#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

typedef struct user
{
	char name[20];
	int score;
	int rank;
}user;

user ranking[11];
user recent;
void print_back_menu();
void print_rank();
void set_rank(user);
void reset_rank();
void save_rank();
void load_rank();
