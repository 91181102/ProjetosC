// Class Form_ComboBox

string getComboBox_text(string text);
int getComboBox_SelectIndex(string Name);
	
// Adiciona um comboBox no formulário.
void AddComboBox(ComboBox *object){
	List_Of_ComboBox *p = Form_Focus->ComboBox_List;
	object->Location->X += Form_Focus->Location->X;
	//object->Location->Y += Form_Focus->Location->Y;
	object->Location->Y += Form_Focus->Padding->Top;
	AddComboBoxIn(p, object);
	AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, object->Name, TypeOf.ComboBox);
}

// Obtém um ComboBox do formulário pelo nome.
ComboBox *get_ComboBox(Form *a, string object_Name){
	List_Of_ComboBox *temp = a->ComboBox_List;
	ComboBox *TMP = new_ComboBox(SET("Not Found"));
	
	while(temp->next != NULL){		
		if(object_Name == temp->next->item->Name){			
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num ComboBox pelo nome.
void ComboBox_focus(string object_Name){
	ComboBox_Focus(get_ComboBox(Form_Focus, object_Name));
}

// Obtém o texto do comboBox pelo nome.
string getComboBox_text(string Name){
	ComboBox *temp = get_ComboBox(Form_Focus, Name);
	//MsgBox(temp->Name);
	return temp->Text;
}

// Obtém o indice selecionado do comboBox.
int getComboBox_SelectIndex(string Name){
	ComboBox *temp = get_ComboBox(Form_Focus, Name);
	return temp->SelectedIndex;
}
//
