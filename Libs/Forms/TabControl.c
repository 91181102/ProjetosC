// Class TabControl


typedef struct TABCONTROL{
	int Index;
	string Name;
	int Type;
	struct TABCONTROL *next;
}TabControl;

TabControl *GLOBAL_TabControl;

TabControl *new_TabControl(){
	TabControl *object = malloc(sizeof(TabControl));
	object->Index = NULL;
	object->Name = NULL;
	object->Type = NULL;
	object->next = NULL;
	
	GLOBAL_TabControl = object;
	
	return object;
}

void getTabControl(TabControl *object){
	GLOBAL_TabControl = object;
	return GLOBAL_TabControl;
}

void setTab(int index, string Name, int type){
	GLOBAL_TabControl->Index = index;
	GLOBAL_TabControl->Name = Name;
	GLOBAL_TabControl->Type = type;	
}

// Verifica se há mais items na lista.
 bool tab_hasNext(TabControl *temp){
	if (temp->next != NULL)
		return true;
	else
		return false;
}

// Adiciona um objeto na lista.
void AddTab(TabControl *object, int Index, string Name, int type){
	TabControl *new_tab = malloc(sizeof(TabControl));
	
	new_tab->Index = Index;
	new_tab->Name = Name;
	new_tab->Type = type;
	new_tab->next = NULL;
		
	if (!tab_hasNext(object)){
		object->next = new_tab;
	}else{
		AddTab(object->next, Index, Name, type);
	}	
}

// Conta quantos elementos há na lista.
int getTabCount(TabControl *object){
	int count = 0;
	
	while(tab_hasNext(object)){
		count++;
		object = object->next;
	}
	return count;
}

//
