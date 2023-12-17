// Class Form.DateTimePicker

void getDate_text(char *dest, string object_Name);

//Adiciona um calend�rio no formulario.
void Form_AddDateTimePicker(Form *form, DateTimePicker *txt){
	List_Of_DateTimePicker *p = form->DateTimePicker_List;
	txt->Location->X += form->Location->X;
	//txt->Location->Y += form->Location->Y + 1;
	txt->Location->Y += form->Padding->Top + 1;
	AddDateTimePickerIn(p, txt);
	AddTab(form->Tab, getTabCount(form->Tab) + 1, txt->Name, TypeOf.DateTimePicker);
}

//Adiciona um calend�rio no formul�rio.
void AddDateTimePicker(DateTimePicker *txt){
	List_Of_DateTimePicker *p = Form_Focus->DateTimePicker_List;
	txt->Location->X += Form_Focus->Location->X;
	//txt->Location->Y += Form_Focus->Location->Y + 1;
	txt->Location->Y += Form_Focus->Padding->Top + 1;
	AddDateTimePickerIn(p, txt);
	AddTab(Form_Focus->Tab, getTabCount(Form_Focus->Tab) + 1, txt->Name, TypeOf.DateTimePicker);
}

// Obt�m um DateTimePicker do formul�rio pelo nome.
DateTimePicker *getDateTimePicker(Form *a, string Calendary_Name){
	List_Of_DateTimePicker *temp = a->DateTimePicker_List;
	DateTimePicker *TMP = new_DateTimePicker();
	
	while(temp->next != NULL){
		if(Calendary_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Define o valor da data de um DateTimePicker do formul�rio.
void setCalendaryFrom(Form *a, string Calendary_Name, int day, int month, int year){
	List_Of_DateTimePicker *temp = a->DateTimePicker_List;	
	
	while(temp->next != NULL){
		if(Calendary_Name == temp->next->item->Name){
			setDate(temp->next->item->Date, day, month, year);
		}		
		temp = temp->next;
	}
}


// Obt�m um DateTimePicker do formul�rio pelo nome.
DateTimePicker *get_DateTimePicker(Form *a, string object_Name){
	List_Of_DateTimePicker *temp = a->DateTimePicker_List;
	DateTimePicker *TMP = new_DateTimePicker();
	
	while(temp->next != NULL){
		if(object_Name == temp->next->item->Name){
			return temp->next->item;
		}
		temp = temp->next;
	}
	return TMP;
}

// Foca o controle num DateTimePicker pelo nome.
void DateTimePicker_focus(string object_Name){
	Calendary_Focus(get_DateTimePicker(Form_Focus, object_Name));
}

// Obt�m a data de um controle DateTimePicker pelo nome.
void getDate_text(char *dest, string object_Name){
	DateTimePicker *temp = get_DateTimePicker(Form_Focus, object_Name);
	strcpy(dest, temp->Date->Value);
	
	
	//return temp->Date->Value;
}
//
