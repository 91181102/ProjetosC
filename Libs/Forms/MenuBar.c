// Class MenuBar

void MenuBar_setVisible();
void AddMenuItem(MenuItem *object);

typedef struct MENU{
	string Name;
	string Title;
	LOCATION *Location;
	int width;
	List_Of_Menu_Item *MenuItem;
	void (*MenuBar_setVisible)();
	void (*AddMenuItem)(MenuItem *object);
}MenuBar;

MenuBar *GLOBAL_MenuBar;


// Cria um novo menu.
MenuBar *new_MenuBar(string Name){
	MenuBar *object = malloc(sizeof(MenuBar));
	
	object->Name = Name;
	object->Title = Name;
	object->Location = setLocation(1, 1);
	object->width = 80;
	object->MenuBar_setVisible = MenuBar_setVisible;
	object->MenuItem = new_List_Of_Menu_Item();
	object->AddMenuItem = AddMenuItem;
	
	GLOBAL_MenuBar = object;
	
	return object;
}

// Muda o foco para um determinado menu.
MenuBar *getMenu(MenuBar *object){
	GLOBAL_MenuBar = object;
	return GLOBAL_MenuBar;
}

// Exibe o menu no formulário.
void MenuBar_setVisible(){
	MenuBar *a = GLOBAL_MenuBar;
	
	//textbackground(Color.Blue);	
	//textcolor(Color.White);	
	//gotoxy(a->Location->X, a->Location->Y);
	//strings(a->width, 32);
	//gotoxy(a->Location->X + 1, a->Location->Y);
	//printf("%s", a->Title);
	
	textbackground(Color.LightGray);	
	textcolor(Color.Black);	
	gotoxy(a->Location->X, a->Location->Y + 1);
	strings(a->width, 32);
	//gotoxy(a->Location->X, a->Location->Y + 1);
	//printf("%s", a->Name);
	Show_MenuItem_From(a->MenuItem);
}

void AddMenuItem(MenuItem *object){
	object->Location->X = GLOBAL_MenuBar->Location->X + GLOBAL_MenuBar->MenuItem->Lenght;
	object->Location->Y = GLOBAL_MenuBar->Location->Y + 1;
	AddMenuItemIn(GLOBAL_MenuBar->MenuItem, object);
	
	GLOBAL_MenuBar->MenuItem->Lenght += strlen(object->Text) + 2;
}








//
