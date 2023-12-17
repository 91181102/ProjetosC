// Classe Data.Connection


bool getConnection();
void closeConnection();
void setMode(string Mode);
void MoveNext();
bool ReadNext();
void Prepare();
	
typedef struct MODE{
	string rb;
	string wb;
	string ab;
	string r_plus;
}_Mode;

_Mode Mode;

typedef struct CONNECTION{
	string table;
	FILE *File;
	string Mode;
	int Size;
	int Count;
	int CurrentRow;
	long int bytes;
	long pos;
	bool(*getConnection)(void);
	void (*closeConnection)(void);
	void (*setMode)(string Mode);
	void (*MoveNext)(void);
	bool (*ReadNext)(void);
	bool (*Prepare)(void);	
}Connection;

Connection *Me;

void ModeSetMode(){
	// Modo de leitura binária.
	Mode.rb = "rb";
	// Modo de escrita binária.
	Mode.wb = "wb";
	// Modo de anexo binário.
	Mode.ab = "ab";	
	Mode.r_plus = "r+";	
}

/**
 * Cria uma nova conexão.
 * @param[table] Nome da tabela
 * @param[Size] Tamanho do registro
 */
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
	object->CurrentRow = -1;
	object->ReadNext = ReadNext;
	object->pos = 0;
	object->Prepare = Prepare;	
	
	Me = object;	
	return object;
}


/**
 * Define o modo de abertura do arquivo.
 * @param[Mode] Modo de abertura.
 */ 
void setMode(string Mode){
	Me->Mode = Mode;
}

/**
 * Abre a conexão com uma tabela.
 */
bool getConnection(){
	Me->File = fopen(Me->table, Me->Mode);
	if (Me->File == NULL){
		return false;
	}else{
		// Posiciona o arquivo no final.
		fseek(Me->File, 0, SEEK_END);
		// Obtém o tamanho do arquivo.
		Me->bytes = ftell(Me->File);
		Me->pos = ftell(Me->File);
		// Conta a quantidade de registros.
		if (Me->bytes > 0 && Me->Size > 0)
			Me->Count = (Me->bytes / Me->Size);
		// Retorna que o arquivo está aberto.
		fseek(Me->File, 0, SEEK_SET);
		return true;
	}
}

void Prepare(){	
	fseek(Me->File, Me->pos, SEEK_SET);
}

/**
 * Fecha a conexão com uma tabela.
 */
void closeConnection(){
	fclose(Me->File);
}


/**
 * Guarda a posição do cursor.
 */
void MoveNext(){
	Me->pos = ftell(Me->File);
}

/**
 * Verifica se há mais registros a serem lidos.
 */
bool ReadNext(){
	Me->CurrentRow +=1;
	if (Me->CurrentRow == Me->Count)
		return false;
	else{		
		return true;
	}
}

//
