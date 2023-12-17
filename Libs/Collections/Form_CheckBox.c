// Class Form.CheckBox


// Adiciona um checkbox no formulário.
void AddCheckBox(CheckBox *object){
	List_Of_CheckBox *p = Form_Focus->CheckBox_List;
	object->Location->X += Form_Focus->Location->X;	
	object->Location->Y += Form_Focus->Padding->Top;
	AddCheckBoxIn(p, object);
	
	AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, object->Name, TypeOf.CheckBox);
}

// Obtém um CheckBox do formulário pelo nome.
CheckBox *get_CheckBox(Form *a, string object_Name){
	List_Of_CheckBox *temp = a->CheckBox_List;
	CheckBox *TMP = new_CheckBox(SET(TMP));
	
	while(temp->next != NULL){
		if(object_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num ChecKBox pelo nome.
void CheckBox_focus(string object_Name){
	CheckBox_Focus(get_CheckBox(Form_Focus, object_Name));
}


//
