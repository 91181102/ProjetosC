// Classe Libs.Data.Table
void AddRow(Rows *object);
void Table_setVisible();
void set_DataSource(DataTable *dt);
void onKeyEnter();
void onSelectChanged();
void onKeyEsc();
	
typedef struct TABLE{
	string Name;
	int ColumnCount;
	int CellForeColor;
	int CellBackColor;
	int CurrentRowIndex;
	bool HeaderRow;
	List_Of_Rows *Rows;
	LOCATION *Location;
	LOCATION *Position;
	LOCATION *InitialPosition;
	_SIZE *Size;
	void (*AddRow)(Rows *object);
	void (*Table_setVisible)(void);
	void (*set_DataSource)(DataTable *dt);
	void (*onKeyEnter)(void);
	void (*onSelectChanged)(void);
	void (*onKeyEsc)(void);
} Table;

typedef struct LIST_OF_TABLE{
	Table *item;
	struct LIST_OF_TABLE *next;
}List_Of_Table;

Table *GLOBAL_Table;
string Table_getValueAt(Table *tb, int RowIndex, string ColumnName);

/* Cria uma nova tabela. */
Table *new_Table(string Name){
	Table *object = malloc(sizeof(Table));
	
	object->Name = Name;
	object->ColumnCount = 0;
	object->HeaderRow = true;
	object->Rows = new_List_Of_Rows();
	object->Location = setLocation(1,1);
	object->InitialPosition = setLocation(1,1);
	object->Position = setLocation(1,1);
	object->Size = new_size(20,6);
	object->AddRow = AddRow;
	object->Table_setVisible = Table_setVisible;	
	object->CellBackColor = Color.Red;
	object->CellForeColor = Color.Yellow;
	object->set_DataSource = set_DataSource;
	object->CurrentRowIndex = -1;
	object->onKeyEnter = onKeyEnter;
	object->onSelectChanged = onSelectChanged;
	object->onKeyEsc = onKeyEsc;
	
	GLOBAL_Table = object;
		
	return object;
}

/* Adiciona uma nova linha na tabela. */
void AddRow(Rows *object){
	GLOBAL_Table->Rows->Count += 1;
	AddRowIn(GLOBAL_Table->Rows, object);
}

void Table_AddRow(Table *tb, Rows *object){
	tb->Rows->Count +=1;
	AddRowIn(tb->Rows, object);
}

/* Obtém a tabela. */
Table *getTable(Table *object){
	GLOBAL_Table = object;
	return GLOBAL_Table;
}


/* Exibe a tabela na tela. */
void Table_setVisible(){
	InitPosition = GLOBAL_Table->Location;
	Position = InitPosition;
	
	int count = 0;
	List_Of_Rows *temp = GLOBAL_Table->Rows;
	
	// Exibe o cabeçalho da tabela.
	if (temp->next != NULL){		
		List_Of_Columns *headerTemp = temp->next->item->Cells;
		while(Columns_hasNext(headerTemp)){
			ColumnHeader_setVisible(headerTemp->next->item);
			headerTemp = headerTemp->next;			
		}		
	}
	
	if (temp->Count > 0){
		textcolor(GLOBAL_Table->CellForeColor);
		textbackground(GLOBAL_Table->CellBackColor);
		while(Rows_hasNext(temp)){
			Position->X = 1;			
			ShowColumnsFrom(temp->next->item->Cells);
			temp = temp->next;
		}
	}
}

void ShowColumnsFromTable(Table *tb, List_Of_Columns *p){
	List_Of_Columns *temp = p;
	
	tb->Position->X = tb->InitialPosition->X;
	tb->Position->Y += 1;
	
	while(Columns_hasNext(temp)){
		Column_SetVisible(tb, temp->next->item);
		temp = temp->next;
	}
}

void showHeaderFromTable(Table *tb, HeaderColumn *object){
	// Define as cores de fonte e fundo
	textcolor(object->ForeColor);
	textbackground(object->BackColor);
	// Posiciona o texto nas coordenadas X e Y.
	gotoxy(tb->Position->X, tb->Position->Y);
	putchar(186); //putchar(179);
	printf("%s", object->Text);
	// Conta os caracteres do cabeçalho.
	int lenght = strlen(object->Text);	
	//Completa com espaços.
	if(lenght < object->Width){
		strings(object->Width - lenght, 32);
		putchar(186); //putchar(179);
	}
	gotoxy(tb->Position->X, tb->Position->Y+ 1);
	
	
	// Posiciona o texto na próxima coluna.
	tb->Position->X += object->Width;
}

void ColumnHeader_setVisibleFromTable(Table *tb, Columns *object){	
	showHeaderFromTable(tb, object->Header);	
}


void Column_SetVisible(Table *tb, Columns *object){
	
	
	// Posiciona o texto nas coordenadas X e Y.
	gotoxy(tb->Position->X, tb->Position->Y);
	// Imprime a moldura.
	putchar(179);
	printf("%s", object->Value);
	// Conta os caracteres do cabeçalho.
	int lenght = strlen(object->Value);
	//Completa com espaços.
	if(lenght < object->Header->Width){
		// Imprime o conteúdo.
		strings(object->Header->Width - lenght, 32);
		// Imprime a moldura.
		putchar(179);	
	}
	tb->Position->X += object->Header->Width;
}

void Table_setCurrentRow(Table *tb, List_Of_Columns *p, int x, int y, bool isSelect){	
	List_Of_Columns *temp = p;
	Columns *object;
	
	tb->Position->X = tb->InitialPosition->X;	
	
	if (isSelect){
		textcolor(tb->CellBackColor);
		textbackground(tb->CellForeColor);	
	}else{
		textcolor(tb->CellForeColor);
		textbackground(tb->CellBackColor);
	}	
	
	while(Columns_hasNext(temp)){		
		object = temp->next->item;		
		// Posiciona o texto nas coordenadas X e Y.
		gotoxy(tb->Position->X, y);
		// Imprime a moldura.
		putchar(179);
		printf("%s", object->Value);
		// Conta os caracteres do cabeçalho.
		int lenght = strlen(object->Value);
		//Completa com espaços.
		if(lenght < object->Header->Width){
			// Imprime o conteúdo.
			strings(object->Header->Width - lenght, 32);
			// Imprime a moldura.			
			putchar(179);	
		}
		tb->Position->X += object->Header->Width;		
		temp = temp->next;
	}
	tb->Position->X = tb->InitialPosition->X;	
}


void Table_SetVisible(Table *tb){
	tb->InitialPosition->X = tb->Location->X;
	tb->InitialPosition->Y = tb->Location->Y;
	tb->Position->X = tb->InitialPosition->X;
	tb->Position->Y = tb->InitialPosition->Y;
	int limite = tb->Size->Height + tb->Position->Y;
	
	
	textcolor(tb->CellForeColor);
	textbackground(Color.Gray); 
	int i = 0;
	for(i=tb->Location->Y; i<=limite; i++){
		gotoxy(tb->Location->X,i);
		strings(tb->Size->Width, 32);		
	}
	
	//printf("Height: %d  Y: %d",tb->Size->Height, tb->Position->Y );
	gotoxy (10,1);
	int count = 0;
	List_Of_Rows *temp =  tb->Rows;
	
	// Exibe o cabeçalho da tabela.
	if (temp->next != NULL){		
		List_Of_Columns *headerTemp = temp->next->item->Cells;
		while(Columns_hasNext(headerTemp)){
			//ColumnHeader_setVisible(headerTemp->next->item);
			ColumnHeader_setVisibleFromTable(tb, headerTemp->next->item);
			headerTemp = headerTemp->next;			
		}		
	}
	//tb->Position->Y += 1;
	
	//if (tb->Rows->Count < 1) return;
	
	if (temp->Count > 0){
		textcolor(tb->CellForeColor);
		textbackground(tb->CellBackColor);
		while(Rows_hasNext(temp) && tb->Position->Y < limite) {
			tb->Position->X = tb->InitialPosition->X;			
			ShowColumnsFromTable(tb, temp->next->item->Cells);
			temp = temp->next;
			gotoxy (10,2); //printf("Height: %d  Y: %d",tb->Size->Height, tb->Position->Y );
		}
	}
	
	
	tb->InitialPosition->X = tb->Location->X;
	tb->InitialPosition->Y = tb->Location->Y;
	tb->Position->X = tb->InitialPosition->X;
	tb->Position->Y = tb->InitialPosition->Y;
}

void Table_SetLocation(Table *tb, int X, int Y){
	tb->Location->X = X;
	tb->Location->Y = Y;
	tb->InitialPosition->X = X;
	tb->InitialPosition->Y = Y;
	tb->Position->X = X;
	tb->Position->Y = Y;
}

void Table_setDataSource(Table *tb, DataTable *dt){
	
//	if (dt->Row->Count < 1) return;
	
	DataTable *temp = dt;
	
	tb->Rows = new_List_Of_Rows();
	
	HeaderColumn *col[temp->Columns->Count];
	Rows *row;
	
	int i = 0; int j = 0;
	for (i=0;i<temp->Columns->Count; i++){
		col[i] = new_HeaderColumn(DataTable_get_NameField(temp, i));		
	}
	
	for(i=0; i<temp->Row->Count; i++){
		row = new_Rows();
		for (j=0;j<temp->Columns->Count; j++){
			row->AddColumns(new_Columns(col[j], getCellByIndex(temp,i,j)));
		}		
		Table_AddRow(tb, row);
	}
}

void set_DataSource(DataTable *dt){
	DataTable *temp = dt;
	
	//memcpy(temp->Row,dt->Row,sizeof(dtRow));
	//memcpy(temp,dt,sizeof(DataTable));
	
	
	GLOBAL_Table->Rows = new_List_Of_Rows();
	
	HeaderColumn *col[temp->Columns->Count];
	Rows *row;
	
	int i = 0; int j = 0;
	for (i=0;i<temp->Columns->Count; i++){
		col[i] = new_HeaderColumn(DataTable_get_NameField(temp, i));		
	}
	
	for(i=0; i<temp->Row->Count; i++){
		row = new_Rows();
		for (j=0;j<temp->Columns->Count; j++){
			row->AddColumns(new_Columns(col[j], getCellByIndex(temp,i,j)));
		}
		GLOBAL_Table->AddRow(row);
	}
}

/* Define o tamanho da coluna. */
void Table_Columns_setWidth(Table *tb, string Name, int width){	
	List_Of_Rows *temp = tb->Rows;
	
	// Exibe o cabeçalho da tabela.
	if (temp->next != NULL){		
		List_Of_Columns *headerTemp = temp->next->item->Cells;
		while(Columns_hasNext(headerTemp)){			
			if (headerTemp->next->item->Header->Name == Name)
				headerTemp->next->item->Header->Width = width;
			headerTemp = headerTemp->next;
		}		
	}	
}

/* Obtém o valor de uma célula da tabela. */
string Table_getValueAt(Table *tb, int RowIndex, string ColumnName){
	int count = 0;	
	List_Of_Rows *temp = tb->Rows;
	Rows *row;
	string result = "NOT FOUND";
	
	while(Rows_hasNext(temp)){
		if(count == RowIndex){
			row = temp->next->item;			
			break;
		}
		temp = temp->next;
		count++;
	}
	
	
	List_Of_Columns *Cells = row->Cells;
	
	while(Columns_hasNext(Cells)){
		if (Cells->next->item->Header->Name == ColumnName){
			return Cells->next->item->Value;	
		}
		Cells = Cells->next;
	}	
	
	return result;
}

void onSelectChanged(){
	return;
}

void onKeyEnter(){
	return;
}

void onKeyEsc(){
	return;
}

void Table_setOnSelectChanged(Table *tb, void *function){
	tb->onSelectChanged = function;
}

void Table_setOnKeyEnter(Table *tb, void *function){
	tb->onKeyEnter = function;
}

void Table_setFocus(Table *tb){	
	
	if (tb->Rows->Count == 0) return;
	
	GLOBAL_Table = tb;
	Table *temp = tb;
	List_Of_Rows *rows = tb->Rows;
	List_Of_Columns *Cells;
	int CurrentRowIndex = temp->CurrentRowIndex = 0;
	bool exit = false;
	KeyEvents e;
	Rows_Array *row = new_Rows_Array(rows, temp->Rows->Count);
	
	int posX = tb->Location->X;
	int posY = tb->Location->Y + 1 + CurrentRowIndex;
	int x = 0; // linha que movimento o cursor.
	int y = 0; // linha que guarda o registro da posição do cursor.
	//int limite = tb->Size->Height + tb->Position->Y;
	int limite = 0; // quantidade de registros (-1).
	int indice = 0; // carrega nome para a listBox.
	limite = tb->Rows->Count - 1;
	int lin = tb->Location->Y + 1;
	int alt = tb->Size->Height;
	int movimento = 0;
	int retorno = -1; // assume o valor de limite.
	int i = 0; // variável contadora de "for".
	
	//gotoxy (10,3); printf("Height: %d  Y: %d",tb->Size->Height, tb->Position->Y );

	Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, posY, true);
	
	int Limit = row[0].Count - 1;
	
	while(!exit){
		//gotoxy(30, 1); printf("x: %d  y: %d  limite: %d  alt: %d  movimento: %d  elementos: %d posY: %d", x, y, limite, alt, movimento, tb->Rows->Count, posY);
		e.KeyPressed = getKey();
		
		if (e.KeyPressed == Keys.ENTER){
			exit = true;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, posY, false);			
			tb->CurrentRowIndex = CurrentRowIndex;			
			tb->onKeyEnter();
		}
		
		if (e.KeyPressed == Keys.ESC){
			exit = true;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, posY, false);			
			tb->CurrentRowIndex = CurrentRowIndex;			
			tb->onKeyEsc();
		}
		
		///
		/// Seta para cima e cursor na borda da janela e registro maior do que zero
		///
		if (e.KeyPressed == Keys.ARROW_UP && x == 0 && y > 0 ) {
			x = 0; y = y - 1; indice = indice - 1; CurrentRowIndex--;
			for(i=0; i<=(alt-1); i++){
				Table_setCurrentRow(tb, row[indice + i].items->Cells, posX, lin + i, false);
			}
			Table_setCurrentRow(tb, row[indice].items->Cells, posX, lin, true);
			tb->CurrentRowIndex = CurrentRowIndex;
			tb->onSelectChanged();
		}
		
		///
		/// Seta para cima e cursor maior do que a borda
		///
		if (e.KeyPressed == Keys.ARROW_UP && x > 0) {
			x = x - 1; y = y - 1; movimento = 0;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x + 1, false);
			CurrentRowIndex -=1; posY -=1;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x, true);
			tb->CurrentRowIndex = CurrentRowIndex;
			tb->onSelectChanged();
		}
		///
		/// Seta para baixo e cursor menor que o limite da janela e o vetor menor que o limite (-1)
		///
		if (e.KeyPressed == Keys.ARROW_DOWN && x<=(alt-2) && y < limite) {			
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x, false);
			CurrentRowIndex +=1; posY +=1;
			x = x + 1; y = y + 1;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x, true);
			tb->CurrentRowIndex = CurrentRowIndex;
			tb->onSelectChanged();
		}
		///
		/// Seta para baixo se o cursor estiver na ultima linha e houver registros
		///		
		if (e.KeyPressed == Keys.ARROW_DOWN && x == (alt-1) && y < (limite) && movimento == 1){
			y = y + 1; x = alt - 1;  posY +=1; indice++;
			for(i = 0; i<=(alt - 2); i++){
				Table_setCurrentRow(tb, row[indice + i].items->Cells, posX, lin + i, false);
			}			
			CurrentRowIndex++;
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x, true);
			tb->CurrentRowIndex = CurrentRowIndex;
			tb->onSelectChanged();
		}
		
		///
		/// Seta para baixo se o cursor estiver na ultima linha e houver registros
		///			
		if (e.KeyPressed == Keys.ARROW_DOWN && x == (alt-1) && y < (limite) && movimento == 0){
			movimento = 1; x = alt - 1; //posY +=1;
			for(i = 0; i<=(alt - 2); i++){
				Table_setCurrentRow(tb, row[indice + i].items->Cells, posX, lin + i, false);
			}
			Table_setCurrentRow(tb, row[CurrentRowIndex].items->Cells, posX, lin + x, true);			
			tb->CurrentRowIndex = CurrentRowIndex;
			tb->onSelectChanged();
		}
		
	}
}

// Operações com listas


List_Of_Table *new_List_Of_Table(){
	List_Of_Table *List = (List_Of_Table *) malloc(sizeof(List_Of_Table));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_Table(List_Of_Table *object){
	free(object);
}

// Adiciona um objeto na lista.
void AddTableIn(List_Of_Table *p, Table *object){
	List_Of_Table *new_item = malloc(sizeof(List_Of_Table));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddTableIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_Table_From(List_Of_Table *p){
	
	List_Of_Table *temp = p;
	
	while(temp->next != NULL){	
		//MsgBox(temp->next->item->Name);
		//if (temp->next->item->Rows->Count > 0)
			Table_SetVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_Table(List_Of_Table *p){
	int i = 0;
	
	List_Of_Table *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}
//
