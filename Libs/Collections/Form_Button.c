// Class Form.Button

// Adiciona um checkbox no formulário.
void AddButton(Button *object){
	List_Of_Button *p = Form_Focus->Button_List;
	object->Location->X += Form_Focus->Location->X;
	object->Location->Y += Form_Focus->Padding->Top;
	AddButtonIn(p, object);	
	//AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, object->Name, TypeOf.Button);
}

// Obtém um Button do formulário pelo nome.
Button *get_Button(Form *a, string object_Name){
	List_Of_Button *temp = a->Button_List;
	Button *TMP = new_Button(SET(TMP));
	
	while(temp->next != NULL){
		if(object_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num Button pelo nome.
void Button_focus(string object_Name){
	Button_Focus(get_Button(Form_Focus, object_Name));
}

// Faz o botão perder o foco.
void Button_lostFocus(string object_Name){
	Button_LostFocus(get_Button(Form_Focus, object_Name));
}

// Obtem um botão pelo índice da lista.
Button *getButtonByIndex(List_Of_Button *temp, int index){
	int count = 0;
	
	while(temp->next != NULL){		
		if(count == index){
			
			return temp->next->item;
		}
		temp = temp->next;
		count++;		
	}	
	return temp->next->item;
}


// Navega entre os botões do formulário.
void Button_Navigate(Form *a){
	List_Of_Button *temp = a->Button_List;
	Button *previous;
	
	KeyEvents e;
	bool exit = false;
	int count = 0;
	int limit = Count_Item_From_List_Of_Button(temp) - 1;
	
	if(temp->next != NULL){			
		exit = Button_Focus(getButtonByIndex(temp, count));		
	}
	
	if (!exit)
		e.KeyPressed = getKey();
	
	do{			
		if ((e.KeyPressed == Keys.ARROW_LEFT || e.KeyPressed == Keys.ARROW_UP)){
			count--;
			if (count < 0) count = 0;
			exit = Button_Focus(getButtonByIndex(temp, count));			
		}
		
		if ((e.KeyPressed == Keys.ARROW_RIGHT || e.KeyPressed == Keys.ARROW_DOWN)){
			count++;
			if (count > limit) count = limit;
			exit = Button_Focus(getButtonByIndex(temp, count));			
		}
		
		if (e.KeyPressed == Keys.ESC){
			exit = true;
		}
		
		if (!exit){
			e.KeyPressed = getKey();
		}		
		
	} while(!exit);	
		
}

//
