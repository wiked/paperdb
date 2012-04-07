#ifndef _PAPERDB_H_06APR2012
#define _PAPERDB_H_06APR2012

// column types.
// that's what the CT stands for.
// -wik
#define PAPERDB_CT_INT		0
#define PAPERDB_CT_STRING 	1
#define PAPERDB_CT_BLOB 	2

// modifiers
#define PAPERDB_MOD_UNSIGNED	1
#define PAPERDB_MOD_NOTNULL	2
#define PAPERDB_MOD_UNIQUE	4


typedef struct
{
	char* fileName;
	unsigned int id;	
} paperdb_file;


typedef struct
{
	char* name;
	unsigned int tp;
	unsigned int size;
} paperdb_column;

typedef struct
{
	char* name;
	unsigned int id;
	unsigned int start_filed_id;
	unsigned int start_file_loc;
} paperdb_table;

#endif
