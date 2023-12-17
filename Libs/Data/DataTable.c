// Classe DataTable


string get_Cell(int index, string Name);
string get_NameField(int index);
string get_CellByIndex(int index, int colIndex);



void AddDataRow(string Fields[]);
void AddFields(string Fields[], int Types[], int lenght);

typedef struct DATATABLE{
	string Name;
	dtCol *Columns;
	dtRow *Row;
	void (*AddFields)(string Fields[], int Types[], int lenght);
	void (*AddDataRow)(DataRow *object);
	string (*get_Cell)(int index, string Name);
	string (*get_CellByIndex)(int index, int colIndex);
}DataTable;

string DataTable_get_NameField(DataTable *dt, int index);


// Define um DataTable publico.
DataTable *GLOBAL_DataTable;

/* Cria um novo DataTable */
DataTable *new_DataTable(string Name){
	DataTable *object = malloc(sizeof(DataTable));
	
	object->Row = new_dtRow();
	object->Name = Name;
	object->AddFields = AddFields;
	object->AddDataRow = AddDataRow;
	object->get_Cell = get_Cell;
	object->get_CellByIndex = get_CellByIndex;
	
	//GLOBAL_DataTable = object;
	return object;
}

DataTable *getDataTable(DataTable *object){
	GLOBAL_DataTable = object;
	return object;
}

void DataTable_AddDataRow(DataTable *dt, string Fields[]){
	int Count = dt->Columns->Count;
	int i = 0;
	DataColumn *col;
	DataRow *row = new_DataRow();
	
	for(i = 0; i < Count; i++){
		col = new_DataColumn();
		col->Index = i;
		col->Name = DataTable_get_NameField(dt, i);
		col->Value = Fields[i];
		row->Cells->Count += 1;
		row->AddDataColumn(row->Cells, col);		
	}
	dt->Row->Count += 1;
	AddNewRow(dt->Row, row);
}

void AddDataRow(string Fields[]){
	int Count = GLOBAL_DataTable->Columns->Count;
	int i = 0;
	DataColumn *col;
	DataRow *row = new_DataRow();
	
	for(i = 0; i < Count; i++){
		col = new_DataColumn();
		col->Index = i;		
		col->Name = get_NameField(i);
		col->Value = Fields[i];
		row->Cells->Count += 1;
		row->AddDataColumn(row->Cells, col);		
	}
	GLOBAL_DataTable->Row->Count += 1;
	AddNewRow(GLOBAL_DataTable->Row, row);
	//printf("\nLinhas: %d  Colunas: %d", GLOBAL_DataTable->Row->Count, GLOBAL_DataTable->Columns->Count);	
}

void AddNewRow(dtRow *p, DataRow *object){	
	dtRow *new_item = malloc(sizeof(dtRow));
	
	new_item->item = object;
	new_item->next = NULL;
	new_item->item->Index = p->Count;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddNewRow(p->next, object);
	}	
}

void AddFields(string Fields[], int Types[], int lenght){	
	dtCol *colunas = new_dtCol();
	DataColumn *col;
	int i = 0;
	
	for(i = 0; i<lenght; i++){
		col = new_DataColumn();
		col->Index += 1;
		col->Name = Fields[i];
		col->Type = Types[i];		
		AddDataColumn(colunas, col);
	}
	
	GLOBAL_DataTable->Columns = colunas;
	GLOBAL_DataTable->Columns->Count = lenght;
	
	printf("\n\n%d ", lenght);
}

void DataTable_AddFields(DataTable *dt, string Fields[], int Types[], int lenght){
	dtCol *colunas = new_dtCol();
	DataColumn *col;
	int i = 0;
	
	for(i = 0; i<lenght; i++){
		col = new_DataColumn();
		col->Index += 1;
		col->Name = Fields[i];
		col->Type = Types[i];		
		AddDataColumn(colunas, col);
	}
	
	dt->Columns = colunas;
	dt->Columns->Count = lenght;
}

// Obtém o valor da coluna.
string get_Cell(int index, string Name){
	int count = 0;
	dtRow *temp = GLOBAL_DataTable->Row;
	DataRow *row;
	
	while(dtRow_hasNext(temp)){
		if (count == index){
			row = temp->next->item;
			break;		
		}
		temp = temp->next;
		count++;
	}
	//printf("\nlinha: %d", count);
	
	DataColumn *column;
	while(dtCol_hasNext(row->Cells)){
		//printf("\n%s Name: %s", row->Cells->next->item->Value, Name);
		if (row->Cells->next->item->Name == Name){
			//printf("\n%s Name: %s", row->Cells->next->item->Value, Name);
			return row->Cells->next->item->Value;
		}		
		row->Cells = row->Cells->next;
	}
	
	//string value = Int_ToString(count);
	return "NOT FOUND";
}

string get_CellByIndex(int index, int colIndex){
	int count = 0;
	dtRow *temp = GLOBAL_DataTable->Row;
	DataRow *row;
	
	while(dtRow_hasNext(temp)){
		if (count == index){
			row = temp->next->item;			
			break;
		}
		temp = temp->next;
		count++;
	}
	count = 0;
	
	while(dtCol_hasNext(row->Cells)){
		if (count == colIndex){			
			return row->Cells->next->item->Value;
		}		
		row->Cells = row->Cells->next;
		count++;
	}
	return "NOT FOUND";
}

string getCellByIndex(DataTable *dt, int index, int colIndex){
	int count = 0;
	dtRow *temp = dt->Row;
	DataRow *row;
	
	while(dtRow_hasNext(temp)){
		if (count == index){
			row = temp->next->item;			
			break;
		}
		temp = temp->next;
		count++;
	}
	count = 0;
	
	dtCol *Cells = row->Cells;
	while(dtCol_hasNext(Cells)){
		if (count == colIndex){			
			return Cells->next->item->Value;
		}		
		Cells = Cells->next;
		count++;
	}

	return "NOT FOUND";
}

/**
 * Obtém o nome da coluna.
 * @param [index] Indice a ser procurado.
 */
string get_NameField(int index){
	dtCol *temp = GLOBAL_DataTable->Columns;
	int count = 0;
	
	while(dtCol_hasNext(temp)){
		//printf("\n%d - %s", index, temp->next->item->Name);
		if (count == index){			
			return temp->next->item->Name;
		}
		count++;
		temp = temp->next;
	}
	return "COLLUMN";
}

string DataTable_get_NameField(DataTable *dt, int index){
	dtCol *temp = dt->Columns;
	int count = 0;
	string match;
	
	while(dtCol_hasNext(temp)){
		//printf("\n%d - %s", index, temp->next->item->Name);
		if (count == index){			
			return temp->next->item->Name;
		}
		count++;
		temp = temp->next;
	}
	return "COLLUMN";
}



//
