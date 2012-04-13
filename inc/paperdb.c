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

unsigned long	paperdbAddFile(paperdb_sys* sys, paperdb_file* f)
{
	unsigned long ret = NULL;
	if(sys != NULL && f != NULL)
	{
		if(sys->files == NULL)
		{
			sys->files = malloc(sizeof(paperdb_file*));
			sys->files[0] = f;
		}
		else
		{
			unsigned long curLen = sizeof(sys->files)/sizeof(paperdb_file*);
			paperdb_file** tmp = malloc(sizeof(sys->files)+sizeof(paperdb_file*));	
			paperdb_file** oldArr = sys->files;
			memcpy(tmp,sys->files, curLen);
			sys->files = tmp;
			free(oldArr);
			ret = curLen;
		}
	}
	return ret;
	
}


unsigned long	paperdbNewFile(paperdb_sys* sys, char* nm)
{
	unsigned long ret = NULL;
	if(nm != NULL && sys != NULL)
	{
		paperdb_file* f = malloc(sizeof(paperdb_file));
		unsigned long fid = 0;
		if(sys->files != NULL)
		{
			fid = sizeof(sys->files);
		}
		
		f->file = fopen(nm, "w");
		char* ver = PAPERDB_VERSION;
		fwrite(ver, sizeof(char), strlen(ver), f->file);
		ret = paperdbAddFile(sys,f);
		
	}
	
	return ret;	
}
