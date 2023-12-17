// Form.Label

// Adiciona um Label no formulário.
void Form_AddLabel(Form *form, Label *label){
	List_Of_Label *p = form->Label_List;
	label->Location->X += form->Location->X;
	//label->Location->Y += form->Location->Y;
	label->Location->Y += form->Padding->Top;
	AddLabelIn(p, label);	
}

// Adiciona um Label no formulário.
void AddLabel(Label *label){
	List_Of_Label *p = Form_Focus->Label_List;
	label->Location->X += Form_Focus->Location->X;
	//label->Location->Y += Form_Focus->Location->Y;
	label->Location->Y += Form_Focus->Padding->Top;
	AddLabelIn(p, label);	
}

// Retorna um label do formulário pelo nome.
string *getLabel_Text(Form *a, string Label_Name){
	List_Of_Label *temp = a->Label_List;
	string TMP;
	
	while(temp->next != NULL){		
		if (Label_Name == temp->next->item->Name){
			TMP = temp->next->item->Text;
		}		
		temp = temp->next;
	}
	return TMP;
}


//
