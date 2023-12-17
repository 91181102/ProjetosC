// Classe Size

typedef struct size{
	int Width;
	int Height;
}_SIZE;

_SIZE *new_size(int width, int height){
	_SIZE *a = malloc(sizeof(_SIZE));
	a->Width = width;
	a->Height = height;
	return a;
}

