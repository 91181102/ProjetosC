// class libs.Data.DataColumn

typedef struct FIELD{
	string Value;
	string Name;
	int Type;
	int Index;	
}DataColumn;

DataColumn *getCell(string Name);
	
typedef struct LIST_COL{
	int Count;
	struct FIELD (*getCell)(string Name);
	DataColumn *item;
	struct LIST_COL *next;
}dtCol;

dtCol *new_dtCol();
DataColumn *new_DataColumn();

dtCol *GLOBAL_dtCol;
DataColumn *GLOBAL_DataColumn;

DataColumn *new_DataColumn(){
	DataColumn *object = malloc(sizeof(DataColumn));
	
	object->Index = 0;
	object->Type = TypeOf.Int;
	object->Value = "0";
	object->Name = "Name";
	
	GLOBAL_DataColumn = object;
	return object;
}

dtCol *new_dtCol(){
	dtCol *List = (dtCol *) malloc(sizeof(dtCol));
	List->Count = 0;
	List->item = NULL;
	List->next = NULL;	
	
	GLOBAL_dtCol = List;
	return List;
}

bool dtCol_hasNext(dtCol *temp){
	if (temp->next != NULL)
		return true;
	else
	 	return false;
}

DataColumn *getCell(string Name){
	dtCol *temp = GLOBAL_dtCol;
	
	while(dtCol_hasNext(temp)){
		if (temp->next->item->Name == Name){
			return temp->next->item;
			temp = temp->next;
		}
	}	
	return new_DataColumn();
}
//
