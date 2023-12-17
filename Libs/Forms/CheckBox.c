// Class CheckBox
#include <string.h>
//#include "conio2.h"

typedef struct CHECKBOX{
	string Name;
	int BackColor;
	int ForeColor;
	LOCATION *Location;
	int ActiveBackColor;
	int ActiveForeColor;		
	string Text;
	boolean Checked;
} CheckBox;

typedef struct LIST_OF_CHECKBOX{
	CheckBox *item;
	struct LIST_OF_CHECKBOX *next;
}List_Of_CheckBox;


CheckBox * new_CheckBox(string name){
	CheckBox *chk = malloc(sizeof(CheckBox));
	
	chk->BackColor = Color.Black;
	chk->ForeColor = Color.White;
	chk->ActiveBackColor = Color.Yellow;
	chk->ActiveForeColor = Color.Black;
	chk->Name = name;
	chk->Location = setLocation(1, 1);
	chk->Text = "CheckBox1";
	chk->Checked = false;
	
	return chk;
}

CheckBox *new_checkBox(string name, string Text, boolean checked, int BackColor, int ForeColor, int X, int Y){
	CheckBox *chk = new_CheckBox(name);
	
	chk->BackColor = BackColor;
	chk->ForeColor = ForeColor;
	chk->Location = setLocation(X, Y);
	chk->Text = Text;
	chk->Checked = checked;
	
	return chk;
}

void setCheckBoxVisible(CheckBox *chk){
	gotoxy(chk->Location->X, chk->Location->Y);
	textcolor(chk->ForeColor);
	textbackground(chk->BackColor);
	if (chk->Checked){
		printf("[X] %s", chk->Text);
	}else{
		printf("[ ] %s", chk->Text);
	}
}

void CheckBox_Focus(CheckBox *chk){
	gotoxy(chk->Location->X, chk->Location->Y);
	textbackground(chk->ActiveBackColor);
	textcolor(chk->ActiveForeColor);
	
	if (chk->Checked){		
		printf("[X] %s", chk->Text);		
	}else{		
		printf("[ ] %s", chk->Text);		
	}
	
	fflush(stdin);
	KeyEvents e;	
	
	while(e.KeyPressed != Keys.ENTER){
		fflush(stdin);
		e.KeyPressed = getKey();
		
		if(e.KeyPressed == Keys.SPACE){
			fflush(stdin);
			if(chk->Checked == true){
				chk->Checked = false;
				gotoxy(chk->Location->X, chk->Location->Y);
				printf("[ ] %s", chk->Text);
			}else{
				chk->Checked = true;
				gotoxy(chk->Location->X, chk->Location->Y);
				printf("[X] %s", chk->Text);
			}
		}
	}

	setCheckBoxVisible(chk);
}

//----------------------
// Operações com listas.
//----------------------
List_Of_CheckBox *new_List_Of_CheckBox(){
	List_Of_CheckBox *List = (List_Of_CheckBox *) malloc(sizeof(List_Of_CheckBox));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_CheckBox(List_Of_CheckBox *List){
	free(List);
}

// Adiciona um objeto na lista.
void AddCheckBoxIn(List_Of_CheckBox *p, CheckBox *object){
	List_Of_CheckBox *new_item = malloc(sizeof(List_Of_CheckBox));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddCheckBoxIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_CheckBox_From(List_Of_CheckBox *p){
	List_Of_CheckBox *temp = p;
	
	while(temp->next != NULL){	
		setCheckBoxVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_CheckBox(List_Of_CheckBox *p){
	int i = 0;
	
	List_Of_CheckBox *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


//
