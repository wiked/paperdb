#include <stdio.h>
#include "inc/paperdb.h"

int main()
{
	paperdb_table* tbl = malloc(sizeof(paperdb_table));
	tbl->name = "Dude!\n";
	printf(tbl->name);
	free(tbl);
	return 0;
}
