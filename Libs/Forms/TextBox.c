// Class TextBox{

typedef struct Textbox{
	string Name;
	int BackColor;
	int ForeColor;
	int ActiveBackColor;
	int ActiveForeColor;
	int Length;
	LOCATION *Location;
	int Width;
	string Text;	
}TextBox;

// Declaração de Lista de Label.
typedef struct LIST_OF_TEXTBOX{
	TextBox *item;
	struct LIST_OF_TEXTBOX *next;
}List_Of_TextBox;

TextBox *new_TextBox(string name){
	TextBox *txt = malloc(sizeof(TextBox));
	txt->BackColor = Color.WaterGreen;
	txt->ForeColor = Color.Blue;
	txt->ActiveBackColor = Color.Yellow;
	txt->ActiveForeColor = Color.Black;
	txt->Location = setLocation(1, 1);
	txt->Width = 10;
	txt->Length = 10;
	txt->Text = "TextBox1";
	txt->Name = name;	
	return txt;
}

TextBox *new_textBox(string name, int BackColor, int ForeColor, int X, int Y, int width, int length){
	TextBox *txt = malloc(sizeof(TextBox));
	txt->Name = name;
	txt->BackColor = BackColor;
	txt->ForeColor = ForeColor;
	txt->ActiveBackColor = Color.Yellow;
	txt->ActiveForeColor = Color.Black;
	txt->Length = length;
	txt->Width = width;
	txt->Text = " ";
	txt->Location = setLocation(X, Y);	
	return txt;
}

void TextBox_set_Text(TextBox *txt, char text[]){
	
}

void TextBox_setText(TextBox *txt, string Text){
	txt->Text = Text;
}

void TextBox_setColor(TextBox *txt, int BackColor, int ForeColor){
	txt->BackColor = BackColor;
	txt->ForeColor = ForeColor;
}

void TextBox_setLocation(TextBox *txt, int X, int Y){
	txt->Location = setLocation(X, Y);
}

void TextBox_setWidth(TextBox *txt, int width){
	txt->Width = width;
}

void TextBox_setLength(TextBox *txt, int length){
	txt->Length = length;
}


void setTextBoxVisible(TextBox *txt){
	gotoxy(txt->Location->X, txt->Location->Y);
	textbackground(txt->BackColor);
	textcolor(txt->ForeColor);
	strings(txt->Width, 32);
	gotoxy(txt->Location->X, txt->Location->Y);
	printf("%s", txt->Text);
}

void TextBox_Focus(TextBox *txt){
	gotoxy(txt->Location->X, txt->Location->Y);
	textbackground(txt->ActiveBackColor);
	textcolor(txt->ActiveForeColor);
	strings(txt->Width, 32);
	gotoxy(txt->Location->X, txt->Location->Y);
	printf("%s", txt->Text);
	
	KeyEvents e; e.KeyPressed = getKey();
	
	if(e.KeyPressed == Keys.ESC || e.KeyPressed == Keys.DEL || e.KeyPressed == Keys.BACK_SPACE){
		fflush(stdin);
		gotoxy(txt->Location->X, txt->Location->Y);
		strings(txt->Width, 32);
		gotoxy(txt->Location->X, txt->Location->Y);
		txt->Text = getChar();
	}
		
	setTextBoxVisible(txt);
}





//----------------------
// Operações com listas.
//----------------------
List_Of_TextBox *new_List_Of_TextBox(){
	List_Of_TextBox *List = (List_Of_TextBox *) malloc(sizeof(List_Of_TextBox));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_TextBox(List_Of_TextBox *List){
	free(List);
}

// Adiciona um Label numa lista.
void AddTextBoxIn(List_Of_TextBox *p, TextBox *textBox){
	List_Of_TextBox *new_item = malloc(sizeof(List_Of_TextBox));	
		
	new_item->item = textBox;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddTextBoxIn(p->next, textBox);
	}	
}

// Posiciona na tela todos os labels da lista.
void Show_TextBox_From(List_Of_TextBox *p){
	List_Of_TextBox *temp = p;
	
	while(temp->next != NULL){	
		setTextBoxVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_TextBox(List_Of_TextBox *p){
	int i = 0;
	
	List_Of_TextBox *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}



// }
