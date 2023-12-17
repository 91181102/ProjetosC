
typedef struct _Location{
	int X;
	int Y;
}LOCATION;

LOCATION *setLocation(int x, int y);
LOCATION *newLocation(int x, int y);

LOCATION *Position;
LOCATION *InitPosition;

LOCATION *setLocation(int x, int y){
	LOCATION *l = malloc(sizeof(LOCATION));
	l->X = x;
	l->Y = y;
	return l;
}

LOCATION *newLocation(int x, int y){
	LOCATION *l = malloc(sizeof(LOCATION));
	l->X = x;
	l->Y = y;
	return l;
}


