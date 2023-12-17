
#include <stdio.h>
#include <stdlib.h>
#include "./Libs/Components.c"
#include "./Modulos/MenuPrincipal.c"

/*
#define foreach(type, array) do { \
        type it = array[0]; \
        int i; \]
		for(i = 0; i < array->Count+1; i++, it = array[i])
#define next  } while(0);

#define hasNext(type, array) do{ \
	type = array; \
	if (type->next != NULL) \
	return true; \
	else return false; \
	\
}

*/

char *subString(char text[], int start, int width);

int main (){
	InitializeComponents();
	setLocal();
	
	TelaMenuPrincipal = new_TelaMenuPrincipal();
	Form_ShowForm(TelaMenuPrincipal);
	Form_Dispose(TelaMenuPrincipal);
	
	
	char hoje[] = "20180204"; 
	//char data[10];
	//printf("%s/%s/%s \n", subString(hoje, 6, 2), subString(hoje, 4, 2), subString(hoje, 0, 4));
	
	
	//sprintf(data, "%s/%s/%s", subString(hoje, 6, 2), subString(hoje, 4, 2), subString(hoje, 0, 4));
	
	//printf("%s\n", ToDateShort(hoje));
		
	gotoxy(1,20);
	system("pause");		
	return 0;
} 
 

