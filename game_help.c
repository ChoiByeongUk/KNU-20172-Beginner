#include"rank.h"
#include <curses.h>

void print_help_key(void)
{
	clear();
	move(10,5);
	addstr("This game is running action game");
	move(11,5);
	addstr("your character going forward");
	move(12,5);
	addstr("So,you put the Key for survive your character");
	move(14,7);
	addstr("<Key>");
	move(15,7);
	addstr("Jump : z");
	move(16,7);
	addstr("Slide: x");
	
	move(18,6);
	addstr("press any key back to the menu");

	getch();
	
	

}
