// Tela Medicos

// Eventos dos componentes
void TelaMedicos_btnEditar();
void TelaMedicos_btnExcluir();
void TelaMedicos_btnSair();
void TelaMedicos_btnNovo();
void TelaMedicos_btnTable();
void ShowSelected();
void ShowChanged();
void TelaMedicos_AtualizarTable(Table *tb, bool visible);

// Tela
Form *TelaMedicos;


Form *new_TelaMedicos(){
	Form *this = new_Form();
	
	int Back = Color.White;
	int Fore = Color.Black;
	
	Form_setColors(this, Color.Black, Color.LightGray);
	Form_setSize(this, 120, 26);
	Form_setForm(this, "Medicos", false, Border.FixedSingle, false);
	Form_setLocation(this, 1, 3);
	
	Button *btnNovo = new_button(SET(btnNovo), " Novo", this->BackColor, this->ForeColor, 2, 0, 10, 3);
	btnNovo->OnKeyEnter = TelaMedicos_btnNovo;
	Button *btnEditar = new_button(SET(btnEditar), "Editar", this->BackColor, this->ForeColor, 12, 0, 10, 3);
	btnEditar->OnKeyEnter = TelaMedicos_btnEditar;
	Button *btnExcluir = new_button(SET(btnExcluir), "Excluir", this->BackColor, this->ForeColor, 22, 0, 11, 3);
	btnExcluir->OnKeyEnter = TelaMedicos_btnExcluir;
	Button *btnTable = new_button(SET(btnTable), "Table", this->BackColor, this->ForeColor, 33, 0, 10, 3);
	btnTable->OnKeyEnter = TelaMedicos_btnTable;
	Button *btnSair = new_button(SET(btnSair), " Sair", this->BackColor, this->ForeColor, 44, 0, 10, 3);
	btnSair->OnKeyEnter = TelaMedicos_btnSair;

	Table *tb1 = new_Table(SET(tb1));
	TelaMedicos_AtualizarTable(tb1, false);	

	this->AddButton(btnNovo);
	this->AddButton(btnEditar);
	this->AddButton(btnExcluir);
	this->AddButton(btnTable);
	this->AddButton(btnSair);
	this->AddTable(tb1);
			
	return this;
}

void TelaMedicos_btnEditar(){	
	
	Table *temp = get_Table(TelaMedicos, "tb1");
	
	Bundle *b = new_Bundle();
	putExtras(b,"crm", Table_getValueAt(temp ,temp->CurrentRowIndex,"CRM"));
	putExtras(b,"nome", Table_getValueAt(temp ,temp->CurrentRowIndex,"NOME"));
	putExtras(b,"id", Table_getValueAt(temp ,temp->CurrentRowIndex,"ID"));
	putExtras(b,"ativo", Table_getValueAt(temp ,temp->CurrentRowIndex,"A"));
	TelaEditarMedico = new_TelaEditarMedico(b);
	
	Form_Show(TelaEditarMedico, TelaMedicos);
	TelaEditarMedico->NavigateByTab();
	
	TelaMedicos_AtualizarTable(get_Table(TelaMedicos,"tb1"), true);
	ButtonResult = false;
}

void TelaMedicos_btnExcluir(){
	ButtonResult = false;
}

void TelaMedicos_btnSair(){
	ButtonResult = true;
	Form_Dispose(TelaMedicos);	
}

void TelaMedicos_btnNovo(){
	Bundle *b = new_Bundle();
	putExtras(b,"crm", " ");
	putExtras(b,"nome", " ");
	putExtras(b,"ativo", "1");
	putExtras(b,"id", "-1");
	
	TelaEditarMedico = new_TelaEditarMedico(b);
	Form_Show(TelaEditarMedico, TelaMedicos);
	TelaEditarMedico->NavigateByTab();
	
	TelaMedicos_AtualizarTable(get_Table(TelaMedicos,"tb1"), true);	
	ButtonResult = false;
}

void TelaMedicos_btnTable(){
	//Form_Focus = TelaMedicos;
	Table_focus("tb1");
	
	//Table_setFocus(get_Table(TelaMedicos, "tb1"));
	ButtonResult = false;
}

void TelaMedicos_AtualizarTable(Table *tb, bool setVisible){
	// Array de médicos.
	Medicos *med = new_Medicos();
	Medicos_FindAll(med);
	
	// Declara um DataTable para guardar a consulta.
	DataTable *dt1 = new_DataTable("dt1");
				
	// Preenche o DataTable.
	dt1 = Medicos_Fill(dt1, med);
	// Preenche a tabela.
	Table_setDataSource(tb, dt1);
	Table_Columns_setWidth(tb, "NOME", 20);
	Table_Columns_setWidth(tb, "CRM", 5);
	Table_Columns_setWidth(tb, "ID", 5);
	Table_Columns_setWidth(tb, "A", 2);
	Table_SetLocation(tb, 1, 4);
	tb->Size->Height = 20;
	tb->Size->Width = 93;	
	//Table_setOnKeyEnter(tb1, ShowSelected);
	Table_setOnKeyEnter(tb, TelaMedicos_btnEditar);
	Table_setOnSelectChanged(tb, ShowChanged);
	
	if (setVisible){
		tb->Location->X += TelaMedicos->Location->X;	
		tb->Location->Y += TelaMedicos->Padding->Top;
		//Show_Table_From(TelaMedicos->Table_List);
		Table_SetVisible(tb);
	}
	//MsgBox("Atualizado");
}

void Medicos_FindAll(Medicos *med){
	// Declara nova conexão.
	Connection *obj = new_Connection(tb_medico_local, sizeof(tb_medico));
	// Declara objeto temporário.
	tb_medico temp;		
	// Declara modo de leitura.
	obj->setMode(Mode.rb);
	// Testa conexão.
	if (obj->getConnection()){
		// Declara um novo objeto de retorno com o tamanho de registros.
		tb_medico *b = calloc(obj->Count, obj->Size);
		// Percorre a tabela e preenche o Array.		
		while(obj->ReadNext()){
			fread(&temp, obj->Size, 1, obj->File);
			if (temp.id != 0){
				b[obj->CurrentRow].crm = temp.crm;
				b[obj->CurrentRow].id = temp.id;
				b[obj->CurrentRow].ativo = temp.ativo;
				strcpy(b[obj->CurrentRow].nome, temp.nome);	
			}			
		}
		// A variável de retorno recebe o resultado da consulta.
		med->items = b;
		med->Count = obj->Count - 1;
	}else{
		MsgBox("Erro ao conectar");
	}	
	// Encerra a conexão.
	obj->closeConnection();		
}

 void ShowSelected(){
 	//printf("\n%s\n", Table_getValueAt(GLOBAL_Table,GLOBAL_Table->CurrentRowIndex,"NOME"));
 }
 
 void ShowChanged(){
 	//gotoxy(10, 8);
 	//printf("\n%s\n", Table_getValueAt(GLOBAL_Table,GLOBAL_Table->CurrentRowIndex,"NOME"));
 }
/*
456 - REGINA SILVEIRA
123 - CAMILLO PACHECCO
786 - SANDRA CORREA
743 - THAIS PALADINO
846 - IGUATEMI QUIRINO
679 - LENA LOBO
498 - MARCOS MACEDO
Pressione qualquer tecla para continuar. . .
673 - DIEGO CORREA
769 - ROBERTO PAIXAO
957 - HENRIQUE LISBOA
635 - LAURA CALDEIRA
653 - HUMBERTO BOAVENTURA
1616 - RAFAEL DA SILVA
*/

//
