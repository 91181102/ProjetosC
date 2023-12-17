// Classe Libs.Data.Table
void AddRow(Rows *object);
void Table_setVisible();
	
typedef struct TABLE{
	string Name;
	int ColumnCount;
	int CellForeColor;
	int CellBackColor;
	bool HeaderRow;
	List_Of_Rows *Rows;
	LOCATION *Location;
	_SIZE *Size;
	void (*AddRow)(Rows *object);
	void (*Table_setVisible)(void);
} Table;

Table *GLOBAL_Table;

/* Cria uma nova tabela. */
Table *new_Table(){
	Table *object = malloc(sizeof(Table));
	object->ColumnCount = 0;
	object->HeaderRow = true;
	object->Rows = new_List_Of_Rows();
	object->Location = setLocation(1,1);
	object->Size = new_size(20,20);
	object->AddRow = AddRow;
	object->Table_setVisible = Table_setVisible;	
	object->CellBackColor = Color.Red;
	object->CellForeColor = Color.Yellow;
	
	GLOBAL_Table = object;
		
	return object;
}

/* Adiciona uma nova linha na tabela. */
void AddRow(Rows *object){
	GLOBAL_Table->Rows->Count += 1;
	AddRowIn(GLOBAL_Table->Rows, object);
}

/* Obtém a tabela. */
Table *getTable(Table *object){
	GLOBAL_Table = object;
	return GLOBAL_Table;
}


/* Exibe a tabela na tela. */
void Table_setVisible(){
	InitPosition = GLOBAL_Table->Location;
	Position = InitPosition;
	
	int count = 0;
	List_Of_Rows *temp = GLOBAL_Table->Rows;
	
	// Exibe o cabeçalho da tabela.
	if (temp->next != NULL){		
		List_Of_Columns *headerTemp = temp->next->item->Cells;
		while(Columns_hasNext(headerTemp)){
			ColumnHeader_setVisible(headerTemp->next->item);
			headerTemp = headerTemp->next;			
		}		
	}
	
	if (temp->Count > 0){
		textcolor(GLOBAL_Table->CellForeColor);
		textbackground(GLOBAL_Table->CellBackColor);
		while(Rows_hasNext(temp)){
			Position->X = 1;			
			ShowColumnsFrom(temp->next->item->Cells);
			temp = temp->next;
		}
	}
}

//
