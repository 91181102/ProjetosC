// Classe Libs.Data.HeaderCollumn
void HeaderColumn_setVisible();
	
typedef struct HEADER_COLUMN{
	string Name; // Define o nome da coluna.
	string Text; // Define o texto que aparece na coluna.
	int ForeColor; // Define a cor da fonte.
	int BackColor;	// Define a cor do fundo do texto.
	int Align; // Define o alinhamento da coluna.
	int Index; // Define o índice da coluna.
	int Width; // Define a quantidade de caracteres na coluna.
	int Type; // Define o tipo de dado armazenado na coluna.

} HeaderColumn;

HeaderColumn *GLOBAL_HeaderColumn;

HeaderColumn *new_HeaderColumn(string Name){
	HeaderColumn *object = malloc(sizeof(HeaderColumn));
	
	object->Name = Name;
	object->Text = Name;
	object->ForeColor = Color.Black;
	object->BackColor = Color.Gray;
	object->Align = Align.Left;
	object->Type = TypeOf.Int;
	object->Width = 10;
	
	return object;
}

/* Exibe o cabeçalho da tabela. */
void showHeader(){
	// Define as cores de fonte e fundo
	textcolor(GLOBAL_HeaderColumn->ForeColor);
	textbackground(GLOBAL_HeaderColumn->BackColor);
	// Posiciona o texto nas coordenadas X e Y.
	gotoxy(Position->X, Position->Y);
	putchar(179);
	printf("%s", GLOBAL_HeaderColumn->Text);
	// Conta os caracteres do cabeçalho.
	int lenght = strlen(GLOBAL_HeaderColumn->Text);	
	//Completa com espaços.
	if(lenght < GLOBAL_HeaderColumn->Width){
		strings(GLOBAL_HeaderColumn->Width - lenght, 32);
		putchar(179);
	}
	// Posiciona o texto na próxima coluna.
	Position->X += GLOBAL_HeaderColumn->Width;
}

//
