// Class Form_Table

// Adiciona um Table no formulário.
void AddTable(Table *object){
	List_Of_Table *p = Form_Focus->Table_List;
	object->Location->X += Form_Focus->Location->X;	
	object->Location->Y += Form_Focus->Padding->Top;
	AddTableIn(p, object);
	AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, object->Name, TypeOf.Table);
}

// Obtém um Table do formulário pelo nome.
Table *get_Table(Form *a, string object_Name){
	List_Of_Table *temp = a->Table_List;
	Table *TMP = new_Table(SET(TMP));	
	
	while(temp->next != NULL){
		if(object_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num Table pelo nome.
void Table_focus(string object_Name){	
	Table_setFocus(get_Table(Form_Focus, object_Name));
}

//
