// Classe Itens {

typedef struct ITEMS{
	int Cod;
	string Text;
	struct ITEMS *next;
}Items;


Items *new_Item(){
	Items *item = malloc(sizeof(Items));
	
	item->Cod = NULL;
	item->Text = NULL;
	item->next = NULL;
	
	return item;
}

Items *new_Items(int Cod, string Text){
	Items *item = new_Item();
	
	item->Cod = Cod;
	item->Text = Text;
	item->next = NULL;
	
	return item;
}

// Verifica se há mais items na lista.
 bool items_hasNext(Items *temp){
	if (temp->next != NULL)
		return true;
	else
		return false;
}

// Adiciona um objeto na lista.
void AddItem(Items *item, int Cod, string Text){
	Items *new_item = malloc(sizeof(Items));
	
	new_item->Cod = Cod;
	new_item->Text = Text;
	new_item->next = NULL;
		
	if (!items_hasNext(item)){
		item->next = new_item;
	}else{
		AddItem(item->next, Cod, Text);
	}	
}





//}
