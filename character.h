#define STANDING 0
#define JUMPING 1
#define SLIDING 2

#define JUMP_DISTANCE 5

typedef struct _characterInfo
{
	
	char character[3][3];
	int  ypos;
	int state;
}CharacterInfo;

CharacterInfo characterInfo;

void show_character();
void move_character();
void init_character_info();
