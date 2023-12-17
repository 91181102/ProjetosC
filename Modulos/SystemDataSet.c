// SystemDataSet

/* Percorre um array.*/
#define foreach(type, array) do { \
        type it = array[0]; \
        int i; \
		for(i = 0; i < array->Count+1; i++, it = array[i])
#define next  } while(0);


// Tabela de Médicos
typedef struct __MEDICO {
	int id;
	char nome[20];
	int crm;
	int ativo;
} tb_medico;

// Array de Medicos.
typedef struct TB_MEDICO{
	int Count;
	int CurrentItem;	
	tb_medico *items;	
}Medicos;

Medicos *new_Medicos();
DataTable *Medicos_Fill(DataTable *dt, Medicos *array);

// Tabela de Pacientes.
typedef struct __PACIENTE {
	int id;
	char nome[30];
	char dt_nasc[8];
	int ativo;
	char sexo[1];
} tb_paciente;

// Array de Pacientes.
typedef struct TB_PACIENTE{
	int Count;
	int CurrentItem;	
	tb_paciente *items;	
}Pacientes;

Pacientes *new_Pacientes();
	
// Tabela de Consultas.
typedef struct __CONSULTAS {
	int id;
	int paciente_id;
	int medico_id;
	char dt_consulta[8];
	char horario[5];
	int ativo;
} tb_consultas;

// Array de consultas.
typedef struct TB_CONSULTAS{
	int Count;
	int CurrentItem;	
	tb_consultas *items;	
}Consultas;

Consultas *new_Consultas();

typedef struct TB_CONSULTASJOIN{
	int Count;
	int CurrentItem;
	tb_consultas *consulta;
	tb_paciente *paciente;
	tb_medico *medico;
}ConsultasJoin;

string tb_medico_local;
string tb_paciente_local;
string tb_consultas_local;

void JoinPacienteOn(tb_paciente temp, Pacientes *array, int id_consulta);
void JoinMedicoOn(tb_medico temp, Medicos *array, int id_consulta);

void setLocal(){
	tb_medico_local = "./Tabelas/medico.txt";
	tb_paciente_local = "./Tabelas/paciente.txt";
	tb_consultas_local = "./Tabelas/consultas.txt";
}

/* Cria um novo array de medicos. */
Medicos *new_Medicos(){
	Medicos *object = malloc(sizeof(Medicos));
	object->Count = 0;
	object->CurrentItem = -1;
	object->items = calloc(3,sizeof(tb_medico));	
	return object;
}

/* Preenche um DataTable com um array */
DataTable *Medicos_Fill(DataTable *dt, Medicos *array){	
	dt = new_DataTable(dt->Name);
	
	string Field[] = { "ID","CRM", "NOME","A" };
	int Types[] = { TypeOf.Int, TypeOf.Int, TypeOf.Char, TypeOf.Int };
	DataTable_AddFields(dt, Field, Types, 4);	
	
	foreach(Medicos,array){
		if (array->items[i].ativo != 0){
			Field[0] = Int_ToString(array->items[i].id);
			Field[1] = Int_ToString(array->items[i].crm);
			Field[2] = array->items[i].nome;
			Field[3] = Int_ToString(array->items[i].ativo);
			DataTable_AddDataRow(dt, Field);	
		}			
	}next;	
	
	return dt;
}

/* Cria um novo array de pacientes. */
Pacientes *new_Pacientes(){
	Pacientes *object = malloc(sizeof(Pacientes));
	object->Count = 0;
	object->CurrentItem = -1;
	object->items = calloc(3, sizeof(tb_paciente));
	return object;
}

/* Preenche um DataTable com um array */
DataTable *Pacientes_Fill(DataTable *dt, Pacientes *array){
	dt = new_DataTable(dt->Name);
	
	string Field[] = { "ID","NOME", "SEXO","DT_NASC", "A" };
	int Types[] = { TypeOf.Int, TypeOf.Char, TypeOf.Char, TypeOf.Char, TypeOf.Int };
	DataTable_AddFields(dt, Field, Types, 5);	
	
	foreach(Pacientes,array){
		if (array->items[i].ativo != 0){
			Field[0] = Int_ToString(array->items[i].id);
			Field[1] = array->items[i].nome;
			Field[2] = array->items[i].sexo;
			Field[3] = array->items[i].dt_nasc;
			//Field[3] = ToDateShort(array->items[i].dt_nasc);			
			Field[4] = Int_ToString(array->items[i].ativo);
			DataTable_AddDataRow(dt, Field);	
		}			
	}next;	
	
	return dt;
}

/* Cria um novo array de consultas. */
Consultas *new_Consultas(){
	Consultas *object = malloc(sizeof(Consultas));
	object->Count = 0;
	object->CurrentItem = -1;
	object->items = calloc(3, sizeof(tb_consultas));
}

/* Preenche um DataTable com um array */
DataTable *Consultas_Fill(DataTable *dt, Consultas *array){
	dt = new_DataTable(dt->Name);
	
	string Field[] = { "ID","ID_PAC", "ID_MED","DATA","HORARIO","A" };
	int Types[] = { TypeOf.Int, TypeOf.Int, TypeOf.Int, TypeOf.Char, TypeOf.Char, TypeOf.Int };
	DataTable_AddFields(dt, Field, Types, 6);	
	
	foreach(Consultas,array){
		if (array->items[i].ativo != 0){
			Field[0] = Int_ToString(array->items[i].id);
			Field[1] = Int_ToString(array->items[i].paciente_id);
			Field[2] = Int_ToString(array->items[i].medico_id);			
			Field[3] = array->items[i].dt_consulta;
			Field[4] = array->items[i].horario;
			Field[5] = Int_ToString(array->items[i].ativo);
			DataTable_AddDataRow(dt, Field);	
		}			
	}next;	
	
	return dt;	
}

/* Junta as tabelas consultas, pacientes e médicos. */
DataTable *Join(DataTable *dt, Consultas *arrayConsultas, Medicos *arrayMedicos, Pacientes *arrayPacientes){
	dt = new_DataTable(dt->Name);
	tb_paciente paciente;
	tb_medico medico;
	
	string Field[] = { "ID","ID_PAC", "PACIENTE","DATA","HORARIO","ID_MED","MEDICO","A" };
	int Types[] = { TypeOf.Int, TypeOf.Int, TypeOf.Char, TypeOf.Char, TypeOf.Char, TypeOf.Int, TypeOf.Char, TypeOf.Int };
	DataTable_AddFields(dt, Field, Types, 8);	
	
	foreach(Consultas, arrayConsultas){
		if (arrayConsultas->items[i].ativo != 0){
			Field[0] = Int_ToString(arrayConsultas->items[i].id);
			
			JoinPacienteOn(paciente, arrayPacientes, arrayConsultas->items[i].paciente_id);
			Field[1] = Int_ToString(paciente.id);			
			strcpy(Field[2], paciente.nome);
			
			Field[3] = arrayConsultas->items[i].dt_consulta;
			Field[4] = arrayConsultas->items[i].horario;
						
			JoinMedicoOn(medico, arrayMedicos, arrayConsultas->items[i].medico_id);
			Field[5] = Int_ToString(medico.id);			
			strcpy(Field[6], medico.nome);	
			
			Field[7] = Int_ToString(arrayConsultas->items[i].ativo);
			DataTable_AddDataRow(dt, Field);
		}
	}next;
	
	return dt;
}

/* Junta a tabela paciente onde o id estiver na tabela consultas. */
void JoinPacienteOn(tb_paciente temp, Pacientes *array, int id_consulta){	
	
	foreach(Pacientes,array){
		if (id_consulta == array->items[i].id){
			temp.id = array->items[i].id;
			strcpy(temp.nome, array->items[i].nome);
			strcpy(temp.sexo, array->items[i].sexo);
			strcpy(temp.dt_nasc, array->items[i].dt_nasc);
			temp.ativo = array->items[i].ativo;
			break;
		}
	}next;
}


/* Junta a tabela médicos onde o id estiver na tabela consultas. */
void JoinMedicoOn(tb_medico temp, Medicos *array, int id_consulta){
		
	foreach(Medicos, array){
		if (id_consulta == array->items[i].id){
			temp.id = array->items[i].id;
			strcpy(temp.nome, array->items[i].nome);
			strcpy(temp.crm, array->items[i].crm);
			temp.ativo = array->items[i].ativo;
			break;
		}
	}next;
}


//
