#ifndef _BOOKDATABASE
#define _BOOKDATABASE

#include "Book.h"
#include "Author.h"
#include "../../DataStructure/BinarySearchTree/BinarySearchTree.hpp"
#include "../../DataStructure/LinkedList/LinkedList.hpp"

class BookDatabase
{
public:
    BookDatabase();
    ~BookDatabase();

    void LoadBooks( string filename );
    void LoadAuthors( string filename );
    void SaveCombined( string filename );

    Book GetBookFromTree( unsigned int isbn );
    Book GetBookFromList( unsigned int isbn );

    Author GetAuthorFromTree( int id );
    Author GetAuthorFromList( int id );

    void SaveStats();

private:
    // TODO: Add BinarySearchTree of Authors
    BinarySearchTree<int, Author> m_authorsTree;

    // TODO: Add BinarySearchTree of Books
    BinarySearchTree<unsigned int, Book> m_booksTree;
    vector<unsigned int> m_bookKeyList;

    LinkedList<Author> m_authorsList;
    LinkedList<Book> m_booksList;

    vector<unsigned int> m_stats_BookTreePush;
    vector<unsigned int> m_stats_BookListPush;
    vector<unsigned int> m_stats_AuthorTreePush;
    vector<unsigned int> m_stats_AuthorListPush;
    vector<unsigned int> m_stats_BookTreeSearch;
    vector<unsigned int> m_stats_BookListSearch;
    vector<unsigned int> m_stats_AuthorTreeSearch;
    vector<unsigned int> m_stats_AuthorListSearch;

    ofstream m_stats;
};

#endif
