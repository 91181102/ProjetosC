// Classe Menu.MenuItem.MenuOption



typedef struct MENU_OPTION{
	string Name;
	string Text;
	void(*OnKeyEnter)();	
}MenuOption;

typedef struct LIST_OF_MENU_OPTION{
	int MaxLenght;
	int Count;
	MenuOption *item;
	struct LIST_OF_MENU_OPTION *next;
} List_Of_Menu_Option;


MenuOption *new_MenuOption(string Name, string Text, void *function){
	MenuOption *object = malloc(sizeof(MenuOption));
	
	object->Name = Name;
	object->Text = Text;
	object->OnKeyEnter = function;
	
	return object;
}

void MenuOption_setVisible(List_Of_Menu_Option *object){
	
}

MenuOption *getMenuOptionByIndex(List_Of_Menu_Option *object, int index){
	int i = 0;
	
	List_Of_Menu_Option *temp = object;
		
	while(temp->next != NULL){
		if (i == index)
			return temp->next->item;
		i++;
		temp = temp->next;		
	}
	return new_MenuOption("MenuOption1", "MenuOption1", OnKeyEnter);
}

//----------------------
// Operações com listas.
//----------------------

List_Of_Menu_Option *new_List_Of_Menu_Option(){
	List_Of_Menu_Option *List = (List_Of_Menu_Option *) malloc(sizeof(List_Of_Menu_Option));
	List->item = NULL;
	List->next = NULL;
	List->MaxLenght = 3;
	List->Count = 0;
	return List;
}

void Dispose_List_Of_Menu_Option(List_Of_Menu_Option *object){
	free(object);
}

// Adiciona um objeto na lista.
void AddMenuOptionIn(List_Of_Menu_Option *p, MenuOption *object){
	List_Of_Menu_Option *new_item = malloc(sizeof(List_Of_Menu_Option));	
		
	new_item->item = object;
	new_item->next = NULL;	
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddMenuOptionIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_MenuOption_From(List_Of_Menu_Option *p){
	List_Of_Menu_Option *temp = p;
	
	while(temp->next != NULL){	
		MenuOption_setVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_Menu_Option(List_Of_Menu_Option *p){
	int i = 0;
	
	List_Of_Menu_Option *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


//---------------------------------
// DropDown Menu
//---------------------------------
void MenuOption_Focus(List_Of_Menu_Option *object){
	List_Of_Menu_Option *temp = object;
	
	
}


// Verifica se há mais items na lista.
 bool Options_hasNext(List_Of_Menu_Option *temp){
	if (temp->next != NULL)
		return true;
	else
		return false;
}
//
