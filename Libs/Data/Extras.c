// Class Lib.Data.Extras

typedef struct EXTRAS{
	string Key;
	string Value;	
}Extras;

typedef struct BUNDLE{
	Extras *item;
	struct BUNDLE *next;
}Bundle;

string getExtras(Bundle *object, string Key);
void AddExtrasIn(Bundle *p, Extras *object);

Extras *new_Extras(string Key, string Value){
	Extras *object = malloc(sizeof(Extras));
	
	object->Key = Key;
	object->Value = Value;
	
	return object;
}

Bundle *new_Bundle(){
	Bundle *object = malloc(sizeof(Bundle));
	
	object->item = NULL;
	object->next = NULL;
	
	return object;
}


void putExtras(Bundle *object, string Key, string Value){
	AddExtrasIn(object, new_Extras(Key, Value));
}

string getExtras(Bundle *object, string Key){
	Bundle *temp = object;	
	
	while(temp->next != NULL){
		if(Key == temp->next->item->Key){
			return temp->next->item->Value;
		}
		temp = temp->next;
	}
	return "";
}



// Operações com listas
void Dispose_Bundle(Bundle *object){
	free(object);
}

// Adiciona um objeto na lista.
void AddExtrasIn(Bundle *p, Extras *object){
	Bundle *new_item = malloc(sizeof(Bundle));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddExtrasIn(p->next, object);
	}	
}





//
