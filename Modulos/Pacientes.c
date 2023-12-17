// Cadastro de pacientes

void TelaPaciente_btnEditar();
void TelaPaciente_btnSair();
void TelaPaciente_btnSalvar();
Form *TelaPaciente;

Form *new_TelaPaciente(Bundle *b){
	TelaPaciente = new_form(b);
	
	int Back = Color.White;
	int Fore = Color.Black;
	
	Form_setColors(TelaPaciente, Color.Black, Color.LightGray);
	Form_setSize(TelaPaciente, 40, 15);
	Form_setForm(TelaPaciente, "Cadastro de Pacientes", true, Border.FixedSingle, false);
	Form_setLocation(TelaPaciente, 12, 4);
	TelaPaciente->ClassicTitle = true;
	
	Label *label1 = new_label(SET(label1),"Nome:", 2, 2, TelaPaciente->ForeColor, TelaPaciente->BackColor);
	Label *label2 = new_label(SET(label2),"Idade:", 2, 4, TelaPaciente->ForeColor, TelaPaciente->BackColor);
	Label *label3 = new_label(SET(label3),"Sexo:", 2, 6, TelaPaciente->ForeColor, TelaPaciente->BackColor);
	Label *label4 = new_label(SET(label4),"Data:", 2, 8, TelaPaciente->ForeColor, TelaPaciente->BackColor);
	Label *label5 = new_label(SET(label5),"Nasc.:", 22, 8, TelaPaciente->ForeColor, TelaPaciente->BackColor);
	
	TextBox *txt_Nome = new_textBox(SET(txt_Nome), Back, Fore, 10, 2, 20, 15);
	TextBox *txt_Idade = new_textBox(SET(txt_Idade), Back, Fore, 10, 4, 20, 15);
	
	ComboBox *cbo_Sexo = new_comboBox(SET(cbo_Sexo), Back, Fore, 10, 6, 18);
	getComboBox(cbo_Sexo)->Add_Item(0, "Masculino");
	getComboBox(cbo_Sexo)->Add_Item(1, "Feminino");
	getComboBox(cbo_Sexo)->SetSelectedIndex(0);
	
	DateTimePicker *txt_Data = new_dateTimePicker(SET(txt_Data), Back, Fore, 10, 8);	
	DateTimePicker *txt_Nasc = new_dateTimePicker(SET(txt_Nasc), Back, Fore, 28, 8);
	
	CheckBox *chk_ativo = new_checkBox(SET(chk_ativo), "Ativo", false, TelaPaciente->BackColor, TelaPaciente->ForeColor, 2, 10);
	
	Button *btnSalvar = new_button(SET(btnSalvar), "Salvar", TelaPaciente->BackColor, TelaPaciente->ForeColor, 2, 10, 10, 3);
	btnSalvar->OnKeyEnter = TelaPaciente_btnSalvar;
	Button *btnEditar = new_button(SET(btnEditar), "Editar", TelaPaciente->BackColor, TelaPaciente->ForeColor, 13, 10, 10, 3);
	btnEditar->OnKeyEnter = TelaPaciente_btnEditar;
	Button *btnSair = new_button(SET(btnSair), " Sair", TelaPaciente->BackColor, TelaPaciente->ForeColor, 24, 10, 10, 3);
	btnSair->OnKeyEnter = TelaPaciente_btnSair;
	
	txt_Nome->Text = getExtras(TelaPaciente->bundle, "nome");
	txt_Idade->Text = getExtras(TelaPaciente->bundle, "crm");
		
	TelaPaciente->AddLabel(label1);
	TelaPaciente->AddLabel(label2);
	TelaPaciente->AddLabel(label3);
	TelaPaciente->AddLabel(label4);
	TelaPaciente->AddLabel(label5);
	TelaPaciente->AddTextBox(txt_Nome);
	TelaPaciente->AddTextBox(txt_Idade);	
	TelaPaciente->AddComboBox(cbo_Sexo);
	TelaPaciente->AddDateTimePicker(txt_Data);
	TelaPaciente->AddDateTimePicker(txt_Nasc);	
	TelaPaciente->AddCheckBox(chk_ativo);
	TelaPaciente->AddButton(btnSalvar);
	TelaPaciente->AddButton(btnEditar);
	TelaPaciente->AddButton(btnSair);
	
	
				
	return TelaPaciente;
}

void TelaPaciente_btnEditar(){	
	//Form_Navigate(Form_Focus);
	ButtonResult = false;
	NavigateByTab();	
}

void TelaPaciente_btnSair(){
	ButtonResult = true;
	Form_Dispose(TelaPaciente);	
}

void TelaPaciente_btnSalvar(){	
	MsgBox("Dados salvos com sucesso!");
	ButtonResult = false;
	TelaPaciente_btnSair();	
}

// ---------------------------------------
