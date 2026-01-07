#include "LibraryProgram.h"

void LibraryProgram::Run()
{
    cout << "Library program begins..." << endl;

    // TODO: Update paths as needed
    // NOTE THAT THE DEFAULT WORKING PATH IS WHERE YOUR PROJECT FILE IS.
    // These paths are based on my codeblocks project being in Project_CodeBlocks.

    m_bookDatabase.LoadBooks( "../Projects/Project2/data/books.csv" );
    m_bookDatabase.LoadAuthors( "../Projects/Project2/data/authors.csv" );
    

    
    // If this doesn't have folders, then it will be saved to the project path.
    m_bookDatabase.SaveCombined( "../Projects/Project2/data/combined.csv" );

    cout << "Library program ends..." << endl;
}
