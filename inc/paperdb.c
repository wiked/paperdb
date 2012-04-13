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
		ret = 9;
		if(sys->files == NULL)
		{
			sys->files = malloc(sizeof(paperdb_file*));
			sys->files[0] = f;
			ret = 0;
		}
		else
		{
			unsigned long curLen = sizeof(sys->files);
			paperdb_file** tmp = malloc(sizeof(sys->files)+sizeof(paperdb_file*));	
			paperdb_file** oldArr = sys->files;
			memcpy(tmp,sys->files, curLen);
			curLen /= sizeof(paperdb_file*);		
			tmp[curLen]=f;	
			sys->files = tmp;
			//free(oldArr);
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
			fid = sizeof(sys->files)/sizeof(paperdb_file*);
		}
		
		f->file = fopen(nm, "w");
		f->id = fid;
		char* ver = PAPERDB_VERSION;
		fwrite(ver, sizeof(char), strlen(ver), f->file);
		printf("made a new file: %lu; Adding it to sys\n", fid);		
		ret = paperdbAddFile(sys,f);
		
	}
	
	return ret;	
}
