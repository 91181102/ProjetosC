// Class Button

void OnKeyEnter();
bool ButtonResult;

typedef struct BUTTONS{
	string Name;
	string Text;	
	_SIZE *Size;
	LOCATION *Location;
	int BackColor;
	int ForeColor;
	int KeyEvent;
	void (*OnKeyEnter)();
}Button;

typedef struct LIST_OF_BUTTON{
	Button *item;
	struct LIST_OF_BUTTON *previous;
	struct LIST_OF_BUTTON *next;
}List_Of_Button;

Button *GLOBAL_button;
List_Of_Button *GLOBAL_List_Of_Button;

Button *new_Button(string Name){	
	Button *a = malloc(sizeof(Button));
	
	a->Text = Name;
	a->Location = setLocation(1, 1);	
	a->Name = Name;
	a->BackColor = Color.White;
	a->ForeColor = Color.Black;	
	a->Size = new_size(strlen(Name) + 2, 3);
	a->KeyEvent = 0;
	a->OnKeyEnter = OnKeyEnter;
	return a;
}

// Cria um novo botão na memória.
Button *new_button(string Name, string Text, int BackColor, int ForeColor, int col, int lin, int width, int height){
	Button *a = new_Button(Name);
	
	a->BackColor = BackColor;
	a->ForeColor = ForeColor;
	a->Location->X = col;
	a->Location->Y = lin;
	a->Text = Text;
	
	if (strlen(Text) < width + 2){
		a->Size = new_size(strlen(Text) + 2, height);
	}else{
		a->Size = new_size(width, height);
	}
	
	a->Size = new_size(width, height);	
	
	return a;
}



// Evento da tecla ENTER pressionada.
void OnKeyEnter(){
	return;
}

// Exibe o comboBox na tela.
void Button_setVisible(Button *object){	
	Button_DrawFrame(object, false);
}

// Desenha a comboBox na tela.
void Button_DrawFrame(Button *a, bool isActive){
	int posX = a->Location->X;
	int posY = a->Location->Y + 1;
	int xCol = posX;
	int xLin = posY;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	textcolor(a->ForeColor);
	textbackground(a->BackColor);
	
	int i = 0, j = 0;		
		
	//Valores default para borda.	
	int Left_Up = 218;
	int Horizon = 196;
	int Vertical = 179;
	int Right_Up = 191;
	int Left_Down = 192;
	int Right_Down = 217;
	int Middle_Left = 195;
	int Middle_Right = 180;
	
	if (isActive){
		Left_Up = 201;
		Horizon = 205;
		Vertical = 186;
		Right_Up = 187;
		Left_Down = 200;
		Right_Down = 188;
		Middle_Left = 204;
		Middle_Right = 185;	
	}
	
	// Desenha a parte superior da borda	
	gotoxy(posX, posY);
	putchar(Left_Up);
	strings(larg - 1, Horizon);	
	putchar(Right_Up);
    gotoxy(posX + 1, posY);
	
	// Desenha as laterais da borda	
	for (i=2; i<alt; i++) {
        gotoxy(posX , posY + (i-1));
		putchar(Vertical);
		strings(larg - 1, ' ');
		gotoxy(posX + (larg - 1), posY + (i-1));
        putchar(Vertical); printf("\n");
	}
	
	// Desenha a parte inferior da borda.
	gotoxy(posX, posY + (i - 1));
	putchar(Left_Down);
	for (j=1; j<=larg-2; j++)
		putchar(Horizon);
	putchar(Right_Down);
	
	// Escreve o texto.
	int col = strlen(a->Text) - (a->Size->Width/2);
	
	gotoxy(a->Location->X + 2, a->Location->Y + 2);
	
		
	printf("%s", a->Text); 
}


bool Button_Focus(Button *object){
	Button_DrawFrame(object, true);
	ButtonResult = false;
	
	object->KeyEvent = getKey();
	
	if(object->KeyEvent == Keys.ENTER){
		Button_LostFocus(object);
		object->OnKeyEnter(); 
		return ButtonResult;
	}
	if(object->KeyEvent == Keys.ESC){
		Button_LostFocus(object);
		return true;
	}
	
	Button_LostFocus(object);
	return false;
}

void Button_LostFocus(Button *object){
	Button_DrawFrame(object, false);
}

//----------------------
// Operações com listas.
//----------------------

List_Of_Button *new_List_Of_Button(){
	List_Of_Button *List = (List_Of_Button *) malloc(sizeof(List_Of_Button));
	List->item = NULL;
	List->previous = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_Button(List_Of_Button *object){
	free(object);
}

// Adiciona um objeto na lista.
void AddButtonIn(List_Of_Button *p, Button *object){
	List_Of_Button *new_item = malloc(sizeof(List_Of_Button));
	
		
	new_item->item = object;	
	new_item->next = NULL;
	new_item->previous = p;
		
	if (p->next == NULL){
		p->previous = new_item->previous;
		p->next = new_item;		
	} else{
		AddButtonIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_Button_From(List_Of_Button *p){
	List_Of_Button *temp = p;
	
	while(temp->next != NULL){	
		Button_setVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_Button(List_Of_Button *p){
	int i = 0;
	
	List_Of_Button *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}

