// Classe Classe Libs.Data.Rows

void AddColumns(Columns * object);

typedef struct ROWS{	
	int RowIndex; // Define o índice da linha.
	List_Of_Columns *Cells; // Define as colunas da linha.
	void (*AddColumns)(Columns *object);
}Rows;

Rows *CurrentRow;

// Array de Rows.
typedef struct ARRAY_ROWS{
	int Count;
	int CurrentItem;	
	Rows *items;	
}Rows_Array;

typedef struct LIST_OF_ROWS{
	int Count;
	Rows *item;
	struct LIST_OF_ROWS *next;
}List_Of_Rows;

bool Rows_hasNext(List_Of_Rows *temp);

Rows *new_Rows(){
	Rows *object = malloc(sizeof(Rows));
	object->Cells = new_List_Of_Columns();	
	object->RowIndex = 0;
	object->AddColumns = AddColumns;
	
	CurrentRow = object;
	
	return object;
}

List_Of_Rows *new_List_Of_Rows(){
	List_Of_Rows *List = (List_Of_Rows *) malloc(sizeof(List_Of_Rows));
	List->Count = 0;
	List->item = NULL;
	List->next = NULL;
	return List;
}

Rows_Array *new_Rows_Array(List_Of_Rows *p, int count){
	Rows_Array *array = calloc(count,sizeof(Rows_Array));
	array[0].Count = count;
	
	count = 0;
	
	List_Of_Rows *temp = p;
	while(Rows_hasNext(temp)){
		array[count].items = temp->next->item;		
		count++;
		temp = temp->next;	
	}	
	return array;	
}

Rows *getRow(Rows *object){
	CurrentRow = object;
	return CurrentRow;
}

void AddColumns(Columns * object){
	CurrentRow->Cells->Count += 1;
	object->Header->Index = CurrentRow->Cells->Count;
	AddColumnIn(CurrentRow->Cells, object);
}

/* Adiciona uma coluna na lista. */
void AddRowIn(List_Of_Rows *p, Rows *object){
	List_Of_Rows *new_item = malloc(sizeof(List_Of_Rows));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddRowIn(p->next, object);
	}
}

/* Verifica se há mais linhas na lista. */
bool Rows_hasNext(List_Of_Rows *temp){
	if (temp->next != NULL)
		return true;
	else
	 	return false;
}

//
