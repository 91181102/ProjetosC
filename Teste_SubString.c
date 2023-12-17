#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *subString(char text[], int start, int width);
void SubString(char text[], int start, int width);
	
int main (){
	char hoje[] = "20180204"; 

	//subString(hoje, 6, 2);
	//subString(hoje, 4, 2);
	//subString(hoje, 0, 4);

	printf("\n%s/%s/%s \n", subString(hoje, 6, 2), subString(hoje, 4, 2), subString(hoje, 0, 4));
	
	printf("\n");
	system("pause");		
	return 0;
}  

char *subString(char text[], int start, int width){
	int size = strlen(text);
    char parte[width];
    memcpy(parte, &text[start], width);
    parte[width] = '\0';
    char *msg = (char*) malloc((size+1) * sizeof(char));
    strncpy(msg, parte, width+1);
    return msg;
}

void SubString(char text[], int start, int width){
	int size = strlen(text);
    char parte[width];    
    memcpy(parte, &text[start], width);
    parte[width] = '\0';
    printf("%s", parte);
}


