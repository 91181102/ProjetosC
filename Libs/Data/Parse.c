// Classe Parse

char *Int_ToString(int value);
bool Int_ToBoolean(int value);
string *Boolean_ToString(bool value);
	
typedef struct PARSE{
	char (*Int_ToString)(int value);
	bool (*Int_ToBoolean)(int value);
	string (*Boolean_ToString)(bool value);
}_parse;

_parse *Parse;


void setParse(){
	_parse *object = malloc(sizeof(_parse));
	object->Int_ToString = Int_ToString;
	object->Int_ToBoolean = Int_ToBoolean;
	object->Boolean_ToString = Boolean_ToString;
	
	Parse = object;
}

char *Int_ToString(int value){
	char *a = malloc(sizeof(int));
   	sprintf(a, "%d%", value);
   	return a;
}


bool Int_ToBoolean(int value){
	if (value == 0)
		return false;
	else
		return true;
}

string *Boolean_ToString(bool value){
	if (value == 0)
		return "false";
	else
		return "true";
}

char *ToDateShort(char *value){
	//sprintf(txt_data->Date->Short, "0%d/%s/%d", dia, mes1[mes], ano);
	char data[10];	
	sprintf(data, "%s/%s/%s ", subString(value, 6, 2), subString(value, 4, 2), subString(value, 0, 4));
	//data[10] = '\0';
	return data;	
}

void toDateShort(char *dest, char value[]){
	
}

//
