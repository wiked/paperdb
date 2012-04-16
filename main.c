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
	

	paperdb_file* f = sys->files[0];
	printf("Setting up offsets\n");
	fflush(stdout);


	sys->files[0]->nextTablePos = pos+50;
	sys->files[0]->schemaOffset = pos+50;
	pos = ftell(f->file);

	printf("Padding file\n");
	fflush(stdout);

	unsigned long blankSz = (2000);
	char* tmp = malloc(blankSz);
	unsigned long charSz = sizeof(char);
	unsigned long charNum = blankSz/charSz;
	printf("CharSz: %lu\n CharNum: %lu\n", charSz, charNum);
	fflush(stdout);
	memset(tmp, ' ', blankSz);

	printf("writeout\n");
	fflush(stdout);

	fwrite(tmp, blankSz,1, f->file);
	printf("And we're walking!\n");
	fflush(stdout);

	free(tmp);
	printf("Done freeing\n");
	fflush(stdout);

	fseek(f->file,f->schemaOffset,SEEK_SET);
	printf("done seeking\n");
	fflush(stdout);

	paperdbSaveTable(sys, tbl, sys->files[0]);		
	printf("Done saving table\n");
	fflush(stdout);

	fclose(f->file);

	return 0;
}
