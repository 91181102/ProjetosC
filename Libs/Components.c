// Classe components


enum boolean {
    true = 1, false = 0
};

typedef enum boolean bool;




#define DUMP(varname) fprintf(stderr, "%s", #varname, varname);
#define GET_VARIABLE_NAME(Variable) (#Variable)
#define SET(Variable) (#Variable)



#include "conio2.h"
#include "conio.c"
#include <windows.h>
#include "./Commons/Align.c"
#include "./Commons/Border.c"
#include "./Commons/Size.c"
#include "./Commons/Padding.c"
#include "String.c"
#include "./Commons/Type.c"
#include "./Commons/Location.c"
#include "./Commons/Colors.c"
#include "./Forms/Label.c"
#include "./Forms/KeyB.c"
#include "./Forms/Items.c"
#include "./Forms/ComboBox.c"
#include "./Forms/TextBox.c"
#include "./Forms/DateTimePicker.c"
#include "./Forms/CheckBox.c"
#include "./Forms/TabControl.c"
#include "./Forms/Button.c"
#include "./Forms/MenuOption.c"
#include "./Forms/MenuItem.c"
#include "./Forms/MenuBar.c"
#include "./Data/HeaderColumn.c"
#include "./Data/DataColumn.c"
#include "./Data/DataRow.c"
#include "./Data/DataTable.c"
#include "./Data/Columns.c"
#include "./Data/Rows.c"
#include "./Data/Table.c"
#include "./Data/Join.c"
#include "./Data/Connection.c"
#include "./Data/Parse.c"
#include "./Data/Extras.c"
#include "./Forms/Form.c"
#include "./Collections/Form_TextBox.c"
#include "./Collections/Form_DateTimePicker.c"
#include "./Collections/Form_CheckBox.c"
#include "./Collections/Form_ComboBox.c"
#include "./Collections/Form_Label.c"
#include "./Collections/Form_Button.c"
#include "./Collections/Form_Table.c"
#include "./Collections/Form_Menu.c"
#include "./Forms/MsgBox.c"

 


void InitializeComponents(){
	setColors();
	setBorderValues();
	setAlignValues();
	ModeSetMode();
	loadKeyB();
	setType();
	setParse();
	Position = setLocation(1,1);
	InitPosition = setLocation(1,1);
	
	Form_Focus = new_Form();	
}
	
