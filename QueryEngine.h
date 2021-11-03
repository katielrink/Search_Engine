/*!
 * \class Query Engine
 * \brief run user queries
 */

#ifndef SEARCH_ENGINE_QUERYENGINE_H
#define SEARCH_ENGINE_QUERYENGINE_H

#include "IndexHandler.h"
#include "document.h"

class QueryEngine {
private:
    vector<document> results; ///@private vector of documents containing all documents matchin query
    bool tested; ///@private boolean to confirm if query have been run
    IndexHandler IH; ///@private index handler to manage all document information
public:
    ///constructor
    QueryEngine();
    ///runs a query to find documents matching query
    ///check query for AND or OR then run corresponding function and create vector with all following words
    ///check query for NOT run not function with next word
    ///check query for AUTHOR run author function with next word
    ///sort vector of documents based on custom sort of frequency of word occurance
    /// \param query string of query entered into engine
    /// \return vector of sorted documents containing key word by relevenace
    vector<document> runQuery(string);
    ///add all documents that contain all words to results vector
    ///for each word to be searched called index handler to get vector of documents containing
    /// add all documents containing first word to vector then remove documents not containing all following words
    ///\param words string of all words to be searched for
    void ANDfucntion(vector<string>);
    ///add all documents containing any of the key words to vector
    ///for each word to be searched called index handler to get vector of documents containing
    ///if results does not contain document add to results
    ///\param words string of all words to be searched for
    void ORfunction(vector<string>);
    ///remove all documents containing key word
    ///call index handler to get all documents containg keyword
    ///for each document in results, remove if it contains keyword
    ///\param word string of word to not be included
    void NOTfunction(string);
    ///get only documents by this author
    ///call index handler to get all documents by this author
    ///check each results author to see if it contains and if not remove
    void authorFunction(string);
    ///remove all stored information
    ///call index handler to clear index
    void clearIndex();
    ///create a new index from a path
    ///call index handler to parse data at path
    ///\param path string with absolute path to directory to be parsed
    void parseIndex(string);
    /// get total number of documents indexed
    /// call index handler to get total number of documents
    /// \return total number of documents indexed
    int getTotalDocs();
    /// get average number of words per document indexed
    /// call index handler to get average number of words per document
    /// \return average number of words per document indexed
    int avgNumWords();
    /// get number of words indexed
    /// call index handler to get number of unique words indexed
    ///\return number of words indexed
    float getUniqueWords();
    /// get number of authors indexed
    /// call index handler to get number of authors indexed
    ///\return number of authors indexed
    int getNumAuthors();
    ///create a persistent index of data indexed already
    ///call index handler to create persistent index
    void createPersistentIndex();
    ///load a persistent index
    ///call index handler to load persistent index
    void loadPersistentIndex();
};


#endif //SEARCH_ENGINE_QUERYENGINE_H
