#include <stdio.h>
#include "inc/paperdb.h"

int main()
{
	paperdb_table* tbl = malloc(sizeof(paperdb_table));	
	paperdb_file* beep = paperdbGetFile(0); 
	tbl->name = "Quack\n";
	printf(tbl->name);
	free(tbl);
	return 0;
}
