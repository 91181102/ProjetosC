// class Libs.Data.DataRow

void AddDataColumn(dtCol *p, DataColumn *object);


typedef struct LIN{
	int Index;
	dtCol *Cells;
	void (*AddDataColumn)(dtCol *p, DataColumn *object);
	struct DataColumn (*getCell)(string Name);
}DataRow;

DataRow *get_DataRowByIndex(int index);

typedef struct LIST_ROW{
	int Count;
	DataRow (*get_DataRowByIndex)(int index);	
	DataRow *item;
	struct LIST_ROW *next;
}dtRow;


dtRow *new_dtRow();
DataRow *new_DataRow();


DataRow *GLOBAL_DataRow;
dtRow *GLOBAL_dtRow;

/* Cria uma nova linha. */
DataRow *new_DataRow(){
	DataRow *object = malloc(sizeof(DataRow));
	
	object->Index = 0;
	object->Cells = new_dtCol();
	object->AddDataColumn = AddDataColumn;
	object->getCell = getCell;
	GLOBAL_DataRow = object;
	
	return object;
}

/* Cria uma nova linha.*/
dtRow *new_dtRow(){
	dtRow *List = (dtRow *) malloc(sizeof(dtRow));
	List->Count = 0;
	List->get_DataRowByIndex = get_DataRowByIndex;
	List->item = NULL;
	List->next = NULL;
	
	GLOBAL_dtRow = List;
	
	return List;
}

/* Adiciona uma nova coluna numa lista de colunas. */
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

/* Verifica se há mais linhas na lista retornando true */
bool dtRow_hasNext(dtRow *temp){
	if (temp->next != NULL)
		return true;
	else
	 	return false;
}

/* Obtém uma linha pelo índice da tabela*/
DataRow *get_DataRowByIndex(int index){
	dtRow *temp = GLOBAL_dtRow;
	int count = 0;
	
	while(dtRow_hasNext(temp)){
		if (count == index){
			GLOBAL_dtCol = temp->next->item->Cells;
			return temp->next->item;
		}
		count++;
		temp = temp->next;
	}
	return new_DataRow();	
}


//
