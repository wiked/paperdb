#ifndef _PAPERDB_H_06APR2012
#define _PAPERDB_H_06APR2012
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// column types.
// that's what the CT stands for.
// -wik
#define PAPERDB_CT_INT		0
#define PAPERDB_CT_STRING 	1
#define PAPERDB_CT_TEXT		2
#define PAPERDB_CT_BLOB 	3

// modifiers
#define PAPERDB_MOD_UNSIGNED	1
#define PAPERDB_MOD_NOTNULL	2
#define PAPERDB_MOD_UNIQUE	4

#define PAPERDB_VERSION 	"PAPERDB VERSION 0.01"
#define PAPERDB_COL_TYPE	unsigned long

// paperdb_file
typedef struct
{
	char* filename;
	unsigned long id;
	unsigned long schemaOffset;
	unsigned long dataOffset;
	unsigned long fileInfoOffset;
	unsigned long nextTablePos;
	unsigned long nextDataPos;
	unsigned long nextFilePos;	
	FILE* file;
} paperdb_file;

// paperdb_column
typedef struct
{
	char* name;
	unsigned long tp;
	unsigned long size;
} paperdb_column;

// paperdb_row
typedef struct
{
	unsigned long start_file_id;
	unsigned long start_file_loc;
	unsigned long next; 
	void** vals;
} paperdb_row;

// paperdb_table
typedef struct
{
	char* name;
	unsigned long id;
	unsigned long schema_file_id;
	unsigned long schema_file_loc;
	unsigned long data_file_id;
	unsigned long data_file_loc;
	paperdb_column** cols;
	unsigned long numCols;
} paperdb_table;

// paperd_sys
typedef struct
{
	char* name;
	paperdb_table** tables;
	paperdb_file** files;;
} paperdb_sys;



paperdb_file*		paperdbGetFile(unsigned long id, paperdb_sys* sys);
paperdb_sys* 		paperdbCreateSystem();
paperdb_sys* 		paperdbOpenSys(char* filename);
unsigned long		paperdbNewFile(paperdb_sys* sys, char* nm);
unsigned long		paperdbAddFile(paperdb_sys* sys, paperdb_file* f);
paperdb_table*		paperdbCreateTable(paperdb_sys* sys, char* nm);
void			paperdbAddColumn(paperdb_table* tbl, char* nm, PAPERDB_COL_TYPE tp, unsigned long sz);
char			paperdbErrorNullCheckArr(void** tst,unsigned long nArgs, char* errStartString, char** errSufs, FILE* fout);
char			paperdbSaveTable(paperdb_sys* sys, paperdb_table* tbl, paperdb_file* f);
char			paperdbWriteColumns(paperdb_column** cols, unsigned long numCols, FILE* fout);
paperdb_table* 		paperdbReadTable(FILE* fin);
paperdb_column**	paperdbReadCols(FILE* fin, paperdb_table* tbl);
#endif
