#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void MsgBox(char texto[50]);
bool msgbox_btnOk();
bool msgBox_btnCancel();

/* exibe uma mensagem no centro da tela */
void MsgBox(char texto[]){ 
	Form *msgbox = new_Form();
	Button *btnOk = new_Button(SET(Ok));
	btnOk->OnKeyEnter = msgbox_btnOk;
		
	int x = (80/2) - strlen(texto)/2;
	int y = (24/2);
	
	msgbox->Location = setLocation(x, y);
	msgbox->Size = new_size((strlen(texto) + 8), 6);		
	
	btnOk->ForeColor = Color.Yellow;
	btnOk->BackColor = Color.Red;
	btnOk->Size = new_size(6, 3);
	btnOk->Location = setLocation(2 + strlen(texto)/2, msgbox->Size->Height + 4);
	
	msgbox->AddButton(btnOk);
	
	Form_setColors(msgbox, Color.Yellow, Color.Red);
	Form_setForm(msgbox, "Aviso", true, Border.None, false);	
	
	Form_ShowForm(msgbox);
	gotoxy(x + 1, y + 1); printf("%s", texto); 
	//gotoxy((x-2) + strlen(texto)/2, y + 3); printf("[Tecle algo]"); 
	//getch();
	bool exit = Button_Focus(btnOk);
		
	Form_DisposeForm(msgbox);
}

void To_String(int a){
	char* string = (char *) malloc (30);
	
	string=itoa(a, string, 10);
	MsgBox(string);
	//sprintf(&texto, "%d", a);
	//return (str);
	printf("%d", a);
}


bool msgbox_btnOk(){
	return true;
}

bool msgbox_btnCancel(){
	return false;
}

