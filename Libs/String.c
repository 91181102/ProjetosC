#include <stdio.h>

typedef struct STRING *string;

typedef struct _STRING{
	string *value;
	int len;
}String;
//string *getChar();


// printa na tela uma quantidade "n" do mesmo caractere
void strings(int quant, char caractere){	
	int i;
	for (i=1;i<quant;i++)
		printf("%c", caractere);
}

// Obtém um texto via teclado.
string *getChar(){
	string texto;
	fflush(stdin);
	texto = gets(malloc(100));
	return texto;
}

// Obtém uma subString a partir do índice de um caractere.
char *subString(char text[], int start, int width){
	int size = strlen(text);
    char parte[width];
    memcpy(parte, &text[start], width);
    parte[width] = '\0';
    char *msg = (char*) malloc((size+1) * sizeof(char));
    strncpy(msg, parte, width + 1);
    return msg;
}


