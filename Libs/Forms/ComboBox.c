// Classe ComboBox{

#include <stdio.h>
#include <stdlib.h>

void Add_Item(int Cod, string Text);
void SetSelectedIndex(int index);

typedef struct combo{
	int cod;
	char nome[30];
}LISTA;



typedef struct Combobox{
	string Name;
	int BackColor;
	int ForeColor;
	int SelectBackColor;
	int SelectForeColor;
	int SelectedIndex;
	int Count;
	KeyEvents Event;
	string Text;	
	_SIZE *Size;
	LOCATION *Location;
	Items *Item;
	struct char_info *screen_buffer;
	void (*Add_Item)(int Cod, string Text);
	void (*SetSelectedIndex)(int index);
}ComboBox;

ComboBox *GLOBAL_ComboBox;

typedef struct LIST_OF_COMBOBOX{
	ComboBox *item;
	struct LIST_OF_COMBOBOX *next;
}List_Of_ComboBox;


// Cria um novo comboBox.
ComboBox *new_ComboBox(){
	ComboBox *cbo = malloc(sizeof(ComboBox));
	
	cbo->Location = setLocation(1, 1);
	cbo->Size = new_size(12, 6);
	cbo->BackColor = Color.Red;
	cbo->ForeColor = Color.Yellow;
	cbo->SelectBackColor = Color.Yellow;
	cbo->SelectForeColor = Color.Black;
	cbo->Item = new_Item();	
	cbo->SelectedIndex = 0;
	cbo->Count = 0;
	cbo->Text = "Select";
	cbo->Name = "ComboBox1";
	cbo->Add_Item = Add_Item;
	cbo->SetSelectedIndex = SetSelectedIndex;
	cbo->Event.KeyPressed = 0;
	
	return cbo;
}

// Cria um novo ComboBox.
ComboBox *new_comboBox(string Name, int BackColor, int ForeColor, int X, int Y, int width){
	ComboBox *cbo = new_ComboBox();
	
	cbo->Name = Name;
	cbo->Location->X = X;
	cbo->Location->Y = Y;
	cbo->Size->Width = width;
	cbo->BackColor = BackColor;
	cbo->ForeColor = ForeColor;
	
	return cbo;
}

// Salva a imagem de fundo.
void ComboBox_getBackground(ComboBox *a){
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	int xCol = posX;
	int xLin = posY;
	
	a->screen_buffer = malloc((xCol + larg + 1) * (xLin + alt + 1) * sizeof(struct char_info));
	_conio_gettext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);	
}

// Fecha o comboBox e restaura a tela.
void ComboBox_Dispose(ComboBox *a){
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	int xCol = posX;
	int xLin = posY;
	
	///
	/// Fecha janela e esvazia o buffer
	///
	puttext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);
	normvideo();
	free(a->screen_buffer); 
}


// Exibe o comboBox na tela.
void ComboBox_setVisible(ComboBox *object){	
	gotoxy(object->Location->X, object->Location->Y);
	textcolor(object->ForeColor);
	textbackground(object->BackColor);
	strings(object->Size->Width + 1, 32);
	gotoxy(object->Location->X + object->Size->Width, object->Location->Y);
	strings(2, 176);
	gotoxy(object->Location->X, object->Location->Y);
	printf("%s", object->Text);	
	//printf("%d", object->Count);
}

// Adiciona um novo item ao ComboBox.
void ComboBox_AddItem(ComboBox *cbo, int Cod, string Text){	
	AddItem(cbo->Item, Cod, Text);
	cbo->Count = Count_Item_From_ComboBox(cbo->Item);
}
 
 
 // Adiciona um novo item ao ComboBoxGlobal.
 void Add_Item(int Cod, string Text){
 	AddItem(GLOBAL_ComboBox->Item, Cod, Text);
 	GLOBAL_ComboBox->Count = Count_Item_From_ComboBox(GLOBAL_ComboBox->Item);
 }
 
 //Invoca o comboBoxGlobal.
 ComboBox *getComboBox(ComboBox *cbo){
 	GLOBAL_ComboBox = cbo;
 	return GLOBAL_ComboBox;
 }
 
 // Conta quantos elementos há na lista.
int Count_Item_From_ComboBox(Items *p){
	int i = 0;
	
	Items *temp = p;
		
	while(items_hasNext(temp)){
		i++;
		temp = temp->next;		
	}
	return i;
}


// Desenha a comboBox na tela.
void ComboBox_DrawFrame(ComboBox *a){
	int posX = a->Location->X;
	int posY = a->Location->Y + 1;
	int xCol = posX;
	int xLin = posY;
	int larg = a->Size->Width;
	int alt = a->Size->Height;
	
	if(a->Size->Height > a->Count + 2){	
		alt = a->Count + 2;
		a->Size->Height = alt;
	}	
	
	int i = 0, j = 0;		
		
	// Desenha a sombra.-------------	
	textbackground(Color.Black);	
	textcolor(a->ForeColor);
	
	for (i = 1; i < alt; i++) {
       	gotoxy(posX + 1, posY + i);
		strings(larg + 1, ' ');
	}
	//-------------------------------
	
	// Desenha a caixa.-------------	
	textbackground(a->ForeColor);	
	textcolor(a->BackColor); 
	for (i = 0; i < alt; i++) {   	
		gotoxy(xCol, xLin + i);
		textbackground(a->BackColor);	
		textcolor(a->ForeColor);		
		strings(larg + 1 , 32);		
	}
	
	// Desenha as bordas.-------------
	textbackground(Color.White);	
	textcolor(a->ForeColor);
	gotoxy(xCol, xLin);			
	strings(larg + 1, 223);	
	
	textbackground(Color.Black);	
	textcolor(a->BackColor);
	gotoxy(xCol, xLin + alt - 1); 
	strings(larg + 1, 223);
}


void ComboBox_LoadLista(ComboBox *cbo, LISTA a[]){
	Items *temp = cbo->Item;
	int i = 0;
	// Popula o vetor com os nomes dos itens do comboBox.	
	while(items_hasNext(temp)){
		a[i].cod = temp->next->Cod;
		strcpy(a[i].nome, temp->next->Text);
		//printf("\n%d %s",a[i].cod, a[i].nome);
		temp = temp->next;
		i++;
	}
}

// Ativa o controle na ComboBox.
void ComboBox_Focus(ComboBox *cbo){
	// Guarda o fundo.
	ComboBox_getBackground(cbo);
	// Desenha a caixa.
	ComboBox_DrawFrame(cbo);
	
	// Obtém a quantidade de elementos.	
	int indice = cbo->Count;
	
	// Define um vetor.
	LISTA a[indice];
	// Obtém a lista de itens.
	ComboBox_LoadLista(cbo, &a);	
	
	// Continua se houver elementos na lista.
	if (cbo->Count > 0){
		// Exibe os itens.	
		ComboBox_ShowItems(cbo, a, indice);
		// Movimenta o cursor.
		ComboBox_Mov(cbo, a);	
	}
	// Fecha a lista e retorna o fundo.
	ComboBox_Dispose(cbo);
	ComboBox_setVisible(cbo);
}


// Mostra os itens do ComboBox.
void ComboBox_ShowItems(ComboBox *cbo, LISTA lista[], int index){	
	int i = 0;
	
	textcolor(cbo->ForeColor);
	textbackground(cbo->BackColor);
	
	for (i = 0; i <cbo->Size->Height - 2; i++){
		gotoxy(cbo->Location->X, cbo->Location->Y + i + 2);
		printf("%s", lista[i].nome);
	}
	
	// Exibe o primeiro elemento selecionado.
	textcolor(cbo->SelectForeColor);
	textbackground(cbo->SelectBackColor);	
	gotoxy(cbo->Location->X, cbo->Location->Y + 2);
	strings(cbo->Size->Width + 1, 32);
	gotoxy(cbo->Location->X, cbo->Location->Y + 2);
	printf("%s", lista[0].nome);
}


// Movimenta o cursor na lista da ComboBox.
void ComboBox_Mov(ComboBox *cbo, LISTA lista[]){
	// Inicializa variaveis	
	int x = 0; // linha que movimento o cursor.
	int y = 0; // linha que guarda o registro da posição do cursor.
	int lin = cbo->Location->Y + 2;
	int col = cbo->Location->X;
	int limite = 0; // quantidade de registros (-1).
	int retorno = -1; // assume o valor de limite.
	int indice = 0; // carrega nome para a listBox.
	int movimento = 0;// habilita ou desabilita a rolagem dos itens da listBox.
	int registro = 0;
	bool Exit = 0; // Encerra a listBox quando sair=1.
	int botao; // tecla apertada.
	int limpar = cbo->Size->Width + 1; // tamanho do campo nome para ser limpo na movimentação do cursor.
	int i = 0; // variável contadora de "for".
	bool alterado = false;
	KeyEvents e;
	
	LISTA nomes[cbo->Count];
	ComboBox_LoadLista(cbo, &nomes);
	
	// Variavel limite recebe o total de registros.
	limite = cbo->Count - 1;
	int alt = cbo->Size->Height;
	
	if(alt > cbo->Count + 1){	
		limite = cbo->Count;
		alt = cbo->Count + 3;
	}
	
		
	// Movimenta o cursor dentro da janela.
	do{
		//gotoxy(30, 1); printf("x: %d  y: %d  limite: %d  alt: %d  movimento: %d  elementos: %d", x, y, limite, alt, movimento, cbo->Count);
		// Verifica a tecla pressionada.
		e.KeyPressed = getKey();
		//cbo->Event->KeyPressed = getKey();
				
		if (e.KeyPressed == Keys.ENTER) { 
			Exit = true; 
			if (alterado)
				ComboBox_setTextByIndex(cbo, y);			
		}
		
		if (e.KeyPressed == Keys.ESC) { Exit = true; retorno = -1;	}
		///
		/// Seta para cima e cursor na borda da janela e registro maior do que zero
		///
		if (e.KeyPressed == Keys.ARROW_UP && x == 0 && y > 0 ) {
			x = 0; y = y - 1; indice = indice - 1;
			textcolor(cbo->ForeColor);
			textbackground(cbo->BackColor);
			for(i=0; i<=(alt-3); i++){
				gotoxy(col, lin + i); strings(limpar,32);
				gotoxy(col, lin + i); printf("%s", nomes[indice + i].nome);					
			}
			textcolor(cbo->SelectForeColor);
			textbackground(cbo->SelectBackColor);
			gotoxy(col, lin); strings(limpar, 32);
			gotoxy(col, lin); printf("%s", nomes[y].nome);
			alterado = true;
		}
		///
		/// Seta para cima e cursor maior do que a borda
		///
		if (e.KeyPressed == Keys.ARROW_UP && x > 0) {
			x = x - 1; y = y - 1; movimento = 0;
			textcolor(cbo->SelectForeColor);
			textbackground(cbo->SelectBackColor);
			gotoxy(col, lin + x); strings(limpar, 32);
			gotoxy(col, lin + x); printf("%s", nomes[y].nome);			
			textcolor(cbo->ForeColor);
			textbackground(cbo->BackColor);
			gotoxy(col, lin + x + 1); strings(limpar,32);
			gotoxy(col, lin + x + 1); printf("%s", nomes[y+1].nome);	
			alterado = true;
		}
		///
		/// Seta para baixo e cursor menor que o limite da janela e o vetor menor que o limite (-1)
		///
		if (e.KeyPressed == Keys.ARROW_DOWN && x<=(alt-4) && y < limite - 1) {
			textcolor(cbo->ForeColor);
			textbackground(cbo->BackColor);
			gotoxy(col, lin + x); strings(limpar,32); 
			gotoxy(col, lin + x); printf("%s", nomes[y].nome); 
			x = x + 1; y = y + 1;
			textcolor(cbo->SelectForeColor);
			textbackground(cbo->SelectBackColor);
			gotoxy(col, lin + x); strings(limpar, 32);
			gotoxy(col, lin + x); printf("%s", nomes[y].nome);
			alterado = true;
		}
		///
		/// Seta para baixo se o cursor estiver na ultima linha e houver registros
		///		
		if (e.KeyPressed == Keys.ARROW_DOWN && x == (alt-3) && y < (limite) && movimento == 1){
			y = y + 1; indice = indice + 1; x = alt - 3;
			for(i = 0; i<=(alt - 3); i++){
				textcolor(cbo->ForeColor);
				textbackground(cbo->BackColor);
				gotoxy(col, lin + i); strings(limpar,32);
				gotoxy(col, lin + i); printf("%s", nomes[indice + i].nome);
			}
			textcolor(cbo->SelectForeColor);
			textbackground(cbo->SelectBackColor);
			gotoxy(col, lin + x); strings(limpar, 32);
			gotoxy(col, lin + x); printf("%s", nomes[y].nome);
			alterado = true;
		}
		///
		/// Seta para baixo se o cursor estiver na ultima linha e houver registros
		///			
		if (e.KeyPressed == Keys.ARROW_DOWN && x == (alt - 3) && y < (limite) && movimento == 0){
			movimento = 1; x = alt - 3;
			for(i = 0; i<=(alt - 3); i++){
				textcolor(cbo->ForeColor);
				textbackground(cbo->BackColor);
				gotoxy(col, lin + i); strings(limpar,32);
				gotoxy(col, lin + i); printf("%s", nomes[indice + i].nome);
			}
			textcolor(cbo->SelectForeColor);
			textbackground(cbo->SelectBackColor);
			gotoxy(col, lin + x); strings(limpar, 32);
			gotoxy(col, lin + x); printf("%s", nomes[y].nome);
			alterado = true;
		}
		
		textcolor(cbo->ForeColor);
		textbackground(cbo->BackColor);
		gotoxy(cbo->Location->X, cbo->Location->Y);
		strings(limpar, 32);
		gotoxy(cbo->Location->X, cbo->Location->Y);
		printf("%s", nomes[y].nome);	
		
		
	} while(Exit == false);
}
//}

void ComboBox_setTextByIndex(ComboBox *cbo, int index){
	Items *temp = cbo->Item;
	int i = 0;
	// Verifica qual o índice selecionado.
	while(items_hasNext(temp)){
		if (i == index){
			cbo->Text = temp->next->Text;
			cbo->SelectedIndex = i;
		}		
		temp = temp->next;
		i++;
	}
}

void SetSelectedIndex(int index){
	ComboBox_setTextByIndex(GLOBAL_ComboBox, index);
}


//----------------------
// Operações com listas.
//----------------------

List_Of_ComboBox *new_List_Of_ComboBox(){
	List_Of_ComboBox *List = (List_Of_ComboBox *) malloc(sizeof(List_Of_ComboBox));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_ComboBox(List_Of_ComboBox *object){
	free(object);
}

// Adiciona um objeto na lista.
void AddComboBoxIn(List_Of_ComboBox *p, ComboBox *object){
	List_Of_ComboBox *new_item = malloc(sizeof(List_Of_ComboBox));	
		
	new_item->item = object;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddComboBoxIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_ComboBox_From(List_Of_ComboBox *p){
	List_Of_ComboBox *temp = p;
	
	while(temp->next != NULL){	
		ComboBox_setVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_ComboBox(List_Of_ComboBox *p){
	int i = 0;
	
	List_Of_ComboBox *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


