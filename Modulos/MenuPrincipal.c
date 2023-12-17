// Menu Principal

#include "SystemDataSet.c"
#include "Pacientes.c"
#include "TelaEditarMedico.c"
#include "TelaEditarPaciente.c"
#include "TelaPacientes.c"
#include "TelaMedicos.c"

void mniMedicos_KeyEnter();
void mniPacientes_KeyEnter();
void mniVerConsultas_KeyEnter();
void mniAgendamentos_KeyEnter();
void TelaMenuPrincipal_mnSair();

Form *TelaMenuPrincipal;

Form *new_TelaMenuPrincipal(){
	Form *this = new_Form();
	//Form *form1 = new_Form();	
	
	Form_setColors(this, Color.Black, Color.Gray);
	Form_setSize(this, 120, 28);
	Form_setForm(this, "Menu Principal", false, Border.FixedDouble, false);
	Form_setLocation(this, 1, 1);
	this->ClassicTitle = true;
	 	
	Label *label1 = new_label(SET(label1),"Cadastro de Medicos", 4, 6, Color.LightGreen, Color.Green);	
	Label *label2 = new_label(SET(label2),"Cadastro de Pacientes", 4, 8, Color.LightGreen, Color.Green);
	Label *label3 = new_label(SET(label3),"Consultas", 4, 10, Color.LightGreen, Color.Green);
	Label *label4 = new_label(SET(label4),"Sair", 4, 12, Color.LightGreen, Color.Green);
	
	MenuBar *menu = new_MenuBar(SET(memu));
	
	menu->Title = "CLINICA MEDICA";
	this->AddMenuBar(menu);
		
	MenuItem *mnCadastro = new_MenuItem(SET(mnCadastro), "Cadastros");
	MenuItem *mnConsultas = new_MenuItem(SET(mnConsultas), "Consultas");
	MenuItem *mnRelatorios = new_MenuItem(SET(mnRelatorios), "Relatorios");
	MenuItem *mnSair = new_MenuItem(SET(mnSair), "Sair");
	
	MenuOption *mniMedicos = new_MenuOption(SET(mniMedicos), "Medicos", mniMedicos_KeyEnter);
	MenuOption *mniPacientes = new_MenuOption(SET(mniPacientes), "Pacientes", mniPacientes_KeyEnter);
	MenuOption *mniVerConsultas = new_MenuOption(SET(mniVerConsultas), "Ver Consultas", mniVerConsultas_KeyEnter);
	MenuOption *mniAgendamentos = new_MenuOption(SET(mniAgendamentos), "Agendamentos", mniAgendamentos_KeyEnter);
	MenuOption *mniEncerrar = new_MenuOption(SET(mniEncerrar), "Encerrar", TelaMenuPrincipal_mnSair);
	
	menu->AddMenuItem(mnCadastro);
	menu->AddMenuItem(mnConsultas);
	menu->AddMenuItem(mnRelatorios);
	menu->AddMenuItem(mnSair);
	
	getMenuItem(mnCadastro)->AddMenuOption(mniMedicos);
	getMenuItem(mnCadastro)->AddMenuOption(mniPacientes);
	getMenuItem(mnCadastro)->AddMenuOption(mniEncerrar);
	getMenuItem(mnConsultas)->AddMenuOption(mniVerConsultas);
	getMenuItem(mnRelatorios)->AddMenuOption(mniAgendamentos);
		
	return this;
}


void TelaMenuPrincipal_mnSair(){
	Form_Dispose(TelaMenuPrincipal);
	MsgBox("Obrigado por utilizar Clinica Medica!");
	exit(0);
}

void mniMedicos_KeyEnter(){
	TelaMedicos = new_TelaMedicos();
	Form_Show(TelaMedicos, TelaMenuPrincipal);
	TelaMedicos->NavigateByTab();
}

void mniPacientes_KeyEnter(){
	TelaPacientes = new_TelaPacientes();
	Form_Show(TelaPacientes, TelaMenuPrincipal);
	TelaPacientes->NavigateByTab();
}

void mniVerConsultas_KeyEnter(){
	return;
}

void mniAgendamentos_KeyEnter(){
	return;
}

//
