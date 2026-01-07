# Library Project

A compact, console-based library management system written in C++ (C++17). Provides basic domain models for books and authors, an in-memory database with simple file-based persistence, and a command-line interface for managing a collection of books.

## Features
- Add, remove, search, and list books and authors
- Simple file-based persistence (see data/)
- Clean, object‑oriented design (Book, Author, BookDatabase, LibraryProgram)
- Easy to extend (persistence backend, tests, GUI/web front end)

## Repository structure
- Author.h — Author model
- Book.h — Book model
- BookDatabase.h / BookDatabase.cpp — core data management and persistence logic
- LibraryProgram.h / LibraryProgram.cpp — CLI and program flow
- data/ — sample or persisted data files

