// TelaEditarPaciente

// Declaração da tela de edição de registros.
Form *TelaEditarPaciente;
// Evento de botões.
void TelaEditarPaciente_btnSalvar();
void TelaEditarPaciente_btnEditar();
void TelaEditarPaciente_btnExcluir();
void TelaEditarPaciente_btnSair();
// Operações com tabelas.
bool Paciente_Insert(tb_paciente temp);
bool Paciente_Update(tb_paciente temp);

/// Monta a tela de editar registros.
Form *new_TelaEditarPaciente(Bundle *b){
	Form *this = new_form(b); // Novo formulário.
	
	int Back = Color.White; 
	int Fore = Color.Black;
	// Define as dimensões, cores e título do formulário.
	Form_setColors(this, Color.Black, Color.LightGray); // Define as cores
	Form_setSize(this, 43, 12); // Define o tamanho do formulário.
	Form_setForm(this, ".::Editar Paciente", true, Border.FixedSingle, false); // Define o título da janela.
	Form_setLocation(this, 30, 10); // Define a localização dentre da janela pai.
	this->ClassicTitle = true;	// Define o tipo de título da janela.	
	// Define o nome dos campos e sua localização.
	Label *label1 = new_label(SET(label1),"Nome:", 2, 2, this->ForeColor, this->BackColor);
	Label *label2 = new_label(SET(label2),"Sexo:", 2, 4, this->ForeColor, this->BackColor);
	Label *label3 = new_label(SET(label3),"Data Nasc.:", 2, 6, this->ForeColor, this->BackColor);	
	// Define a caixa de texto.
	TextBox *txt_Nome = new_textBox(SET(txt_Nome), Back, Fore, 10, 2, 30, 15);	
	TextBox *txt_id = new_textBox(SET(txt_id), Back, Fore, 21, 4, 8, 15);
    // Define uma caixa de combinação e adiciona os itens.
	ComboBox *cbo_Sexo = new_comboBox(SET(cbo_Sexo), Back, Fore, 10, 4, 13);
	getComboBox(cbo_Sexo)->Add_Item(0, "Masculino");
	getComboBox(cbo_Sexo)->Add_Item(1, "Feminino");
	getComboBox(cbo_Sexo)->SetSelectedIndex(0);	
	// Define um calendário.
	DateTimePicker *txt_Nasc = new_dateTimePicker(SET(txt_Nasc), Back, Fore, 14, 6);	
	// Define os botões.
	Button *btnSalvar = new_button(SET(btnSalvar), "Salvar", this->BackColor, this->ForeColor, 1, 7, 10, 3);
	btnSalvar->OnKeyEnter = TelaEditarPaciente_btnSalvar;
	Button *btnEditar = new_button(SET(btnEditar), "Editar", this->BackColor, this->ForeColor, 11, 7, 10, 3);
	btnEditar->OnKeyEnter = TelaEditarPaciente_btnEditar;
	Button *btnExcluir = new_button(SET(btnExcluir), "Excluir", this->BackColor, this->ForeColor, 21, 7, 11, 3);
	btnExcluir->OnKeyEnter = TelaEditarPaciente_btnExcluir;	
	Button *btnSair = new_button(SET(btnSair), " Sair", this->BackColor, this->ForeColor, 32, 7, 10, 3);
	btnSair->OnKeyEnter = TelaEditarPaciente_btnSair;
	
	txt_Nome->Text = getExtras(this->bundle, "nome");
	cbo_Sexo->Text = getExtras(this->bundle, "sexo");
	txt_id->Text = getExtras(this->bundle, "id");
	// Adiciona os controles na janela. 	
	this->AddLabel(label1);
	this->AddLabel(label2);
	this->AddLabel(label3);
	this->AddTextBox(txt_Nome);	
	this->AddComboBox(cbo_Sexo);
	this->AddDateTimePicker(txt_Nasc);
	//TelaEditarMedico->AddTextBox(txt_id);
	this->AddButton(btnSalvar);
	this->AddButton(btnEditar);
	this->AddButton(btnExcluir);
	this->AddButton(btnSair);
			
	return this;
}

void TelaEditarPaciente_btnSalvar(){}
	ButtonResult = false;	
	tb_paciente temp;
	
	temp.id = atoi(getExtras(TelaEditarPaciente->bundle, "id"));
	temp.ativo = 1;
	
	//strcpy(temp.dt_nasc, getDate_text("txt_Nasc"));
	
	strcpy(temp.nome, getTextBox_text("txt_Nome"));
	getDate_text(&temp.dt_nasc, "txt_Nasc");
	if (getComboBox_SelectIndex("cbo_Sexo") == 0){
		strcpy(temp.sexo, "M ");		
	}else{	
		strcpy(temp.sexo, "F ");
	}	
			
//	MsgBox(temp.nome);	
//	MsgBox(temp.dt_nasc);
//	MsgBox(temp.sexo);

	if (temp.id == -1){
		temp.id = Paciente_getNextId();		
			
		if (Paciente_Insert(temp)){
			MsgBox("Dados salvos com sucesso!");
			if (temp.id == 0){
				temp.id += 1;
				Paciente_Insert(temp);
			}			
			TelaEditarPaciente_btnSair();	
		}
		else{
			MsgBox("Erro ao salvar dados!");
			return;	
		}		
	}else{
		if (Paciente_Update(temp)){
			MsgBox("Dados atualizados com sucesso!");
			TelaEditarPaciente_btnSair();	
		}
		else{
			MsgBox("Erro ao atualizar dados!");
			return;	
		}
	}	
}

void TelaEditarPaciente_btnEditar(){
	ButtonResult = false;
	NavigateByTab();	
}

void TelaEditarPaciente_btnExcluir(){
	ButtonResult = false;
	tb_paciente temp;	
	
	temp.id = atoi(getExtras(TelaEditarMedico->bundle, "id"));
	temp.ativo = 0;
	strcpy(temp.nome, getTextBox_text("txt_nome"));
	strcpy(temp.dt_nasc, getTextBox_text("txt_dt_nasc"));
	strcpy(temp.sexo, getTextBox_text("txt_sexo"));
		
	if (Paciente_Update(temp)){
		MsgBox("Registro excluido com sucesso!");
		TelaEditarPaciente_btnSair();	
	}
	else{
		MsgBox("Erro ao excluir registro!");
		return;	
	}	
}

void TelaEditarPaciente_btnSair(){
	ButtonResult = true;
	Form_Dispose(TelaEditarPaciente);	
}

bool Paciente_Insert(tb_paciente temp){}
	// Declara nova conexão.
	Connection *obj = new_Connection(tb_paciente_local, sizeof(tb_paciente));
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

bool Paciente_Update(tb_paciente temp){}
	tb_paciente tmp1;
	// Declara uma nova conexão.
	Connection *obj = new_Connection(tb_paciente_local, sizeof(tb_paciente));	
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

int Paciente_getNextId(){
	int id = -1;
	tb_paciente tmp1;
	// Declara uma nova conexão.
	Connection *obj = new_Connection(tb_paciente_local, sizeof(tb_paciente));	
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
