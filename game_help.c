#include"rank.h"
#include"game_main.c"


extern int main();

void print_help_key(void)
{
	char input;
	while(1)
	{
		printf("This game is running action game\n\
		your character going forward\n\
		So,you put the Key for survive your character\n\
		<Key>\n\
		Jump : z\n\
		Slide: x\n");
	}
	

}


void choice_help_menu(void)
{
	int input;
	while(1)
	{
		print_help_key();
		printf(" Back to main( press 'Q'): ");
		scanf("%d",&input);
		if(input=='Q'||input=='q')
			main();
	}
}

