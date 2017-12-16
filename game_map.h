#define MAX_OBSTACLES 15

typedef struct obstacle
{
	int type, row, col;
} obstacle;
obstacle obs[MAX_OBSTACLES];

int g_iMaxRow, g_iMaxCol;
int g_iGround;
