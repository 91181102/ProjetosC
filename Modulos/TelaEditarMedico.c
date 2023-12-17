// TelaEditarMedico
// Tela
Form *TelaEditarMedico;

void TelaEditarMedico_btnSalvar();
void TelaEditarMedico_btnEditar();
void TelaEditarMedico_btnExcluir();
void TelaEditarMedico_btnSair();
bool Medicos_Insert(tb_medico temp);
bool Medicos_Update(tb_medico temp);

Form *new_TelaEditarMedico(Bundle *b){
	Form *this = new_form(b);
	
	int Back = Color.White;
	int Fore = Color.Black;
	
	Form_setColors(this, Color.Black, Color.LightGray);
	Form_setSize(this, 43, 9);
	Form_setForm(this, ".::Editar Medico", true, Border.FixedSingle, false);
	Form_setLocation(this, 30, 10);
	this->ClassicTitle = true;
	
	
	Label *label1 = new_label(SET(label1),"Nome:", 2, 2, this->ForeColor, this->BackColor);
	Label *label2 = new_label(SET(label2),"CRM:", 2, 4, this->ForeColor, this->BackColor);
	
	TextBox *txt_Nome = new_textBox(SET(txt_Nome), Back, Fore, 10, 2, 20, 15);
	TextBox *txt_Crm = new_textBox(SET(txt_Crm), Back, Fore, 10, 4, 10, 15);	
	TextBox *txt_id = new_textBox(SET(txt_id), Back, Fore, 21, 4, 8, 15);	

	
	Button *btnSalvar = new_button(SET(btnSalvar), "Salvar", this->BackColor, this->ForeColor, 1, 4, 10, 3);
	btnSalvar->OnKeyEnter = TelaEditarMedico_btnSalvar;
	Button *btnEditar = new_button(SET(btnEditar), "Editar", this->BackColor, this->ForeColor, 11, 4, 10, 3);
	btnEditar->OnKeyEnter = TelaEditarMedico_btnEditar;
	Button *btnExcluir = new_button(SET(btnExcluir), "Excluir", this->BackColor, this->ForeColor, 21, 4, 11, 3);
	btnExcluir->OnKeyEnter = TelaEditarMedico_btnExcluir;	
	Button *btnSair = new_button(SET(btnSair), " Sair", this->BackColor, this->ForeColor, 32, 4, 10, 3);
	btnSair->OnKeyEnter = TelaEditarMedico_btnSair;
	
	txt_Nome->Text = getExtras(this->bundle, "nome");
	txt_Crm->Text = getExtras(this->bundle, "crm");
	txt_id->Text = getExtras(this->bundle, "id");
		
	this->AddLabel(label1);
	this->AddLabel(label2);
	this->AddTextBox(txt_Nome);
	this->AddTextBox(txt_Crm);
	//TelaEditarMedico->AddTextBox(txt_id);
	this->AddButton(btnSalvar);
	this->AddButton(btnEditar);
	this->AddButton(btnExcluir);
	this->AddButton(btnSair);
			
	return this;
}

void TelaEditarMedico_btnSalvar(){	
	ButtonResult = false;	
	tb_medico temp;
	
	temp.crm = atoi(getTextBox_text("txt_Crm"));	
	temp.id = atoi(getExtras(TelaEditarMedico->bundle, "id"));
	strcpy(temp.nome, getTextBox_text("txt_Nome"));
	temp.ativo = 1;
		
	if (temp.id == -1){
		temp.id = Medicos_getNextId();		
			
		if (Medicos_Insert(temp)){
			MsgBox("Dados salvos com sucesso!");
			if (temp.id == 0){
				temp.id += 1;
				Medicos_Insert(temp);
			}			
			TelaEditarMedico_btnSair();	
		}
		else{
			MsgBox("Erro ao salvar dados!");
			return;	
		}		
	}else{
		if (Medicos_Update(temp)){
			MsgBox("Dados atualizados com sucesso!");
			TelaEditarMedico_btnSair();	
		}
		else{
			MsgBox("Erro ao atualizar dados!");
			return;	
		}
	}	
}

void TelaEditarMedico_btnEditar(){
	ButtonResult = false;
	NavigateByTab();	
}

void TelaEditarMedico_btnExcluir(){
	ButtonResult = false;
	tb_medico temp;
	
	temp.crm = atoi(getTextBox_text("txt_Crm"));	
	temp.id = atoi(getExtras(TelaEditarMedico->bundle, "id"));
	temp.ativo = 0;
	strcpy(temp.nome, getTextBox_text("txt_Nome"));
		
	if (Medicos_Update(temp)){
		MsgBox("Registro excluido com sucesso!");
		TelaEditarMedico_btnSair();	
	}
	else{
		MsgBox("Erro ao excluir registro!");
		return;	
	}	
}

void TelaEditarMedico_btnSair(){
	ButtonResult = true;
	Form_Dispose(TelaEditarMedico);	
}

bool Medicos_Insert(tb_medico temp){	
	// Declara nova conexão.
	Connection *obj = new_Connection(tb_medico_local, sizeof(tb_medico));
	// Declara modo de gravação.
	obj->setMode(Mode.ab);
	// Testa conexão.
	if (obj->getConnection()){
		// Faz o insert na tabela.
		fwrite(&temp, obj->Size, 1, obj->File);
	}else{
		// Exibe mensagem de erro.
		MsgBox("Erro ao conectar");
		return false;
	}	
	// Encerra a conexão.
	obj->closeConnection();
	return true;
}

bool Medicos_Update(tb_medico temp){	
	tb_medico tmp1;
	// Declara uma nova conexão.
	Connection *obj = new_Connection(tb_medico_local, sizeof(tb_medico));	
	// Define modo de acesso.
	obj->setMode(Mode.r_plus);
	// Testa conexão.
	if (obj->getConnection()){
		// Pecorre a tabela.
		while(obj->ReadNext()){
			// Faz a leitura do registro atual.
			fread(&tmp1, obj->Size, 1, obj->File);
			// Compara a id do registro.			
			if (temp.id == tmp1.id){				
				obj->Prepare();				
				// Faz o update na tabela.
            	fwrite(&temp, obj->Size, 1, obj->File);				
				break;
			}
			// Guarda a posição do registro.
			obj->MoveNext();
			
		}
	}else{
		// Exibe mensagem de erro.
		MsgBox("Erro ao conectar");
		return false;
	}	
	// Encerra a conexão.
	obj->closeConnection();
	return true;
}

int Medicos_getNextId(){
	int id = -1;
	tb_medico tmp1;
	// Declara uma nova conexão.
	Connection *obj = new_Connection("./Tabelas/medico.txt", sizeof(tb_medico));	
	// Define modo de acesso.
	obj->setMode(Mode.rb);
	// Testa conexão.
	if (obj->getConnection()){
		// Pecorre a tabela.
		while(obj->ReadNext()){
			// Faz a leitura do registro atual.
			fread(&tmp1, obj->Size, 1, obj->File);
			// Verifica se a id lida é maior do que a atual.
			if (tmp1.id > id)
				id = tmp1.id;
		}
	}else{
		// Exibe mensagem de erro.
		MsgBox("Erro ao conectar");
		return 1;
	}	
	// Encerra a conexão.
	obj->closeConnection();
	return id + 1;
}

//
