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
			free(sys->files);	
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
		f->filename = nm;	
		f->file = fopen(nm, "w");
		f->id = fid;
		char* ver = PAPERDB_VERSION;
		unsigned long verSize = (strlen(ver)+1)*(sizeof(char));
		fwrite(&verSize, sizeof(unsigned long), 1, f->file);
		fwrite(ver, sizeof(char), strlen(ver), f->file);
		
		ret = paperdbAddFile(sys,f);
		
	}
	
	return ret;	
}

paperdb_table*	paperdbCreateTable(paperdb_sys* sys, char* nm)
{
	
	paperdb_table* ret = NULL;

	void* tst[]  = {&sys, &sys->files, nm};
	char* sufs[] = {"Paperdb system not initialized", "No Files in paperdb_sys object", "Table name is NULL"};
	
	
	char tester = paperdbErrorNullCheckArr(tst, 3, "paperdbCreateTable failed. ",sufs, stderr);
	if(!tester)
	{

		ret = malloc(sizeof(paperdb_table));

		ret->name = nm;
		ret->schema_file_id = 0;
		ret->schema_file_loc = 0;
		ret->data_file_id = 0;
		ret->data_file_loc = 0;
		ret->cols = NULL;
	}

	return ret;
}

void		paperdbAddColumn(paperdb_table* tbl, char* nm, PAPERDB_COL_TYPE tp, unsigned long sz)
{
	void* tst[] = {tbl, nm};
	char* sufs[] = {"Table passed in as NULL","Column Name is NULL"};
	char* pref = "paperdbAddColumn failed. ";
	paperdb_column* col = NULL;
	if(!paperdbErrorNullCheckArr(tst,2, pref, sufs, stderr))
	{
		col = malloc(sizeof(paperdb_column));
		col->name = nm;
		col->tp = tp;
		col->size = sz;	
		if(tbl->cols == NULL)
		{
			tbl->cols = malloc(sizeof(paperdb_column*));
			tbl->cols[0] = col;
			tbl->numCols = 1;
		}
		else
		{
			unsigned long idx = sizeof(tbl->cols)/ sizeof(paperdb_column*);
			unsigned long curLen = sizeof(tbl->cols);
			paperdb_column** newCols = malloc(sizeof(paperdb_column*)*(idx+1));
			memcpy(newCols, tbl->cols, curLen);
			newCols[idx] = col;
			free(tbl->cols);
			tbl->cols = newCols;
			tbl->numCols += 1;
		}
	}
	return;
}

char		paperdbErrorNullCheck(void* tst, char* errString, FILE* fout)
{
	char ret = (tst == NULL);
	if(ret)
	{
		fprintf(fout, errString);
	}
	fflush(fout);
	return ret;
}


char		paperdbErrorNullCheckArr(void** tst, unsigned long nArgs, char* errStartString, char** errSufs, FILE* fout)
{
	char ret = 0;
	int i =0;
	unsigned long startLen = strlen(errStartString)+1;	
	for( ;i < nArgs; ++i)
	{
		
		char* tmpSuf = errSufs[i];
		unsigned long sufLen = strlen(tmpSuf)+1;
		char* tmpStr = malloc(sizeof(char)*(startLen+sufLen+1));
		strcpy(tmpStr, errStartString);
		strcat(tmpStr, tmpSuf);
		strcat(tmpStr, "\n");

		ret = ret || paperdbErrorNullCheck(tst[i],tmpStr, fout);
		free(tmpStr);
	}
	return ret;
}


char	paperdbWriteColumns(paperdb_column** cols, unsigned long numCols, FILE* fout)
{
	// first, write how many columns we've got
	fwrite(&numCols, sizeof(numCols), 1, fout);
	int i = 0;
	for(;i< numCols;++i)
	{
		char* nm = cols[i]->name;
		unsigned long nmSz = sizeof(nm);
		fwrite(&nmSz, sizeof(nmSz), 1, fout);
		fwrite(nm, nmSz, 1, fout);		
		unsigned long tp = cols[i]->tp;	
		unsigned long sz = cols[i]->size;
		fwrite(&tp, sizeof(unsigned long), 1, fout);
		fwrite(&sz, sizeof(unsigned long), 1, fout); 
	} 
}

void	paperdbWriteULong(unsigned long* val, FILE* fout)
{	
	fwrite(val, sizeof(unsigned long), 1, fout);
}

void	paperdbWriteString(char* nm, FILE* fout)
{
	unsigned long nmSz = sizeof(nm);
	fwrite(&nmSz, sizeof(nmSz), 1, fout);
	fwrite(nm, nmSz, 1, fout);
}

unsigned long paperdbReadULong(FILE* fin)
{
	unsigned long lng;
	fread(&lng, 1, sizeof(unsigned long), fin);
	return lng;
}

char* paperdbReadString(FILE* fin)
{
	unsigned long nmSz = paperdbReadULong(fin);
	char* tmp = malloc(nmSz);
	fread(tmp, 1, nmSz, fin);
	return tmp;
}

paperdb_column** paperdbReadCols(FILE* fin, paperdb_table* tbl)
{
	paperdb_column** ret = NULL;
	if(!(paperdbErrorNullCheck(fin, "paperdbReadCols failed.  fin was NULL\n", stdout) || paperdbErrorNullCheck(tbl, "paperdbReadCols failed. tbl was NULL\n", stdout)))
	{
		unsigned long numCols = paperdbReadULong(fin);
		ret = malloc(sizeof(paperdb_column*)*numCols);
		tbl->numCols = numCols;
		int i = 0;
		for(;i<numCols; ++i)
		{
			char* nm = paperdbReadString(fin);
			unsigned long tp = paperdbReadULong(fin);
			unsigned long sz = paperdbReadULong(fin);
			ret[i] = malloc(sizeof(paperdb_column));
			ret[i]->name = nm;
			ret[i]->tp = tp;
			ret[i]->size = sz;
		}
	}
	return ret;
}

paperdb_table* paperdbReadTable(FILE* fin)
{
	paperdb_table* ret = NULL;
	if(!paperdbErrorNullCheck(fin, "paperdbReadTable failed. fin was NULL.",stdout))
	{
		unsigned long id = paperdbReadULong(fin);
		char* nm = paperdbReadString(fin);
		unsigned long dfi = paperdbReadULong(fin);
		unsigned long dfl = paperdbReadULong(fin);
		ret = malloc(sizeof(paperdb_table));
		ret->id = id;
		ret->name = nm;
		ret->data_file_id = dfi;
		ret->data_file_loc = dfl;
		paperdb_column** cols = paperdbReadCols(fin, ret);		
	}
	return ret;
}

char	paperdbSaveTable(paperdb_sys* sys, paperdb_table* tbl, paperdb_file* f)
{
	FILE* fout = f->file;
	char ret = 0;
	// I'm of two minds whether or not to put some checking here to see if fout has been set up correctly.
	// I'm going to skip it for now.. because I think there's good arguments to be made that fout should be set up before paperdbSaveTable is called.
	void* tst[] = {sys, sys->files, fout, tbl};
	char* errs[] = {"System not Initialized", "System files not initialized", "Table file stream is NULL", "Table is NULL"};
	char* pre ="paperdbSaveTable failed. "; 
	if(!paperdbErrorNullCheckArr(tst, 4, pre, errs, stdout))
	{
		unsigned long curPos = ftell(fout);
		paperdbWriteULong(&tbl->id, fout);
		paperdbWriteString(tbl->name, fout);
		paperdbWriteULong(&tbl->data_file_id, fout);
		paperdbWriteULong(&tbl->data_file_loc, fout);
		paperdbWriteColumns(tbl->cols, tbl->numCols, fout);
		unsigned long newPos = ftell(fout);
		unsigned long endPos = newPos + 100;
		paperdbWriteULong(&endPos, fout);
		f->nextTablePos = (endPos+1);
	}
	return ret;
}


