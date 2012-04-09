#include "paperdb.h"

paperdb_sys* 	paperdbOpenSys(char* filename)
{
	FILE* pf = fopen(filename, "w");
	char* tmp = "Blarg and stuff!";
	fwrite(tmp, sizeof(tmp[0]), strlen(tmp), pf);
	fclose(pf); 
}

paperdb_file* paperdbGetFile(unsigned long id, paperdb_sys* sys)
{
	return 0;
}

paperdb_sys* 	paperdbCreateSystem()
{
	paperdb_sys* ret = malloc(sizeof(paperdb_sys));
	ret->tables = NULL;
	ret->files = NULL;
	return ret;
}

