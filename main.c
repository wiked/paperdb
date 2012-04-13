#include "inc/paperdb.h"

int main()
{
	paperdb_sys* sys = paperdbCreateSystem();
	unsigned long fid = paperdbNewFile(sys, "temp.paper");
	fclose(sys->files[0]->file);
	fid = paperdbNewFile(sys, "temp2.paper");
	printf("Got our new fid: %lu\n", fid);
	fclose(sys->files[1]->file);
	printf("fid: %lu\n", fid);
	return 0;
}
