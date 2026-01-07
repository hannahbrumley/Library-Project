#ifndef _LIBRARY_PROGRAM
#define _LIBRARY_PROGRAM

#include "BookDatabase.h"

class LibraryProgram
{
public:
    void Run();

private:
    BookDatabase m_bookDatabase;
};

#endif
