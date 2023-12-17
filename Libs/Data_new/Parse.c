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
//
