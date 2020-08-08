#include <STDIO.H>
#include <MALLOC.H>
//#include <STRINGS.H>
#include <LIBDS.H>

#ifndef CD_SERVICE_H
#define CD_SERVICE_H

struct CDService {
	static void open();
	static void close();
	static void read(unsigned char* file_path, u_long** file);
	static int didInitDs;
};

#endif // CD_SERVICE_H