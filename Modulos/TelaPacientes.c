// TelaPacientes

// Tela
Form *TelaPacientes;

/*
Programação em C com interface.
Implementação de janelas, menus, botões, caixas de combinação, calendários, caixas de texto, labels, caixa de opção e acesso a dados em tabelas TXT.

#dev 
#linguagemc 
#algorithms 
#algoritmo 
*/

void TelaPacientes_AtualizarTable(Table *tb, bool isVisible);
void TelaPacientes_btnEditar();
void TelaPacientes_btnNovo();
void TelaPacientes_btnSair();
void TablePacientes_onKeyEnter();
void TablePacientes_onSelectChanged();

Form *new_TelaPacientes(){
	Form *this = new_Form();
	
	int Back = Color.White;
	int Fore = Color.Black;
	
	Form_setColors(this, Color.Black, Color.LightGray);
	Form_setSize(this, 120, 26);
	Form_setForm(this, "Pacientes", false, Border.FixedSingle, false);
	Form_setLocation(this, 1, 3);
	
	Button *btnNovo = new_button(SET(btnNovo), " Novo", this->BackColor, this->ForeColor, 2, 0, 10, 3);
	btnNovo->OnKeyEnter = TelaPacientes_btnNovo;
	Button *btnEditar = new_button(SET(btnEditar), "Editar", this->BackColor, this->ForeColor, 12, 0, 10, 3);
	btnEditar->OnKeyEnter = TelaPacientes_btnEditar;
	Button *btnSair = new_button(SET(btnSair), " Sair", this->BackColor, this->ForeColor, 44, 0, 10, 3);
	btnSair->OnKeyEnter = TelaPacientes_btnSair;

	Table *tb1 = new_Table(SET(tb1));
	TelaPacientes_AtualizarTable(tb1, false);	

	this->AddButton(btnNovo);
	this->AddButton(btnEditar);	
	this->AddButton(btnSair);
	this->AddTable(tb1);
			
	return this;
}

void TelaPacientes_btnEditar(){		
	Table_focus("tb1");	
	ButtonResult = false;
}

void TelaPacientes_btnNovo(){
	Bundle *b = new_Bundle();
	putExtras(b,"data", " ");
	putExtras(b,"nome", " ");
	putExtras(b,"ativo", "1");
	putExtras(b,"sexo", "Masculino");
	putExtras(b,"id", "-1");
	
	TelaEditarPaciente = new_TelaEditarPaciente(b);
	Form_Show(TelaEditarPaciente, TelaPacientes);
	TelaEditarPaciente->NavigateByTab();
	
	TelaPacientes_AtualizarTable(get_Table(TelaPacientes,"tb1"), true);
	free(b);
	ButtonResult = false;
}

void TelaPacientes_btnSair(){
	ButtonResult = true;
	Form_Dispose(TelaPacientes);	
}

void TelaPacientes_AtualizarTable(Table *tb, bool setVisible){
	// Array de pecientes.
	Pacientes *array = new_Pacientes();
	Pacientes_FindAll(array);
	
	// Declara um DataTable para guardar a consulta.
	DataTable *dt1 = new_DataTable("dt1");
				
	// Preenche o DataTable.
	dt1 = Pacientes_Fill(dt1, array);
	// Preenche a tabela.
	Table_setDataSource(tb, dt1);
	Table_Columns_setWidth(tb, "NOME", 20);
	Table_Columns_setWidth(tb, "SEXO", 5);
	Table_Columns_setWidth(tb, "DT_NASC", 11);
	Table_Columns_setWidth(tb, "ID", 5);
	Table_Columns_setWidth(tb, "A", 2);
	Table_SetLocation(tb, 1, 4);
	tb->Size->Height = 20;
	tb->Size->Width = 93;
	
	// Define os eventos.
	Table_setOnKeyEnter(tb, TablePacientes_onKeyEnter);
	Table_setOnSelectChanged(tb, TablePacientes_onSelectChanged);
	
	// Verifica se deve exibir a tabela na tela.
	if (setVisible){
		tb->Location->X += TelaPacientes->Location->X;	
		tb->Location->Y += TelaPacientes->Padding->Top;	
		Table_SetVisible(tb);
	}	
}

void Pacientes_FindAll(Pacientes *array){
	// Declara nova conexão.
	Connection *obj = new_Connection(tb_paciente_local, sizeof(tb_paciente));
	// Declara objeto temporário.
	tb_paciente temp;		
	// Declara modo de leitura.
	obj->setMode(Mode.rb);
	// Testa conexão.
	if (obj->getConnection()){
		// Declara um novo objeto de retorno com o tamanho de registros.
		tb_paciente *b = calloc(obj->Count, obj->Size);
		// Percorre a tabela e preenche o Array.		
		while(obj->ReadNext()){
			fread(&temp, obj->Size, 1, obj->File);
			if (temp.id > 0){
				b[obj->CurrentRow].id = temp.id;
				b[obj->CurrentRow].ativo = temp.ativo;
				strcpy(b[obj->CurrentRow].nome, temp.nome);
				//strcpy(b[obj->CurrentRow].dt_nasc, temp.dt_nasc);
				strcpy(b[obj->CurrentRow].dt_nasc, ToDateShort(temp.dt_nasc));				
				strcpy(b[obj->CurrentRow].sexo, temp.sexo);	
			}			
		}
		// A variável de retorno recebe o resultado da consulta.
		array->items = b;
		array->Count = obj->Count - 1;
	}else{
		MsgBox("Erro ao conectar");
	}	
	// Encerra a conexão.
	obj->closeConnection();		
}

 void TablePacientes_onKeyEnter(){
 	return;
 }
 
 void TablePacientes_onSelectChanged(){
 	return;
 }
//
