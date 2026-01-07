#include "BookDatabase.h"

#include "../../Utilities/CsvParser.hpp"
#include "../../Utilities/StringUtil.hpp"
#include "../../Utilities/Timer.hpp"
#include "../Project2/Author.h"
#include "../Project2/Book.h"

#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

BookDatabase::BookDatabase()
{
    string filename = "stats.txt";
    m_stats.open(filename);
    cout << "Saving Books\"" << filename << "\"" << endl;
    
}

BookDatabase::~BookDatabase()
{
    m_stats.close();
}

void BookDatabase::LoadBooks( string filename )
{
    cout << "Load books from \"" << filename << "\"..." << endl;
    //throw NotImplementedException( "BookDatabase::LoadBooks" );   

    CsvDocument doc = CsvParser::Parse(filename); 

    Book book; 

    int exceptionCounter = 0;

    for (size_t row = 0; row < doc.rows.size(); row++)
    {
        for (size_t col = 0; col < doc.rows[row].size(); col++)
        {
            if (doc.header[col] == "ISBN10")
            {
                book.isbn10 = StringUtil::StringToUInt(doc.rows[row][col]);
                
            }
            else if (doc.header[col] == "AUTHORID")
            {
                book.authorId = StringUtil::StringToInt(doc.rows[row][col]);
                
            }
            else if (doc.header[col] == "TITLE")
            {
                book.title = doc.rows[row][col]; 
                
            }
        }

        Timer timer; 
        timer.Start(); 
        
        m_booksTree.Push(book.isbn10, book);
        m_stats_BookTreePush.push_back(timer.GetElapsedMilliseconds()); 


        timer.Start(); 
        m_booksList.PushBack(book); 
        m_stats_BookListPush.push_back(timer.GetElapsedMilliseconds()); 

        m_bookKeyList.push_back(book.isbn10); 

        if (m_booksTree.GetCount() % 1000 == 0)
        {
            cout << m_booksTree.GetCount() << "/" << doc.rows.size() << " books loaded..." << endl; 
        }
        m_stats << m_booksTree.GetCount() << " books loaded" << endl; 
        
         

    }

   

}

void BookDatabase::LoadAuthors( string filename )
{
    cout << "Load authors from \"" << filename << "\"... ";
    //throw NotImplementedException( "BookDatabase::LoadAuthors" );

    CsvDocument doc = CsvParser::Parse(filename); 

    Author author; 

    for (size_t row = 0; row < doc.rows.size(); row++)
    {
        for (size_t col = 0; col < doc.rows[row].size(); col++)
        {
            if (doc.header[col] == "ID")
            {
                author.authorId = StringUtil::StringToInt(doc.rows[row][col]); 
                 
            }

            else if (doc.header[col] == "NAME")
            {
                author.name = doc.rows[row][col]; 
                //cout << author.name << endl; 
                
            }
        }

        Timer timer; 
        timer.Start(); 

        m_authorsTree.Push(author.authorId,author);
        m_stats_AuthorTreePush.push_back(timer.GetElapsedMilliseconds()); 


        timer.Start(); 
        m_authorsList.PushBack(author); 
        m_stats_AuthorListPush.push_back(timer.GetElapsedMilliseconds());


        m_stats << m_authorsTree.GetCount() << " authors loaded" << endl; 
        cout << m_authorsTree.GetCount() << " authors loaded" << endl << endl; 
    }
}

Book BookDatabase::GetBookFromTree( unsigned int isbn )
{
    //throw NotImplementedException( "BookDatabase::GetBookFromTree" );

    Timer timer; 
    timer.Start(); 
    Book book; 
     
    book = m_booksTree.GetData(isbn);
   
        
    
    
    m_stats_BookTreeSearch.push_back(timer.GetElapsedMilliseconds()); 
    return book; 


   
}

Book BookDatabase::GetBookFromList( unsigned int isbn )
{
    //throw NotImplementedException( "BookDatabase::GetBookFromList" );

    Book book;
    Timer timer;
    timer.Start();
    for (int i = 0; i < m_booksList.Size(); i++)
    {
        if (m_booksList.GetAt(i).isbn10 == isbn)
        {
            book = m_booksList.GetAt(i);
            break;
        }
    }
    m_stats_BookListSearch.push_back(timer.GetElapsedMilliseconds());
    return book;
}

Author BookDatabase::GetAuthorFromTree(int id )
{
    //throw NotImplementedException( "BookDatabase::GetAuthorFromTree" );
    Timer timer;
    timer.Start();
    Author author;
    author = m_authorsTree.GetData(id);




    m_stats_AuthorTreeSearch.push_back(timer.GetElapsedMilliseconds());
    return author;
    

  


}

Author BookDatabase::GetAuthorFromList( int id )
{
    //throw NotImplementedException( "BookDatabase::GetAuthorFromList" );
    Author author;
    Timer timer;
    timer.Start();
    for (int i = 0; i < m_authorsList.Size(); i++)
    {
        if (m_authorsList.GetAt(i).authorId == id)
        {
            author = m_authorsList.GetAt(i);
            break;
        }
    }
    m_stats_AuthorListSearch.push_back(timer.GetElapsedMilliseconds());
    return author;

}

void BookDatabase::SaveCombined( string filename )
{
    //throw NotImplementedException( "BookDatabase::SaveCombined" );
    CsvDocument doc; 
    doc.header = { "ISBN", "TITLE", "AUTHORID", "AUTHORNAME" }; 

    int counter = 0; 

    for (auto & i: m_bookKeyList)
    {
        if (counter % 1000 == 0)
        {
            cout << counter << "/" << m_bookKeyList.size() << " books matched to authors..." << endl; 
        }

        Book book; 
        Author author; 

        book = GetBookFromTree(i); 
        book = GetBookFromList(i); 

        author = GetAuthorFromTree(book.authorId); 
        author = GetAuthorFromList(book.authorId);


        vector<string> row = { StringUtil::ToString(book.isbn10), book.title, StringUtil::ToString(author.authorId), author.name };

        
        

        
        

        doc.rows.push_back(row);
        counter++; 


    }
    CsvParser::Save(filename, doc);
    SaveStats(); 

}

void BookDatabase::SaveStats()
{
    cout << "Output stats..." << endl;
    
    //Uncomment me out later
   auto CalculateAverage = []( vector<unsigned int> stats) -> float {
        unsigned int sum = 0;
        for ( auto& num : stats ) { sum += num; }
        return sum / stats.size();
    };
    
    float average_BookTreePush     = CalculateAverage( m_stats_BookTreePush );
    float average_BookListPush     = CalculateAverage( m_stats_BookListPush );
    float average_AuthorTreePush   = CalculateAverage( m_stats_AuthorTreePush );
    float average_AuthorListPush   = CalculateAverage( m_stats_AuthorListPush );
    float average_BookTreeSearch   = CalculateAverage( m_stats_BookTreeSearch );
    float average_BookListSearch   = CalculateAverage( m_stats_BookListSearch );
    float average_AuthorTreeSearch = CalculateAverage( m_stats_AuthorTreeSearch );
    float average_AuthorListSearch = CalculateAverage( m_stats_AuthorListSearch );

    m_stats << endl << "SUMMARY" << endl << endl;

    m_stats << fixed << setprecision( 5 );

    const int W = 15;

    m_stats << left
        << setw( W ) << "DATA"
        << setw( W ) << "FUNCTION"
        << setw( W ) << "TREE AVG MS"
        << setw( W ) << "LIST AVG MS"
        << endl << string( 80, '-' ) << endl;

    m_stats
        << setw( W ) << "Book"
        << setw( W ) << "Push"
        << setw( W ) << average_BookTreePush
        << setw( W ) << average_BookListPush << endl;

    m_stats
        << setw( W ) << "Author"
        << setw( W ) << "Push"
        << setw( W ) << average_AuthorTreePush
        << setw( W ) << average_AuthorListPush << endl;

    m_stats
        << setw( W ) << "Book"
        << setw( W ) << "Search"
        << setw( W ) << average_BookTreeSearch
        << setw( W ) << average_BookListSearch << endl;

    m_stats
        << setw( W ) << "Author"
        << setw( W ) << "Search"
        << setw( W ) << average_AuthorTreeSearch
        << setw( W ) << average_AuthorListSearch << endl;




  
}


