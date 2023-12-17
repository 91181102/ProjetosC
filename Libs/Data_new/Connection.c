// Classe Data.Connection

bool getConnection();
void closeConnection();
void setMode(string Mode);
bool MoveNext();
	
typedef struct MODE{
	string rb;
	string wb;	
}_Mode;

_Mode Mode;

typedef struct CONNECTION{
	string table;
	FILE *File;
	string Mode;
	int Size;
	int Count;
	long int bytes;
	bool(*getConnection)(void);
	void (*closeConnection)(void);
	void (*setMode)(string Mode);
	bool (*MoveNext)(void);
}Connection;

Connection *Me;

void ModeSetMode(){
	Mode.rb = "rb";
	Mode.wb = "wb";
}

///<summary> Cria uma nova conexão. </summary>
///<parameter: table> Nome da tabela </parameter>
///<parameter: Size> Tamanho do registro </parameter>
Connection *new_Connection(string table, int Size){
	Connection *object = malloc(sizeof(Connection));
	FILE *File;
	
	object->table = table;
	object->File = File;
	object->Mode = Mode.rb;
	object->getConnection = getConnection;
	object->closeConnection = closeConnection;
	object->MoveNext = MoveNext;
	object->setMode = setMode;
	object->bytes = 0;
	object->Size = Size;
	object->Count = 0;
	
	Me = object;	
	return object;
}


 
void setMode(string Mode){
	Me->Mode = Mode;
}

bool getConnection(){
	Me->File = fopen(Me->table, Me->Mode);
	if (Me->File == NULL){
		return false;
	}else{
		// Posiciona o arquivo no final.
		fseek(Me->File, 0, SEEK_END);
		// Obtém o tamanho do arquivo.
		Me->bytes = ftell(Me->File);
		// Conta a quantidade de registros.
		if (Me->bytes > 0 && Me->Size > 0)
			Me->Count = Me->bytes / Me->Size;
		// Retorna que o arquivo está aberto.
		fseek(Me->File, 0, SEEK_SET);
		return true;
	}
}

void closeConnection(){
	fclose(Me->File);
}

bool MoveNext(){	
	if (!feof(Me->File))
		return true;
	else
		return false;
}



//
