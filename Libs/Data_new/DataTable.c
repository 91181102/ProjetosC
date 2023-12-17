// Classe DataTable



typedef struct FIELD{
	string Value;
	string Name;
	int Type;
	int Index;	
}DataColumn;

typedef struct LIST_COL{
	int Count;
	DataColumn *item;
	struct LIST_COL *next;
}dtCol;

void AddDataColumn(dtCol *p, DataColumn *object);

typedef struct LIN{
	int Index;
	dtCol *Cells;
	void (*AddDataColumn)(dtCol *p, DataColumn *object);
}DataRow;

typedef struct LIST_ROW{
	int Count;
	DataRow *item;
	struct LIST_ROW *next;
}dtRow;


void AddDataRow(string Fields[]);
void AddFields(string Fields[], int Types[], int lenght);

typedef struct DATATABLE{
	string Name;
	dtCol *Columns;
	dtRow *Row;
	void (*AddFields)(string Fields[], int Types[], int lenght);
	void (*AddDataRow)(DataRow *object);
}DataTable;

dtCol *new_dtCol();
dtRow *new_dtRow();
DataColumn *new_DataColumn();
DataRow *new_DataRow();


// Define um DataTable publico.
DataTable *GLOBAL_DataTable;
DataColumn *GLOBAL_DataColumn;

/* Cria um novo DataTable */
DataTable *new_DataTable(string Name){
	DataTable *object = malloc(sizeof(DataTable));
	object->Row = new_dtRow();
	object->Name = Name;
	object->AddFields = AddFields;
	object->AddDataRow = AddDataRow;
	
	GLOBAL_DataTable = object;
	return object;
}

/* Cria uma nova linha */
DataRow *new_DataRow(){
	DataRow *object = malloc(sizeof(DataRow));
	
	object->Index = 0;
	object->Cells = new_dtCol();
	object->AddDataColumn = AddDataColumn;
	
	return object;
}

/* Cria uma nova coluna */
DataColumn *new_DataColumn(){
	DataColumn *object = malloc(sizeof(DataColumn));
	
	object->Index = 0;
	object->Type = TypeOf.Int;
	object->Value = "0";
	object->Name = "Name";
	
	GLOBAL_DataColumn = object;	
	return object;
}

/* Cria uma nova lista de colunas */
dtCol *new_dtCol(){
	dtCol *List = (dtCol *) malloc(sizeof(dtCol));
	List->Count = 0;
	List->item = NULL;
	List->next = NULL;
	
	return List;
}

/* Cria uma nova lista de linhas */
dtRow *new_dtRow(){
	dtRow *List = (dtRow *) malloc(sizeof(dtRow));
	List->Count = 0;
	List->item = NULL;
	List->next = NULL;
	return List;
}

/* Adiciona uma coluna na lista de colunas. */
void AddDataColumn(dtCol *p, DataColumn *object){
	dtCol *new_item = malloc(sizeof(dtCol));
			
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddDataColumn(p->next, object);
	}
	
}

/* Adiciona os campos numa linha e depois adiciona na tabela. */
void AddDataRow(string Fields[]){
	int Count = GLOBAL_DataTable->Columns->Count;
	int i = 0;
	DataColumn *col;
	DataRow *row = new_DataRow();
	
	for(i = 0; i<Count; i++){
		col = new_DataColumn();
		col->Index = i;
		col->Name = "";
		col->Value = Fields[i];
		row->Cells->Count += 1;
		row->AddDataColumn(row->Cells, col);
	}
	GLOBAL_DataTable->Row->Count += 1;
	AddNewRow(GLOBAL_DataTable->Row, row);
	printf("\nLinhas: %d  Colunas: %d", GLOBAL_DataTable->Row->Count, GLOBAL_DataTable->Columns->Count);
}

/* Adiciona uma linha na Lista de linhas. */
void AddNewRow(dtRow *p, DataRow *object){	
	dtRow *new_item = malloc(sizeof(dtRow));
	
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddNewRow(p->next, object);
	}	
}

/* Adiciona um campo na tabela. */
void AddFields(string Fields[], int Types[], int lenght){
	
	dtCol *colunas = new_dtCol();
	DataColumn *col;
	int i = 0;
	
	for(i = 0; i<lenght; i++){
		col = new_DataColumn();
		col->Index += 1;
		col->Name = Fields[i];
		col->Type = Types[i];
	}
	GLOBAL_DataTable->Columns = colunas;
	GLOBAL_DataTable->Columns->Count = lenght;
	
	printf("\n\n%d", lenght);
}


/* Obtém uma coluna */

DataColumn *getDataColumn(string Name){
	
	return GLOBAL_DataColumn;
}

bool dtCol_hasNext(dtCol *object){
	return true;	
};

//
