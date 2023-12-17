// Classe Libs.Data.Colluns

string getValue();
void setValue(string Value);
void showHeader();

typedef struct COLLUMNS{
	HeaderColumn *Header; // Define o cabeçalho da coluna.	
	string Value; // Define o valor da coluna.	
	string (*getValue)();
	void (*setValue)(string Value);
	void (*showHeader)(void);
}Columns;

Columns *GLOBAL_Column;


typedef struct LIST_OF_COLUMNS{
	int Count;	
	Columns *item;
	struct LIST_OF_COLUMNS *next;
}List_Of_Columns;


bool Columns_hasNext(List_Of_Columns *temp);

/* Cria uma nova coluna. */
Columns *new_Columns(HeaderColumn *Header, string Value){
	Columns *object = malloc(sizeof(Columns));
	
	object->Header = Header;	
	object->Value = Value;
	object->getValue = getValue;
	object->setValue = setValue;
	object->showHeader = showHeader;
	
	return object;
}


/* Obtém a coluna. */
Columns *getColumn(Columns *object){
	GLOBAL_Column = object;
	GLOBAL_HeaderColumn = object->Header;
	return GLOBAL_Column;
}


/* Cria uma nova lista de colunas. */
List_Of_Columns *new_List_Of_Columns(){
	List_Of_Columns *List = (List_Of_Columns *) malloc(sizeof(List_Of_Columns));
	List->Count = 0;
	List->item = NULL;
	List->next = NULL;
	return List;
}

/* Obtém o valor armazenado na coluna. */
string getValue(){
	return GLOBAL_Column->Value;
}

/* Altera o valor de uma coluna. */
void setValue(string Value){
	GLOBAL_Column->Value = Value;
}

/* Adiciona uma coluna na lista. */
void AddColumnIn(List_Of_Columns *p, Columns *object){
	List_Of_Columns *new_item = malloc(sizeof(List_Of_Columns));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddColumnIn(p->next, object);
	}
}

/* Exibe a coluna na tabela */
void ColumnSetVisible(Columns *object){
	// Posiciona o texto nas coordenadas X e Y.
	gotoxy(Position->X, Position->Y);
	// Imprime a moldura.
	putchar(179);
	printf("%s", object->Value);
	// Conta os caracteres do cabeçalho.
	int lenght = strlen(object->Value);
	//Completa com espaços.
	if(lenght < object->Header->Width){
		// Imprime o conteúdo.
		strings(object->Header->Width - lenght, 32);
		// Imprime a moldura.
		putchar(179);	
	}
	Position->X += object->Header->Width;
}



/* Exibe o cabeçalho da coluna. */
void ColumnHeader_setVisible(Columns *object){
	GLOBAL_HeaderColumn = object->Header;
	
	object->showHeader();
}

/* Exibe todas as colunas da lista */
void ShowColumnsFrom(List_Of_Columns *p){
	List_Of_Columns *temp = p;
	
	Position->X = InitPosition->X;
	Position->Y += 1;
	
	while(Columns_hasNext(temp)){
		ColumnSetVisible(temp->next->item);
		temp = temp->next;		
	}
}




/* Verifica se há mais colunas na lista. */
bool Columns_hasNext(List_Of_Columns *temp){
	if (temp->next != NULL)
		return true;
	else
	 	return false;
}

/* Obtém uma coluna pelo seu índice */
Columns *getColumnByIndex(List_Of_Columns *Cells, int Index){
	List_Of_Columns *temp = Cells;
	int Count = 0;
	
	while(Columns_hasNext(temp)){
		if (Count == Index){
			GLOBAL_Column = temp->next->item;
			return GLOBAL_Column;
		}
		
		temp = temp->next;
		Count++;		
	}
	GLOBAL_Column = new_Columns(new_HeaderColumn("Column1"), "0");
	return GLOBAL_Column;
}

/* Obtém uma coluna pelo seu nome */
Columns *getColumnByName(List_Of_Columns *Cells, string Name){
	List_Of_Columns *temp = Cells;	
	
	while(Columns_hasNext(temp)){
		if (temp->next->item->Header->Name == Name){
			GLOBAL_Column = temp->next->item;
			return GLOBAL_Column;
		}
		
		temp = temp->next;		
	}
	GLOBAL_Column = new_Columns(new_HeaderColumn("Column1"), "0");
	return GLOBAL_Column;
}


//
