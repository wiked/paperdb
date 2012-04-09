#include "inc/paperdb.h"

int main()
{
	paperdb_table* tbl = malloc(sizeof(paperdb_table));	
	paperdb_sys* beep = paperdbOpenSys("blarg.txt"); 
	tbl->name = "yup\n";
	printf(tbl->name);
	free(tbl);
	return 0;
}
