#ifndef _PAPERDB_H_06APR2012
#define _PAPERDB_H_06APR2012
#include <stdio.h>

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


// paperdb_file
typedef struct
{
	char* fileName;
	unsigned long id;
	unsigned long schemaOffset;
	unsigned long dataOffset;	
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
	unsigned long start_file_id;
	unsigned long start_file_loc;
	paperdb_column** cols;
} paperdb_table;

// paperd_sys
typedef struct
{
	char* name;
	paperdb_table** tables;
	paperdb_file** files;;
} paperdb_sys;


paperdb_file*	paperdbGetFile(unsigned long id, paperdb_sys* sys);
paperdb_sys* 	paperdbCreateSystem();
paperdb_sys* 	paperdbOpenSys(char* filename);


#endif
