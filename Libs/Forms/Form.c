// Classe Form {
#include <string.h>

/* Funções do struct*/
void AddTextBox(TextBox *txt);
void AddLabel(Label *label);
void AddDateTimePicker(DateTimePicker *txt);
void AddCheckBox(CheckBox *object);
void AddComboBox(ComboBox *object);
void AddButton(Button *object);
void AddMenuBar(MenuBar *object);
void AddTable(Table *object);
void Navigate();
void NavigateByTab();

/* Estrutura para criar uma janela. */
typedef struct FORM{
	int BackColor;	
    int ForeColor;
    string Text;
    _SIZE *Size;
    padding *Padding;
    LOCATION *Location;
    int BorderStyle;
    bool Title;
    bool ClassicTitle;
    bool Shadow;
    int ScreenSaved;
    struct char_info *screen_buffer;
	List_Of_Label *Label_List;
	List_Of_TextBox *TextBox_list;
	List_Of_DateTimePicker *DateTimePicker_List;
	List_Of_CheckBox *CheckBox_List;
	List_Of_ComboBox *ComboBox_List;
	List_Of_Button *Button_List;
	List_Of_Table *Table_List;
	Bundle *bundle;
	TabControl *Tab;
	struct FORM *Parent;
	MenuBar *MenuList;
	void (*Navigate)();
	void (*AddTextBox)(TextBox *txt);
	void (*AddLabel)(Label *label);	
	void (*AddDateTimePicker)(DateTimePicker *txt);
	void (*AddCheckBox)(CheckBox *object);
	void (*AddComboBox)(ComboBox *object);
	void (*AddButton)(Button *object);
	void (*AddTable)(Table *object);
	void (*AddMenuBar)(MenuBar *object);
	void (*NavigateByTab)();
} Form;

Form *Form_Focus;

/* Funções do objeto. */
Form *getForm(Form *object);
void Form_setColors(Form *form, int ForeColor, int BackColor);
void Form_setSize(Form *form, int width, int height);
void Form_setLocation(Form *form, int up, int left);
void Form_setForm(Form *form, string *Text, bool Shadow, int BorderStyle, bool Title);
void Form_DrawFrame(Form *a);
void Form_ShowForm(Form *form);
void Form_Show(Form *form, Form *Parent);
void Form_Dispose(Form *form);
void Form_DisposeForm(Form *a);
void SaveScreen(Form *a);
void Form_Navigate(Form *form);




/* Cria uma instância na memória para uma nova janela. */
Form *new_Form(){
	Form *form = malloc(sizeof(Form));
	
	form->Shadow = false;
	form->BackColor = Color.Gray;
	form->ForeColor = Color.Black;
	form->Text = "Form1";
	form->Size = new_size(20, 20);
	form->Location = setLocation(1, 1);
	form->BorderStyle = Border.FixedSingle;
	form->Title = true;	
	form->ClassicTitle = false;
	form->Label_List = new_List_Of_Label();
	form->TextBox_list = new_List_Of_TextBox();
	form->DateTimePicker_List = new_List_Of_DateTimePicker();
	form->CheckBox_List = new_List_Of_CheckBox();
	form->ComboBox_List = new_List_Of_ComboBox();
	form->Button_List = new_List_Of_Button();
	form->Table_List = new_List_Of_Table();
	form->bundle = new_Bundle();
	form->Tab = new_TabControl();
	form->MenuList = NULL;
	form->Parent = NULL;
	form->Navigate = Navigate;
	form->AddTextBox = AddTextBox;
	form->AddLabel = AddLabel;
	form->AddDateTimePicker = AddDateTimePicker;
	form->AddCheckBox = AddCheckBox;
	form->AddComboBox = AddComboBox;
	form->AddButton = AddButton;
	form->AddTable = AddTable;
	form->AddMenuBar = AddMenuBar;
	form->NavigateByTab = NavigateByTab;
	
	form->Padding = setPadding(
		form->Location->X + 1, 
		form->Location->Y + 3, 
		(form->Size->Width + form->Location->X) - 1, 
		(form->Size->Height + form->Location->Y) - 1
		);
	
	Form_Focus = form;
	
	return form;
}

Form *new_form(Bundle *bundle){
	Form *form = new_Form();
	form->bundle = bundle;
	
	return form;
}

Form *getForm(Form *object){
	Form_Focus = object;
	return Form_Focus;
}

/* Define as cores de fundo e frente da janela. */
void Form_setColors(Form *form, int ForeColor, int BackColor){
	form->BackColor = BackColor;
	form->ForeColor = ForeColor;
}

/* Define o tamanho da janela. */
void Form_setSize(Form *form, int width, int height){
	form->Size = new_size(width, height);
	
		if (form->Title == true){
		form->Padding->Top = form->Location->Y + 2;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}else{
		form->Padding->Top = form->Location->Y;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}
}

/* Define a localização da janela na tela. */
void Form_setLocation(Form *form, int up, int left){
	form->Location = setLocation(up, left);
	
	if (form->Title == true){
		form->Padding->Top = form->Location->Y + 2;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}else{
		form->Padding->Top = form->Location->Y;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}
}

/* Define as propriedades da janela. */
void Form_setForm(Form *form, string *Text, bool Shadow, int BorderStyle, bool Title){
	form->Text = Text;
	form->Shadow = Shadow;
	form->BorderStyle = BorderStyle;
	form->Title = Title;
	
	if (form->Title == true){
		form->Padding->Top = form->Location->Y + 2;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}else{
		form->Padding->Top = form->Location->Y;
		form->Padding->Left = form->Location->X;
		form->Padding->Right = (form->Size->Width + form->Location->X) - 1;
		form->Padding->Bottom = (form->Size->Height + form->Location->Y) - 1;
	}
}


/* Desenha a borda da janela.*/
void Form_DrawFrame(Form *a){
	
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	int i = 0, j = 0;
		
	// Desenha a sombra.
	if (a->Shadow == true){	
		textbackground(0);	
		textcolor(15);		
		 
		for (i=1; i<alt+1; i++) {
        	gotoxy(posX + 1, posY + i);
			strings(larg + 1, ' ');
		}
	}	
		
	// Cor de fundo e fonte.	
	textbackground(a->BackColor);	
	textcolor(a->ForeColor); 
	
	//Valores default para borda.
	int Left_Up = 218;
	int Horizon = 196;
	int Vertical = 179;
	int Right_Up = 191;
	int Left_Down = 192;
	int Right_Down = 217;
	int Middle_Left = 195;
	int Middle_Right = 180;
	
	// Verifica qual tipo de borda.
	if (a->BorderStyle == Border.None){
		Left_Up = 0;
		Horizon = 0;
		Vertical = 0;
		Right_Up = 0;
		Left_Down = 0;
		Right_Down = 0;	
		Middle_Left = 0;
		Middle_Right = 0;
	} else if (a->BorderStyle == Border.FixedDouble) {
		Left_Up = 201;
		Horizon = 205;
		Vertical = 186;
		Right_Up = 187;
		Left_Down = 200;
		Right_Down = 188;
		Middle_Left = 204;
		Middle_Right = 185;	
	} 
	
	// Desenha a parte superior da borda	
	gotoxy(posX, posY);
	putchar(Left_Up);
	strings(larg - 1, Horizon);	
	putchar(Right_Up);
    gotoxy(posX + 1, posY);
		
	// Desenha as laterais da borda	
	for (i=2; i<alt; i++) {
        gotoxy(posX , posY + (i-1));
		putchar(Vertical);
		strings(larg - 1, ' ');
		gotoxy(posX + (larg - 1), posY + (i-1));
        putchar(Vertical); printf("\n");
	}	
	
	// Desenha a parte inferior da borda	
	gotoxy(posX, posY + (i - 1));
	putchar(Left_Down);
	for (j=1; j<=larg-2; j++)	
		putchar(Horizon);
	putchar(Right_Down);	

	// Verifica se tem titulo.
	if (a->Title == true){
		gotoxy(posX, posY + 2);putchar(Middle_Left);
    	gotoxy(posX + 1, posY + 2); strings(larg - 1, Horizon); putchar(Middle_Right);    	
		//gotoxy(posX + 1, posY + 1); printf("%s", a->Text);
		gotoxy(posX + 1, posY + 1); printf("%s", a->Text);
	}
	
	if(a->ClassicTitle){
		textbackground(Color.Blue);	
		textcolor(Color.White);	
		gotoxy(a->Location->X, a->Location->Y);
		strings(a->Size->Width + 1, 32);
		gotoxy(a->Location->X + 1, a->Location->Y);
		printf("%s", a->Text);
	}
	
	/**/ 
}

/* Abre uma janela na tela. */
void Form_ShowForm(Form *form){
	// Salva o fundo.
	SaveScreen(form);
	// Desenha a tela.
	Form_DrawFrame(form);
	// Posiciona o Label.
	if (Count_Item_From_List_Of_Label(form->Label_List) > 0)
		Show_Label_From(form->Label_List);
	// Posiciona o TextBox.
	if (Count_Item_From_List_Of_TextBox(form->TextBox_list) > 0)
		Show_TextBox_From(form->TextBox_list);
	// Posiciona o Calendário.
	if (Count_Item_From_List_Of_DateTimePicker(form->DateTimePicker_List) > 0)
		Show_DateTimePicker_From(form->DateTimePicker_List);
	// Posiciona o checkBox.
	if (Count_Item_From_List_Of_CheckBox(form->CheckBox_List) > 0)
		Show_CheckBox_From(form->CheckBox_List);
	// Posiciona o comboBox.
	if (Count_Item_From_List_Of_ComboBox(form->ComboBox_List) > 0)
		Show_ComboBox_From(form->ComboBox_List);
	// Posiciona o Button.
	if (Count_Item_From_List_Of_Button(form->Button_List) > 0)
		Show_Button_From(form->Button_List);
	// Posiciona as tabelas.
	if (Count_Item_From_List_Of_Table(form->Table_List) > 0)
		Show_Table_From(form->Table_List);
	// Posiciona o menu.
	if (form->MenuList != NULL){
		getMenu(form->MenuList)->MenuBar_setVisible();
		MenuBar_Focus(form);
	}
}

/* Abre uma janela na tela dentro de outra janela. */
void Form_Show(Form *form, Form *Parent){
	form->Parent = Parent;
	Form_Focus = form;
	Form_ShowForm(Form_Focus);
}

/* Retira a janela da tela e restaura o background. */
void Form_Dispose(Form *form){
 	
 	Form_Focus = form->Parent;
 	Form_DisposeForm(form);
 }

/* Retira a janela da tela e restaura o background. */
void Form_DisposeForm(Form *a){	
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	int xCol = posX;
	int xLin = posY;
	
	///
	/// Fecha janela e esvazia o buffer
	///
	puttext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);
	normvideo();
	free(a->screen_buffer); 
}

/* Captura a região da tela onde a janela será aberta.*/
void SaveScreen(Form *a){
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	int xCol = posX;
	int xLin = posY;	
	
	a->screen_buffer = malloc((xCol + larg + 1) * (xLin + alt + 1) * sizeof(struct char_info));
	_conio_gettext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);	
}



// Navegação entre Controles do formulário.
void Form_Navigate(Form *form){
	/*List_Of_TextBox *temp = form->TextBox_list;	
	while(temp->next != NULL){	
		//setTextBoxVisible(temp->next->item);
		TextBox_Focus(temp->next->item);
		temp = temp->next;		
	}
	
	List_Of_DateTimePicker *dt_temp = Form_Focus->DateTimePicker_List;	
	while(dt_temp->next != NULL){
		Calendary_Focus(dt_temp->next->item);
		dt_temp = dt_temp->next;
	}*/
	Form_Focus = form;
	Form_Focus->Navigate();
}


// Navegação entre controles.
void Navigate(){
	List_Of_TextBox *temp = Form_Focus->TextBox_list;
	
	while(temp->next != NULL){
		TextBox_Focus(temp->next->item);
		temp = temp->next;		
	}
	
	List_Of_DateTimePicker *dt_temp = Form_Focus->DateTimePicker_List;
	
	while(dt_temp->next != NULL){
		Calendary_Focus(dt_temp->next->item);
		dt_temp = dt_temp->next;
	}
	
	List_Of_CheckBox *chk_temp = Form_Focus->CheckBox_List;
	
	while(chk_temp->next != NULL){
		CheckBox_Focus(chk_temp->next->item);
		chk_temp = chk_temp->next;
	}
	
	List_Of_ComboBox *cbo_temp = Form_Focus->ComboBox_List;
	
	while(cbo_temp->next != NULL){
		ComboBox_Focus(cbo_temp->next->item);
		cbo_temp = cbo_temp->next;
	}
}

void NavigateByTab(){
	TabControl *object = Form_Focus->Tab;
	
	while(tab_hasNext(object)){
		object = object->next;
		//printf("\n%d, %s %d", object->Index, object->Name, object->Type);
		
		if(object->Type == TypeOf.TextBox){
			TextBox_focus(object->Name);
		}
		
		if(object->Type == TypeOf.ComboBox){
			ComboBox_focus(object->Name);
		}
		
		if(object->Type == TypeOf.CheckBox){
			CheckBox_focus(object->Name);
		}
		
		if (object->Type == TypeOf.DateTimePicker){
			DateTimePicker_focus(object->Name);
		}
		
		if (object->Type == TypeOf.Table){
			Table_focus(object->Name);
		}
	}
	
	Button_Navigate(Form_Focus);
}



// ---------------------------------------------------------------------------------------

// }




