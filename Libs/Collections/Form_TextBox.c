// Class Form.TextBox

//Adiciona um TextBox no formulário.
void Form_AddTextBox(Form *form, TextBox *textBox){
	List_Of_TextBox *p = form->TextBox_list;
	textBox->Location->X += form->Location->X;
	//textBox->Location->Y += form->Location->Y;
	textBox->Location->Y += form->Padding->Top;
	AddTextBoxIn(p, textBox);
	AddTab(form->Tab, getTabCount(form->Tab) + 1, textBox->Name, TypeOf.TextBox);
}

//Adiciona um TextBox no formulário.
void AddTextBox(TextBox *txt){
	List_Of_TextBox *p = Form_Focus->TextBox_list;
	txt->Location->X += Form_Focus->Location->X;
	//txt->Location->Y += Form_Focus->Location->Y;
	txt->Location->Y += Form_Focus->Padding->Top;
	AddTextBoxIn(p, txt);
	AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, txt->Name, TypeOf.TextBox);
}

// Retorna um TextBox do formulário pelo nome.
string *getTextBox_Text(Form *a, string TextBox_Name){
	List_Of_TextBox *temp = a->TextBox_list;
	string TMP;
	
	while(temp->next != NULL){
		if(TextBox_Name == temp->next->item->Name){
			TMP = temp->next->item->Text;
		}
		temp = temp->next;
	}
	return TMP;
}

// Obtém o conteúdo do atributo Text de um TextBox.
string *getTextBox_text(string TextBox_Name){
	return getTextBox_Text(Form_Focus, TextBox_Name);
}

// Define o conteúdo do atributo Text de um TextBox do Formulário.
void setTextBox_Text(Form *a, string name, string value){
	List_Of_TextBox *temp = a->TextBox_list;
	string TMP;
	
	while(temp->next != NULL){
		if(name == temp->next->item->Name){
			temp->next->item->Text = value;
		}
		temp = temp->next;
	}
}

// Define o conteúdo do atributo Text de um TextBox.
void setTextBox_text(string name, string value){
	List_Of_TextBox *temp = Form_Focus->TextBox_list;
	string TMP;
	
	while(temp->next != NULL){
		if(name == temp->next->item->Name){
			temp->next->item->Text = value;
		}
		temp = temp->next;
	}
}

// Obtém um TextBox do formulário pelo nome.
TextBox *getTextBox(Form *a, string TextBox_Name){
	List_Of_TextBox *temp = a->TextBox_list;
	TextBox *TMP = new_TextBox(SET(TMP));
	
	while(temp->next != NULL){
		if(TextBox_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num TextBox pelo nome.
void TextBox_focus(string TextBox_Name){
	TextBox_Focus(getTextBox(Form_Focus, TextBox_Name));
}




//
