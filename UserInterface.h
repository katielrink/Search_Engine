/// \class User Interface
/// \brief Create a search engine user interface
///
/// Read in user prompts and interpret into runnable search engine queries

#ifndef SEARCH_ENGINE_USERINTERFACE_H
#define SEARCH_ENGINE_USERINTERFACE_H

#include <string>
#include "QueryEngine.h"
using namespace std;

class UserInterface {
private:
    QueryEngine QE; ///@private Query engine to manage queries made by user
    string documentPath; ///@private string containing path to index from
    ///remove all previously stored information
    ///call query engine to clear index
    void clearIndex();
    ///@private create a persistent index of data indexed already
    ///call query engine to create persistent index
    void createPersistentIndex();
    ///@private load a persistent index
    ///call query engine to load persistent index
    void loadPersistentIndex();
    //create a new index from a path
    ///@private call query engine to parse data at path and save document path
    ///\param path string with absolute path to directory to be parsed
    void parseData(string);
    ///@private print results of a user query
    ///call query engine to get vector of documents of results of query
    ///print out first 15 results returned with displayData() then ask to preview document
    ///\param query string of user query
    void query(string);
    ///@private display the title of a document and the authors
    ///use rapidjson to read in data from document id and read title and all authors
    ///\param string of id of document
    void displayData(string);
    ///@private display the first 300 words of a document
    ///use rapidjson to read in first in body text until 300 words is reached and print to screen
    ///\param id string of id of document to preview
    void displayPreview(string);
    ///print total number of documents from query engine
    void printTotalDocuments();
    ///print average number of words from query engine
    void printAverageNumberofWords();
    ///print number of unqiue words from query engine
    void printUniqueWords();
    ///print number of authors from query engine
    void printNumberofAuthors();
    ///print out numbers to enter to query the search engine for various feautures
    void printOptions();
public:
    ///interface for the user to interact with
    ///loop through allowing user to input options until -1 entered
    ///for each entry query prompt for further information and call corresponding function
    UserInterface();
};


#endif //SEARCH_ENGINE_USERINTERFACE_H
