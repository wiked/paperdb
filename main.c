#include "inc/paperdb.h"

int main()
{
	paperdb_sys* sys = paperdbCreateSystem();
	unsigned long fid = paperdbNewFile(sys, "temp.paper");
	if(fid != NULL)
	{
		sprintf("fid: %d", fid);
		fclose(sys->files[0]);

	}
	return 0;
}
