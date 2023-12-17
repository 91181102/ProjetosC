 #include <windows.h>
 
   
typedef struct keyb{
	int PGDN;
	int PGUP;
	int ARROW_LEFT;
	int ARROW_RIGHT;
	int ARROW_UP;
	int ARROW_DOWN;
	int ESC;
	int RETURN;
	int ENTER;
	int SPACE;
	int SIM;
	int NAO;
	int BACK_SPACE;
	int F1;
	int F2;
	int F3;
	int F4;
	int F5;
	int F12;
	int HOME;
	int END;
	int DEL;
	int INS;
	int TAB;
	int SHIFT;
	int CONTROL;	
} KEYB;

KEYB Keys;

typedef struct key{
	int Keys;
	string KeyLabel;
} KEY;

typedef struct keyevent{
	int KeyPressed;		
}KeyEvents;

KeyEvents GLOBAL_KeyEvents;

void new_KeyEvents(){
	
}

///
/// constantes para teclas
///
void loadKeyB(){
	Keys.PGDN = 81;
	Keys.PGUP = 73;
	Keys.ARROW_LEFT = 75;
	Keys.ARROW_RIGHT = 77;
	Keys.ARROW_UP = 72;
	Keys.ARROW_DOWN = 80;
	Keys.ESC = 27;
	Keys.RETURN = 13;
	Keys.ENTER = 13;
	Keys.SPACE = 32;
	Keys.SIM = 49;
	Keys.NAO = 48;
	Keys.BACK_SPACE = 8;
	Keys.F1 = 59;
	Keys.F2 = 60;
	Keys.F3 = 61;
	Keys.F4 = 62;
	Keys.F5 = 63;
	Keys.F12 = 123;
	Keys.HOME = 36;
	Keys.END = 35;
	Keys.DEL = 46;
	Keys.INS = 45;
	Keys.TAB = 9;
	Keys.SHIFT = 16;
	Keys.CONTROL = 17;
}


KEY setKeys(int b){
	KEY a;
	
	if (b == Keys.ARROW_DOWN){
		a.KeyLabel = "DOWN";
		a.Keys = Keys.ARROW_DOWN;
	}
	
	if (b == Keys.F1){
		a.KeyLabel = "F1";
		a.Keys = Keys.F1;
	}
	return a;
}


int getKey(){
	int op, sair = 0;
	do{// verifica qual tecla foi apertada
		fflush(stdin); // apaga buffer do teclado
		if (kbhit()){ // executa quando uma tecla ? apertada
			op = getch(); // guarda o valor da tecla apertada
			sair = 1; // sai da estrutura
		}
	} while(sair == 0); // executa enquanto saida = 0
	return op; // retorna a tecla pressionada
}


