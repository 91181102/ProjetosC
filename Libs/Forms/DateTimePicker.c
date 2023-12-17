// class DateTimePicker
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include "conio2.h"
//#include "conio.c"

typedef struct data{
	char Short[10];
	int year;
	int month;
	int day;
	int week;
	char Value[10];	
	char Long[50];
	int BackColor;
	int ForeColor;
	struct tm *local;	
	time_t t;
}__DATE;

typedef struct datetimepicker{
	int Value;
	string Name;
	int BackColor;
	int ForeColor;
	int BorderForeColor;
	int ActiveBackColor;
	int ActiveForeColor;
	int TextBackColor;
	int TextForeColor;
	int Length;
	LOCATION *Location;
	int Width;
	__DATE *Date;
	struct char_info *screen_buffer;
}DateTimePicker;

typedef struct LIST_OF_DATETIMEPICKER{
	DateTimePicker *item;
	struct LIST_OF_DATETIMEPICKER *next;
}List_Of_DateTimePicker;

// Salva a imagem de fundo.
void Calendary_getBackground(DateTimePicker *a){
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Width;
	int alt = 11;
	int xCol = posX;
	int xLin = posY;	
	
	a->screen_buffer = malloc((xCol + larg + 1) * (xLin + alt + 1) * sizeof(struct char_info));
	_conio_gettext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);	
}


__DATE *new_Date(int day, int month, int year){
	__DATE *date = malloc(sizeof(__DATE));
	
	date->BackColor = Color.White;
	date->ForeColor = Color.Black;	
	date->t = time(NULL);
	date->local = localtime(&date->t);
	date->day = day;
	date->month = month;
	date->year = year;
	date->week = date->local->tm_wday;
	
	return date;
}

void setDate(__DATE *date, int day, int month, int year){
	date->t = time(NULL);
	date->local = localtime(&date->t);
	
	struct tm tm = {0};
	tm.tm_year = year - 1900;
	tm.tm_mday = day;
	tm.tm_mon = month - 1;
	mktime(&tm); 

	 
	
	date->year = year; 
	date->month = month - 1;
	date->day = day;
	date->week = calculo_dia_da_semana(day, month, year);
		
}



// Cria um novo DateTimePicker na memória.
DateTimePicker *new_DateTimePicker(){
	// Aloca memória.
	DateTimePicker *txt = malloc(sizeof(DateTimePicker));
	// Define as propriedades.
	txt->Location = setLocation(10, 15);
	txt->ForeColor = Color.White;
	txt->BorderForeColor = Color.Yellow;
	txt->BackColor = Color.Red;
	txt->ActiveBackColor = txt->ForeColor;
	txt->ActiveForeColor = txt->BackColor;
	txt->TextForeColor = txt->ForeColor;
	txt->TextBackColor = txt->BackColor;
	txt->Width = 22;		
	
	txt->Date = malloc(sizeof(__DATE));
		
	txt->Date->BackColor = Color.White;
	txt->Date->ForeColor = Color.Black;	
	txt->Date->t = time(NULL);
	txt->Date->local = localtime(&txt->Date->t);
	
	struct tm tm = {0};
	tm.tm_year = txt->Date->local->tm_year;
	tm.tm_mday = txt->Date->local->tm_mday;
	tm.tm_mon = txt->Date->local->tm_mon;
	mktime(&tm);
	 
	
	txt->Date->year = txt->Date->local->tm_year + 1900; 
	txt->Date->month = txt->Date->local->tm_mon;
	txt->Date->day = txt->Date->local->tm_mday;
	txt->Date->week = txt->Date->local->tm_wday;
	
	//setDate(txt->Date, txt->Date->day, txt->Date->month, txt->Date->year);
	//print_date(txt->Date);
	return txt;
}

DateTimePicker *new_dateTimePicker(string name, int BackColor, int ForeColor, int X, int Y){
	DateTimePicker *txt = new_DateTimePicker();
	txt->Name = name;
	txt->Location->X = X;
	txt->Location->Y = Y;
	txt->TextBackColor = BackColor;
	txt->TextForeColor = ForeColor;
	return txt;
}


void print_date(__DATE *date){	
	const char *mes1[] = {"01","02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
	if (date->day<10) {		
		printf("0%d/%s/%d", date->day, mes1[date->month], date->year);
	} else {		
		printf("%d/%s/%d", date->day, mes1[date->month], date->year);	
	}
	//printf("\n\n\n\n\n\n\nShort: %s", date->Short);
	//printf("\nLong: %s", date->Long);
	//printf("\nValue: %s", date->Value);
	//printf("\nShort: %s", date->Short);
}

void setDateTimePickerVisible(DateTimePicker *txt){
	gotoxy(txt->Location->X, txt->Location->Y - 1);
	textbackground(txt->TextBackColor);
	textcolor(txt->TextForeColor);
	strings(10, 32);
	gotoxy(txt->Location->X, txt->Location->Y - 1);
	
	print_date(txt->Date->Short);	
}

// Navega pelo calendário.
void Calendary_Focus(DateTimePicker *txtData){
	//txt_data = txtData;
	// Guarda o background.
	Calendary_getBackground(txtData);
	// Desenha o calendári ona tela.
	DateTimePicker_DrawFrame(txtData);
	// Obtém o valor da nova data.
	txtData->Value = Calendary_Navigate(
		txtData->Location->X, 
		txtData->Location->Y, 
		txtData->Location->X, 
		txtData->Location->Y - 1,
		txtData
	);	
	// Retira o calendário da tela.	
	Calendary_Dispose(txtData);
}

/* Retira o calendário da tela e restaura o background. */
void Calendary_Dispose(DateTimePicker *a){	
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Width;
	int alt = 11;
	int xCol = posX;
	int xLin = posY;	

	/// Fecha janela e esvazia o buffer
	puttext(xCol, xLin, xCol + larg + 1, xLin + alt + 1, a->screen_buffer);
	normvideo();
	free(a->screen_buffer); 
}


void DateTimePicker_DrawFrame(DateTimePicker *a){
	int posX = a->Location->X;
	int posY = a->Location->Y;
	int larg = a->Width;
	int alt = 11;
	int i = 0, j = 0;		
		
	// Desenha a sombra.----------	
	textbackground(0);	
	textcolor(15);
	for (i=1; i<alt+1; i++) {
       	gotoxy(posX + 1, posY + i);
		strings(larg + 1, ' ');
	}
	//-----------------------------
		
	// Cor de fundo e fonte.	
	textbackground(a->BackColor);	
	textcolor(a->BorderForeColor); 
	
	//Valores default para borda.	
	int Left_Up = 201;
	int Horizon = 205;
	int Vertical = 186;
	int Right_Up = 187;
	int Left_Down = 200;
	int Right_Down = 188;
	int Middle_Left = 204;
	int Middle_Right = 185;	
	
	// Desenha a parte superior da borda	
	gotoxy(posX, posY);
	putchar(Left_Up);
	strings(larg - 1, Horizon);	
	putchar(Right_Up);
    gotoxy(posX + 1, posY);
	
	// Desenha as laterais da borda	
	for (i=2; i<alt; i++) {
        gotoxy(posX , posY + (i-1));
		putchar(Vertical);
		strings(larg - 1, ' ');
		gotoxy(posX + (larg - 1), posY + (i-1));
        putchar(Vertical); printf("\n");
	}
	
	// Desenha a parte inferior da borda.
	gotoxy(posX, posY + (i - 1));
	putchar(Left_Down);
	for (j=1; j<=larg-2; j++)
		putchar(Horizon);
	putchar(Right_Down);
	
	gotoxy(posX, posY + 2);putchar(Middle_Left);
    gotoxy(posX + 1, posY + 2); strings(larg - 1, Horizon); putchar(Middle_Right);    	
	
	// Desenha a separação do ano e mês.	
	gotoxy(posX + 5, posY); putchar(203);
	gotoxy(posX + 5, posY + 2); putchar(202);
	gotoxy(posX + 5, posY + 1); putchar(186);
	
	// Coloca os dias da semana no topo.
	textbackground(a->BackColor);	
	textcolor(a->BorderForeColor); 	
	gotoxy(posX + 1, posY + 3); printf("D  S  T  Q  Q  S  S");	

}


string *getMonth(int mes){
		
	switch(mes){
		case 0:  return "Janeiro"; break;
		case 1:  return "Fevereiro"; break;
		case 2:  return "Marco"; break;
		case 3:  return "Abril"; break;
		case 4:  return "Maio"; break;
		case 5:  return "Junho"; break;
		case 6:  return "Julho"; break;
		case 7:  return "Agosto"; break;
		case 8:  return "Setembro"; break;
		case 9:  return "Outubro"; break;
		case 10:  return "Novembro"; break;
		case 11:  return "Dezembro"; break;
		default:  return "Janeiro"; break;
	}
}

string *getWeek(int semana){	
	switch(semana){
		case 0: return "domingo";
		case 1: return "segunda-feira";
		case 2: return "terça-feira";
		case 3: return "quarta-feira";
		case 4: return "quinta-feira";
		case 5: return "sexta-feira";
		case 6: return "sabado";				
		default: return "domingo";
	}
}

int calculo_dia_da_semana(int dia,int mes,int ano){
    switch (mes) {
        case 1: break;
        case 2: dia += 31; break;
        case 3: dia += 59; break;
        case 4: dia += 90; break;
        case 5: dia += 120; break;
        case 6: dia += 151; break;
        case 7: dia += 181; break;
        case 8: dia += 212; break;
        case 9: dia += 243; break;
        case 10: dia += 273; break;
        case 11: dia += 304; break;
        case 12: dia += 334; break;
    }
    /* Se o ano é um ano-bisexto E
       Se o mes de fevereiro ja passou entao acrescente um dia ao deslocamento*/
	if (((ano%4)==0) && ( ((ano%100)!=0) || ((ano%400)==0) ) && (mes > 2))
		dia += 1;
	dia += -1 + (ano-1)*365 + (ano-1)/4 -(ano-1)/100 +(ano-1)/400 ;            
                
    return dia % 7;
}               



int Calendary_Navigate(int posX, int posY, int coluna, int linha, DateTimePicker *txt_data){	
	int ano, mes, dia, semana, data1;
	char data[8], dia1[2]; // variaveis para armazenar a data com 8 digitos e o dia com 2 digitos
	const char *mes1[] = {"01","02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
	KeyEvents e;

	// matriz pra guardar os dias dentro do mes
	int diaDoMes[6][6]; 
	// cria estrutura tm para armazenar data
	struct tm tm = {0}; 
	
	ano = txt_data->Date->year;
	mes = txt_data->Date->month;
	dia = txt_data->Date->day;
	semana = txt_data->Date->week;
		
	int x = posX, y = posY, i = 0, j = semana, jj = j * 3, dias, xLin = x + 4, xCol = y;	
	int op = 0, desenhar = 2;
	bool exit = false;		

	// Estrutura para escolher o dia
	do{ 
		// escolhe o mes e o ano
		if (desenhar == 2){	
			desenhar = 1; x = posX; y = posY;
			
			if (mes < 0) {
				mes = 11; 
				ano = ano - 1; 
				tm.tm_year = ano - 1900;
			}
			
			if (mes > 11) {
				mes = 0; 
				ano = ano + 1; 
				tm.tm_year = ano - 1900;
			}
			
			tm.tm_year = ano - 1900;
			tm.tm_mday = 1;
			tm.tm_mon = mes;
			// Reseta a nova data informada
			mktime(&tm); 
			semana = tm.tm_wday;
						
			// Ano e Mes
			cor(txt_data->ForeColor,txt_data->BackColor);
			// Escreve o ano.
			gotoxy(x + 1, y + 1); printf("%d", ano);
			for (i = 0; i < 6; i++){
				cor(txt_data->ForeColor,txt_data->BackColor); 
				gotoxy(x + 1, i + y + 4); strings(21, 32); 
			}			
			
			// Imprime o mês no calendário e obtém a quantidade de dias.
			dias = getDaysMonth(mes, ano, true, txt_data->Location);
			// verifica se o dia atual da posição do cursor é maior que os dias do mês
			if (dia > dias) dia = dias; 
		}		
		
		if (desenhar == 1){	
			desenhar = 0; i = 0; j = semana;
			jj = 0; jj = j * 3; x = posX;
			xLin = 0; xLin = y + 4; 
			xCol = 0; xCol = x;
						
			for(x = 0; x < 31; x++){
				diaDoMes[i][j] = x + 1; 
				if (x >= dias) diaDoMes[i][j] = NULL; 
				if (i < 10) gotoxy((xCol + jj + 1), xLin + i);
				
				// Verifica se a coluna é domingo ou outro dia.
				if (j == 0) 
					cor(txt_data->BorderForeColor,txt_data->BackColor); 
				else 
					cor(txt_data->ForeColor,txt_data->BackColor);
				
				// Marca o dia ativo.
				if (diaDoMes[i][j] == dia) 
					cor(txt_data->ActiveForeColor,txt_data->ActiveBackColor);
				
				if (diaDoMes[i][j] != 0) printf("%d", diaDoMes[i][j]);
				else strings(3, 32);
				j = j + 1; jj = jj + 3;
				if (j == 7){
					j = 0; i = i + 1; jj = 0;
				}
			}				
		}
		
		// Cor de fonte e fundo do texto da data.
		cor(txt_data->Date->ForeColor, txt_data->Date->BackColor);
		txt_data->Date->year = ano;
		txt_data->Date->month = mes;
		txt_data->Date->day = dia;
		txt_data->Date->week = calculo_dia_da_semana(dia,mes,ano);
			
		if (dia<10) {
			sprintf(txt_data->Date->Value, "%d%s0%d", ano, mes1[mes], dia);
			sprintf(txt_data->Date->Short, "0%d/%s/%d", dia, mes1[mes], ano);
			sprintf(txt_data->Date->Long, "%s, %d de %s de %d", getWeek(semana), dia, getMonth(mes), ano);
		}else {			
			sprintf(txt_data->Date->Value, "%d%s%d", ano, mes1[mes], dia);
			sprintf(txt_data->Date->Short, "%d/%s/%d", dia, mes1[mes], ano);
			sprintf(txt_data->Date->Long, "%s, %d de %s de %d", getWeek(semana), dia, getMonth(mes), ano);
		}
		gotoxy(coluna, linha); printf("%s", txt_data->Date->Short);
		data1 = atoi(txt_data->Date->Value);
				
		e.KeyPressed = getKey();
		
		if (e.KeyPressed == Keys.ESC) exit = true;
		if (e.KeyPressed == Keys.ENTER) exit = true;
		if (e.KeyPressed == Keys.TAB) exit = true;
		if ((e.KeyPressed == Keys.ARROW_LEFT) && (dia - 1 > 0)) { dia = dia - 1; desenhar = 1; }
		if ((e.KeyPressed == Keys.ARROW_RIGHT) && (dia + 1 < dias + 1)) { dia = dia + 1; desenhar = 1; }
		if ((e.KeyPressed == Keys.ARROW_UP) && (dia - 7 > 0)) { dia = dia - 7; desenhar = 1; }
		if ((e.KeyPressed == Keys.ARROW_DOWN) && (dia + 7 < dias + 1)) { dia = dia + 7; desenhar = 1; }
		if (e.KeyPressed == Keys.PGDN) { mes = mes - 1; desenhar = 2; }
		if (e.KeyPressed == Keys.PGUP) { mes = mes + 1; desenhar = 2; }
		
	} while(!exit);
	
	return data1;	
}

// Imprime o mês no calendário e retorna a quantidade de dias do mês.
int getDaysMonth(int mes, int ano, bool show, LOCATION *pos){
	int x1, x, y, dias;
	string Mes = "";
	x1 = pos->X;
	x = pos->X;
	y = pos->Y + 1;
	
	switch(mes){
		case 0:  Mes = "JANEIRO"; dias = 31; x = x + 10; break;
		case 1:  Mes = "FEVEREIRO"; dias = 28; x = x + 9; break;
		case 2:  Mes = "MARCO"; dias = 31; x = x + 11; break;
		case 3:  Mes = "ABRIL"; dias = 30; x = x + 11; break;
		case 4:  Mes = "MAIO"; dias = 31; x = x + 12; break;
		case 5:  Mes = "JUNHO"; dias = 30; x = x + 11; break;
		case 6:  Mes = "JULHO"; dias = 31; x = x + 11; break;
		case 7:  Mes = "AGOSTO"; dias = 31; x = x + 10; break;
		case 8:  Mes = "SETEMBRO"; dias = 30; x = x + 10; break;
		case 9:  Mes = "OUTUBRO"; dias = 31; x = x + 10; break;
		case 10:  Mes = "NOVEMBRO"; dias = 30; x = x + 10; break;
		case 11:  Mes = "DEZEMBRO"; dias = 31; x = x + 10; break;
		default:  Mes = "JANEIRO"; dias = 31; x = x + 10; break;
	}
			
	// verifica se o ano é bissexto
	if (mes==1 && (ano%4==0)) dias = 29; 
	
	// Verifica se deve imprimir o mês na tela.
	if(show){
		// Apaga o texto do mes.
		gotoxy(x1 + 8, y); strings(11, 32);
		// Imprime o mês na tela.
		gotoxy(x, y); printf("%s", Mes); 
	}		
	return dias;
}


/*
int tecla(){
	int op, sair = 0;
	do{// verifica qual tecla foi apertada
		fflush(stdin); // apaga buffer do teclado
		if (kbhit()){ // executa quando uma tecla ? apertada
			op = getch(); // guarda o valor da tecla apertada
			sair = 1; // sai da estrutura
		}
	} while(sair == 0); // executa enquanto saida = 0
	return op; // retorna a tecla pressionada	
}*/

void cor(int fonte, int fundo){
	textbackground(fundo);	// cor do fundo
	textcolor (fonte); // cor da fonte
	
	// 0 = preto		8 = cinza escuro
	// 1 = azul			9 = azul claro
	// 2 = verde		10 = verde claro (A)
	// 3 = verde agua	11 = verde agua claro (B)
	// 4 = vermelho		12 = vermelho claro (C)
	// 5 = roxo			13 = lil?s (D)
	// 6 = amarelo		14 = amarelo claro (E)
	// 7 = cinza claro	15 = branco (F)
}

//----------------------
// Operações com listas.
//----------------------
List_Of_DateTimePicker *new_List_Of_DateTimePicker(){
	List_Of_DateTimePicker *List = (List_Of_DateTimePicker *) malloc(sizeof(List_Of_DateTimePicker));
	List->item = NULL;
	List->next = NULL;
	return List;
}

void Dispose_List_Of_DateTimePicker(List_Of_DateTimePicker *List){
	free(List);
}

// Adiciona um Label numa lista.
void AddDateTimePickerIn(List_Of_DateTimePicker *p, DateTimePicker *textBox){
	List_Of_DateTimePicker *new_item = malloc(sizeof(List_Of_DateTimePicker));	
		
	new_item->item = textBox;
	new_item->next = NULL;
	
	if (p->next == NULL){
		p->next = new_item;
	} else{
		AddDateTimePickerIn(p->next, textBox);
	}	
}

// Posiciona na tela todos os labels da lista.
void Show_DateTimePicker_From(List_Of_DateTimePicker *p){
	List_Of_DateTimePicker *temp = p;
	
	while(temp->next != NULL){	
		setDateTimePickerVisible(temp->next->item);
		temp = temp->next;		
	}
}

// Conta quantos elementos há na lista.
int Count_Item_From_List_Of_DateTimePicker(List_Of_DateTimePicker *p){
	int i = 0;
	
	List_Of_DateTimePicker *temp = p;
		
	while(temp->next != NULL){	
		i++;
		temp = temp->next;		
	}
	return i;
}


//
