// Class Form.Menu

/* Adiciona um Menu no formulário. */
void AddMenuBar(MenuBar *object){
	
	object->Location->X += Form_Focus->Location->X - 1;
	//object->Location->Y += Form_Focus->Location->Y - 1;
	object->Location->Y += Form_Focus->Padding->Top - 1;
	object->width = Form_Focus->Size->Width + 1;
	
	Form_Focus->MenuList = object;	
}

/* Obtém o item de menu pelo índice. */
MenuItem *getMenuItemByIndex(List_Of_Menu_Item *object, int index){
	List_Of_Menu_Item *temp = object;
	int count = 0;
	
	while(temp->next != NULL){	
		if (index == count)
			return temp->next->item;
		temp = temp->next;
		count++;
	}
	return temp->next->item;
}

/* Mantém o foco no menu. */
void MenuBar_Focus(Form *form){
	List_Of_Menu_Item *temp = form->MenuList->MenuItem;
	
	KeyEvents e;
	bool exit = false;
	int index = 0;
	int limit = Count_Item_From_List_Of_Menu_Item(temp) - 1;
	
	MenuItem_setFocus(getMenuItemByIndex(temp, index));
	
	//e.KeyPressed = getKey();
	//e.KeyPressed = getKey();
	
	do{				
		if (e.KeyPressed == Keys.ARROW_RIGHT){
			fflush(stdin);
			index++;
			if (index > limit) index = limit;
			//gotoxy(30, 1); printf("             ");
			//GLOBAL_KeyEvents.KeyPressed = 0;
			exit = MenuItem_setFocus(getMenuItemByIndex(temp, index));
			//GLOBAL_KeyEvents.KeyPressed = getKey();
		}
		
		if (e.KeyPressed == Keys.ARROW_LEFT){
			fflush(stdin);
			index--;
			if (index < 0) index = 0;
			//gotoxy(30, 1); printf("             "); 
			//GLOBAL_KeyEvents.KeyPressed = 0;
			exit = MenuItem_setFocus(getMenuItemByIndex(temp, index));			
		}
		
		if (e.KeyPressed == Keys.ESC && exit == false){
			fflush(stdin);
			exit = true;
			break;
		}
		//gotoxy(30, 1); printf("MenuBar Focus"); 
		if (!exit){
			//e.KeyPressed = getKey();
			
			//if(kbhit()){
				e.KeyPressed = getch();
				
			//}
				
		}			
	}while(!exit);
}

//
