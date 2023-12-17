typedef struct _Bounds{
	int up;
	int left;
	int width;
	int height;
}BOUNDS;

BOUNDS *new_Bounds();

BOUNDS *new_Bounds(int up, int left, int width; int height){
	BOUNDS *b = malloc(sizeof(BOUNDS));
	b->up = up;
	b->left = left;
	b->width = width;
	b->height = height;
	return b;
}


