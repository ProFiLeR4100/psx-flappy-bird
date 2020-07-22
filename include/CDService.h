#include <STDIO.H>
#include <MALLOC.H>
#include <STRINGS.H>
#include <LIBDS.H>

#ifndef CD_SERVICE_CLASS
#define CD_SERVICE_CLASS

class CDService {
public:
    static void open();
    static void close();
    static void read(unsigned char* file_path, unsigned long** file);
    static int didInitDs;
};

#endif // CD_SERVICE_CLASS