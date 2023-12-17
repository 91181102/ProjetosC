// Clsse padding


typedef struct PADDING{
	int Left;
	int Top;
	int Right;
	int Bottom;
}padding;

padding *setPadding(int Left, int Top, int Right, int Bottom){
	padding *object;
	
	object->Left = Left;
	object->Top = Top;
	object->Right = Right;
	object->Bottom = Bottom;
	
	return object;
}


//
