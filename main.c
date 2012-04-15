#include "inc/paperdb.h"

int main()
{
	paperdb_sys* sys = paperdbCreateSystem();
	sys->name = "Homer";
	unsigned long fid = paperdbNewFile(sys, "temp.paper");
	
	printf("sysname: %s\n", sys->name);
	//fclose(sys->files[0]->file);
	unsigned long pos = ftell(sys->files[0]->file);	
	printf("FilePos after file creation: %lu\n", pos);
	printf("sysname after filecreate: %s\n", sys->name);
	paperdb_table* tbl = paperdbCreateTable(sys, "user");
	printf("table created: '%s'\n", tbl->name);
	paperdbAddColumn(tbl, "id", PAPERDB_CT_INT, 1); 
	printf("column created on tbl '%s': '%s'", tbl->name, tbl->cols[0]->name);
	fflush(stdout);
	paperdbAddColumn(tbl, "tp", PAPERDB_CT_STRING, 10); 
	printf("column created on tbl '%s': '%s'", tbl->name, tbl->cols[1]->name);
	fflush(stdout);
	paperdbWriteColumns(tbl->cols, 2, sys->files[0]->file);
	fclose(sys->files[0]->file);
	FILE* fin = fopen("temp.paper", "r");
	fseek(fin, pos, SEEK_SET);
	unsigned long numCols;
	fread(&numCols, sizeof(numCols), 1, fin);
	printf("Number of cols: %lu\n", numCols);
	int i = 0;
	for(;i<numCols; ++i)
	{
		unsigned long sz;
		fread(&sz, sizeof(sz), 1, fin);
		printf("name size: %lu\n", sz);
		fflush(stdout);
		char* nm = malloc(sz);
		fread(nm, sz, 1, fin);
		unsigned long tp;
		fread(&tp, sizeof(tp), 1, fin);
		unsigned long colSz;
		fread(&colSz, sizeof(colSz), 1, fin);

		printf("Found column:\n\tname:\t'%s'\n\ttp:\t%lu\n\tsz:\t%lu\n", nm, tp, colSz);
		fflush(stdout);
	}
	

	return 0;
}
