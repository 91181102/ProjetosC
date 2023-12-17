// Classe Label{

typedef struct _Label{
	string Name;
	LOCATION *Location;
	string Text;
	int ForeColor;
	int BackColor;
	char *text;
} Label;


// Declaração de Lista de Label.
typedef struct LIST_OF_LABEL{
	Label *item;
	struct LIST_OF_LABEL *next;
}List_Of_Label;


void setVisible(Label *component);
Label *new_Label();
Label *new_label(string name, string Text, int X, int Y, int ForeColor, int BackColor);

void setLabelVisible(Label *component){	
	textbackground(component->BackColor);
	textcolor(component->ForeColor);
	gotoxy(component->Location->X, component->Location->Y);
	printf("%s", component->Text);
}

Label *new_Label(string name){	
	Label *a = malloc(sizeof(Label));
	a->BackColor = Color.Black;
	a->ForeColor = Color.White;
	a->Location = setLocation(1, 1);
	a->Text = "Label1";
	a->Name = name;
	return a;
}

Label *new_label(string name, string Text, int X, int Y, int ForeColor, int BackColor){	
	Label *a = malloc(sizeof(Label));
	a->BackColor = BackColor;
	a->ForeColor = ForeColor;
	a->Location = setLocation(X, Y);
	a->Text = Text;
	a->Name = name;	
	return a;
}


//----------------------
// Operações com listas.
//----------------------
List_Of_Label *new_List_Of_Label(){
	List_Of_Label *List = (List_Of_Label *) malloc(sizeof(List_Of_Label));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_Label(List_Of_Label *List){
	free(List);
}

// Adiciona um Label numa lista.
void AddLabelIn(List_Of_Label *p, Label *label){
	List_Of_Label *new_item = malloc(sizeof(List_Of_Label));	
		
	new_item->item = label;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddLabelIn(p->next, label);
	}	
}

// Posiciona na tela todos os labels da lista.
void Show_Label_From(List_Of_Label *p){
	List_Of_Label *temp = p;
	
	while(temp->next != NULL){	
		setLabelVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_Label(List_Of_Label *p){
	int i = 0;
	List_Of_Label *temp = p;
	
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


// }
