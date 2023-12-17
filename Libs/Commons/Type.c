// Class Type



typedef struct TYPE{
	int CheckBox;
	int ComboBox;	
	int DateTimePicker;
	int Form;	
	int TextBox;
	int Button;
	int Int;
	int Double;
	int Float;
	int Bool;
	int Char;
	int Table;
}Type;

Type TypeOf;

void setType(){
	TypeOf.CheckBox = 0;
	TypeOf.ComboBox = 1;	
	TypeOf.DateTimePicker = 2;
	TypeOf.Form = 3;
	TypeOf.TextBox = 4;
	TypeOf.Button = 5;
	TypeOf.Int = 6;
	TypeOf.Double = 7;
	TypeOf.Float = 8;
	TypeOf.Bool = 9;
	TypeOf.Char = 10;
	TypeOf.Table = 11;
}


//----------------------------
