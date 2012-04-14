#include "inc/paperdb.h"

int main()
{
	paperdb_sys* sys = paperdbCreateSystem();
	sys->name = "Homer";
	unsigned long fid = paperdbNewFile(sys, "temp.paper");
	
	printf("sysname: %s\n", sys->name);
	fclose(sys->files[0]->file);
	
	printf("sysname after filecreate: %s\n", sys->name);
	paperdb_table* tbl = paperdbCreateTable(sys, "user");
	printf("table created: '%s'\n", tbl->name);
	paperdbAddColumn(tbl, "id", PAPERDB_CT_INT, 1); 
	printf("column created on tbl '%s': '%s'", tbl->name, tbl->cols[0]->name);
	paperdbAddColumn(tbl, "tp", PAPERDB_CT_STRING, 10); 
	printf("column created on tbl '%s': '%s'", tbl->name, tbl->cols[1]->name);

	return 0;
}
