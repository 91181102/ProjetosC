// Class MenuItem
void AddMenuOption(MenuOption *object);

typedef struct MENU_ITEM{
	string Text;
	string Name;
	LOCATION *Location;
	int Width;
	KeyEvents Event;
	List_Of_Menu_Option *DropDownItems;
	void (*AddMenuOption)(MenuOption *object);
	struct char_info *screen_buffer;
}MenuItem;

typedef struct LIST_OF_MENU_ITEM{
	int Lenght;	
	MenuItem *item;
	struct LIST_OF_MENU_ITEM *next;
}List_Of_Menu_Item;

MenuItem *GLOBAL_MenuItem;

MenuItem *new_MenuItem(string Name, string Text);
MenuItem *getMenuItem(MenuItem *object);
void MenuItem_setVisible(MenuItem *object);
bool MenuItem_setFocus(MenuItem *object);
void MenuItem_lostFocus(MenuItem *object);
void MenuItem_getBackground(MenuItem *a);
void MenuItem_Dispose(MenuItem *a);
void MenuItem_DrawFrame(MenuItem *a);
void AddMenuOption(MenuOption *object);
List_Of_Menu_Item *new_List_Of_Menu_Item();
void Dispose_List_Of_Menu_Item(List_Of_Menu_Item *object);
void AddMenuItemIn(List_Of_Menu_Item *p, MenuItem *object);
void Show_MenuItem_From(List_Of_Menu_Item *p);
int Count_Item_From_List_Of_Menu_Item(List_Of_Menu_Item *p);


/* Cria um novo MenuItem na memória. */
MenuItem *new_MenuItem(string Name, string Text){
	MenuItem *object = malloc(sizeof(MenuItem));
	
	object->Name = Name;
	object->Text = Text;
	object->Location = setLocation(1,1);
	object->Width = strlen(Text) + 2;
	object->AddMenuOption = AddMenuOption;
	object->DropDownItems = new_List_Of_Menu_Option();
	GLOBAL_MenuItem = object;
	
	return object;
}

/* Mantém o MenuItem na variável global. */
MenuItem *getMenuItem(MenuItem *object){
	GLOBAL_MenuItem = object;
	return GLOBAL_MenuItem;
}

/* Exibe o MenuItem na tela. */
void MenuItem_setVisible(MenuItem *object){	
	gotoxy(object->Location->X, object->Location->Y);
	textcolor(Color.Black);
	textbackground(Color.LightGray);
	strings(object->Width + 1, 32);
	gotoxy(object->Location->X + 1, object->Location->Y);	
	printf("%s", object->Text);			
}

/* Mantém o foco num MenuItem até que uma tecla seja pressionada. */
bool MenuItem_setFocus(MenuItem *object){
	// Posiciona o menu nas coordenadas x e y.
	gotoxy(object->Location->X, object->Location->Y);
	textcolor(Color.Black);
	textbackground(Color.White);
	// Desenha espaços vazios.
	strings(object->Width + 1, 32);
	gotoxy(object->Location->X + 1, object->Location->Y);
	// Escreve o texto do menuItem.
	printf("%s", object->Text);	
	
	// Exibe a caixa de subMenu caso tenha itens.
	if (object->DropDownItems->Count > 0){
		MenuItem_getBackground(object);
		MenuItem_DrawFrame(object);
		MenuItem_Focus(object, true);
	}
		
	// Espera uma tecla ser pressionada.
	object->Event.KeyPressed = getKey();
	MenuItem_lostFocus(object);
		
	// Retorna a tecla pressionada para o controle do menu.
	if (object->Event.KeyPressed == Keys.ESC){	
		return true;	
	}
	else{
		MenuItem_setVisible(object);		
		return false;
	}
}

/* Perde o foco no MenuItem. */
void MenuItem_lostFocus(MenuItem *object){
	if (object->DropDownItems->Count > 0)
		MenuItem_Dispose(object);
}

/* Salva a imagem de fundo. */
void MenuItem_getBackground(MenuItem *a){
	//gotoxy(1,20); printf("X: %d  Y: %d  MaxLenght: %d  Count: %d", a->Location->X, a->Location->Y + 1, a->DropDownItems->MaxLenght, a->DropDownItems->Count);
	int posX = a->Location->X;
	int posY = a->Location->Y + 1;
	int larg = a->DropDownItems->MaxLenght + 4;
	int alt = a->DropDownItems->Count + 2;
	int xCol = posX;
	int xLin = posY;
	
	a->screen_buffer = malloc((xCol + larg + 1) * (xLin + alt + 1) * sizeof(struct char_info));
	_conio_gettext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);
}

// Fecha o DropDown e restaura a tela.
void MenuItem_Dispose(MenuItem *a){
	int posX = a->Location->X;
	int posY = a->Location->Y + 1;
	int larg = a->DropDownItems->MaxLenght + 4;
	int alt = a->DropDownItems->Count + 2;
	int xCol = posX;
	int xLin = posY;

	puttext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);
	normvideo();
	free(a->screen_buffer); 
}

// Desenha a comboBox na tela.
void MenuItem_DrawFrame(MenuItem *a){
	int posX = a->Location->X;
	int posY = a->Location->Y + 1;
	int xCol = posX;
	int xLin = posY;
	int larg = a->DropDownItems->MaxLenght + 4;
	int alt = a->DropDownItems->Count + 1;
	int Vertical = 186;
	int Left_Up = 201;
	int	Horizon = 205;	
	int	Right_Up = 187;
	int	Left_Down = 200;
	int	Right_Down = 188;
	
	int i = 0, j = 0;		
		
	// Desenha a sombra.-------------	
	textbackground(Color.Black);	
	textcolor(Color.White);	
	for (i = 1; i < alt + 2; i++) {
       	gotoxy(posX + 1, posY + i);
		strings(larg + 1, 32);
	}
	
	//-------------------------------
	textbackground(Color.White);	
	textcolor(Color.Black);
	// Desenha a parte superior da borda	
	gotoxy(posX, posY);
	putchar(Left_Up);
	strings(larg - 1, Horizon);	
	putchar(Right_Up);
    gotoxy(posX + 1, posY);
    
	// Desenha a caixa.-------------
	for (i = 0; i < alt; i++) {   	
		gotoxy(xCol, xLin + i + 1);
		putchar(Vertical);
		//textbackground(Color.White);	
		//textcolor(Color.Black);		
		strings(larg - 1 , 32);	
		gotoxy(posX + (larg - 1), posY + i + 1);
        putchar(Vertical); printf("\n");	
	}
	
	// Desenha a parte inferior da borda	
	gotoxy(posX, posY + i);
	putchar(Left_Down);
	for (j=1; j<=larg-2; j++)	
		putchar(Horizon);
	putchar(Right_Down);
}

/* Adiciona uma opção no MenuItem */
void AddMenuOption(MenuOption *object){
	//printf("\n%s: len: %d", object->Text, strlen(object->Text));
	
	if(GLOBAL_MenuItem->DropDownItems->MaxLenght < strlen(object->Text)){
		GLOBAL_MenuItem->DropDownItems->MaxLenght = strlen(object->Text);	
	}
	GLOBAL_MenuItem->DropDownItems->Count += 1;
	AddMenuOptionIn(GLOBAL_MenuItem->DropDownItems, object);
}

//----------------------
// Operações com listas.
//----------------------
/* Cria uma nova lista de MenuItem */
List_Of_Menu_Item *new_List_Of_Menu_Item(){
	List_Of_Menu_Item *List = (List_Of_Menu_Item *) malloc(sizeof(List_Of_Menu_Item));
	List->item = NULL;
	List->next = NULL;
	List->Lenght = 0;	
	return List;
}


/* Limpa a lista de menu da memória. */
void Dispose_List_Of_Menu_Item(List_Of_Menu_Item *object){
	free(object);
}


/* Adiciona um objeto na lista. */
void AddMenuItemIn(List_Of_Menu_Item *p, MenuItem *object){
	List_Of_Menu_Item *new_item = malloc(sizeof(List_Of_Menu_Item));	
		
	new_item->item = object;
	new_item->next = NULL;
	new_item->Lenght = 0;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddMenuItemIn(p->next, object);
	}	
}

// Posiciona na tela todos os objetos da lista.
void Show_MenuItem_From(List_Of_Menu_Item *p){
	List_Of_Menu_Item *temp = p;
	
	while(temp->next != NULL){	
		MenuItem_setVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_Menu_Item(List_Of_Menu_Item *p){
	int i = 0;
	
	List_Of_Menu_Item *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


//----------------------------------------------------
// Navega na lista do menu
//----------------------------------------------------

/* Carrega uma lista de nomes. */
void MenuItem_LoadLista(MenuItem *object, LISTA a[]){
	List_Of_Menu_Option *temp = object->DropDownItems;
	int i = 0;
	// Popula o vetor com os nomes dos itens do comboBox.	
	while(Options_hasNext(temp)){
		a[i].cod = i;
		strcpy(a[i].nome, temp->next->item->Text);
		//printf("\n%d %s",a[i].cod, a[i].nome);
		temp = temp->next;
		i++;
	}
}

void MenuItem_Focus(MenuItem *object, bool isFocused){	
	// Obtém a quantidade de elementos.	
	int indice = object->DropDownItems->Count;
	
	// Define um vetor.
	LISTA a[indice];
	// Obtém a lista de itens.
	MenuItem_LoadLista(object, &a);
	
	// Continua se houver elementos na lista.
	if (object->DropDownItems->Count > 0){
		// Exibe os itens.	
		MenuItem_ShowItems(object, a, indice);
		// Movimenta o cursor.
		if (isFocused){
			MenuItem_Mov(object, a);
		}
	}
}

// Mostra os itens do ComboBox.
void MenuItem_ShowItems(MenuItem *object, LISTA lista[], int index){	
	int i = 0;
	
	//textcolor(cbo->ForeColor);
	//textbackground(cbo->BackColor);
	
	for (i = 0; i <object->DropDownItems->Count; i++){
		gotoxy(object->Location->X + 2, object->Location->Y + i + 2);
		printf("%s", lista[i].nome);
	}
	
	// Exibe o primeiro elemento selecionado.
	textcolor(Color.White);
	textbackground(Color.Black);	
	gotoxy(object->Location->X + 1, object->Location->Y + 2);
	strings(object->DropDownItems->MaxLenght + 3, 32);
	gotoxy(object->Location->X + 2, object->Location->Y + 2);
	printf("%s", lista[0].nome);
}


// Movimenta o cursor na lista da ComboBox.
void MenuItem_Mov(MenuItem *object, LISTA lista[]){
	// Inicializa variaveis	
	int x = 0; // linha que movimento o cursor.
	int y = 0; // linha que guarda o registro da posição do cursor.
	int lin = object->Location->Y + 2;
	int col = object->Location->X;
	int limite = 0; // quantidade de registros (-1).
	int retorno = -1; // assume o valor de limite.
	int indice = 0; // carrega nome para a listBox.
	int movimento = 0;// habilita ou desabilita a rolagem dos itens da listBox.
	int registro = 0;
	bool Exit = false; // Encerra a listBox quando sair=1.
	int botao; // tecla apertada.
	int limpar = object->DropDownItems->MaxLenght + 3; // tamanho do campo nome para ser limpo na movimentação do cursor.
	int i = 0; // variável contadora de "for".
	bool alterado = false;
	KeyEvents e;
	
	LISTA nomes[object->DropDownItems->Count];
	MenuItem_LoadLista(object, &nomes);
	
	// Variavel limite recebe o total de registros.
	limite = object->DropDownItems->Count - 1;
	int alt = object->DropDownItems->Count + 1;
	
	// Movimenta o cursor dentro da janela.
	do{
		//gotoxy(30, 1); printf("Metodo do menu");
		//gotoxy(30, 1); printf("x: %d  y: %d  limite: %d  alt: %d  movimento: %d  elementos: %d", x, y, limite, alt, movimento, object->DropDownItems->Count);
		
		// Verifica a tecla pressionada.		
		if (!Exit ){
			GLOBAL_KeyEvents.KeyPressed = getKey();	
		}		
		
		if (GLOBAL_KeyEvents.KeyPressed == Keys.ARROW_LEFT || GLOBAL_KeyEvents.KeyPressed == Keys.ARROW_RIGHT) { 
			Exit = true;		
			return;		
		}
		
		// Executa o método do MenuOption.
		if (GLOBAL_KeyEvents.KeyPressed == Keys.ENTER){
			Exit = true;
			MenuItem_setVisible(object);			
			getMenuOptionByIndex(object->DropDownItems, y)->OnKeyEnter();			
			return;
		}
		
		///
		/// Seta para cima e cursor maior do que a borda
		///
		if (GLOBAL_KeyEvents.KeyPressed == Keys.ARROW_UP && x > 0) {
			x = x - 1; y = y - 1; movimento = 0;
			textcolor(Color.Black);
			textbackground(Color.White);			
			gotoxy(col + 1, lin + x + 1); strings(limpar,32); 
			gotoxy(col + 2, lin + x + 1); printf("%s", nomes[y + 1].nome); 
			textcolor(Color.White);
			textbackground(Color.Black);
			gotoxy(col + 1, lin + x); strings(limpar, 32);
			gotoxy(col + 2, lin + x); printf("%s", nomes[y].nome);
			alterado = true;
		}
		
		///
		/// Seta para baixo e cursor menor que o limite da janela e o vetor menor que o limite (-1)
		///
		if (GLOBAL_KeyEvents.KeyPressed == Keys.ARROW_DOWN && x<=(alt-1) && y < limite) {
			textcolor(Color.Black);
			textbackground(Color.White);
			gotoxy(col + 1, lin + x); strings(limpar,32); 
			gotoxy(col + 2, lin + x); printf("%s", nomes[y].nome); 
			x = x + 1; y = y + 1;
			textcolor(Color.White);
			textbackground(Color.Black);
			gotoxy(col + 1, lin + x); strings(limpar, 32);
			gotoxy(col + 2, lin + x); printf("%s", nomes[y].nome);
			alterado = true;
		}		
	} while(Exit == false);
}
//
