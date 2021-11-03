/*!
 * \class Index Handler
 * \include document.h
 * \include HashMap.h
 * \include AVLTree.h
 * holds a hashmap of authors of documents and a AVLTree of words of documents
 * parse files to store and interpret and retrieve information regarding index later
 * uses rapidjson to read in json files information
 * uses porter2_stemmer to stem words stored
 */

#ifndef SEARCH_ENGINE_INDEXHANDLER_H
#define SEARCH_ENGINE_INDEXHANDLER_H

#include <iostream>
#include <vector>
#include "document.h"
#include "HashMap.h"
#include "AVLTree.h"

using namespace std;

class IndexHandler {
    private:
        //author -> document
        HashMap<string, document> authorsToDocuments; ///\var \private hashmap to store author's last name as key and document as corresponding value
        //word -> documents
        AVLTree<string, vector<document>> wordsToDocuments; ///\var \private AVLTree to store a given word with a vector of documents it appears in
        //stats
        int totalDocs; ///\var \private total number of documents indexed
        int totalWordsOverall; ///\var \private total number of words indexed
    public:
        ///\fn constructor
        IndexHandler();
        /*!
         * \fn upload data from json files in a directory
         * loops through all files in directory that are .json and parses them using rapidjson
         * store id of file then count the total number of words in the file
         * read in all authors and store in hashmap
         * read in all words from title abstract and body and store in AVLTree
         * \param path path to directory of files
         */
        void uploadData(string);
        /*!
         * \fn create a persistent index for a file
         * store data from AVLTree and Hashmap by calling their methods to storeData
         */
        void createPersistentIndex();
        /*!
         * \fn upload data from a persistent index
         * read in line by line index and store document word, id, total words, and occurances in AVLTree
         */
        void upLoadFromPersistentIndex();
        /*!
         * \fn check if a string exists within documents
         * call contains method on AVLTree
         * \param key word to check if exists
         * \return boolean whether word exists or not
         */
        bool containsWord(string);
        ///check if a author exists within documents
        ///call hashtable contains function
        ///\param key string of author to check if exists
        ///\return if author exists within hashtable
        bool containsAuthor(string);
        ///get all documents containing a word
        ///call get function on AVLTree
        ///\param key word to search AVLTree for
        ///\return vector of documents containing word
        vector<document>& getWord(string);
        ///get all documents by an author
        ///call get function on hashtable
        ///\param key word to search hashmap for
        ///\return vector of documents by author
        vector<document> getAuthor(string);
        ///clear all information stores
        ///empty functions in hashmap and AVLTree
        void clearIndex();
        ///get the total number of documents indexed
        ///\return totaldocs
        int getTotalDocs();
        ///get the average number of words per document
        ///\return total word count divided by number of documents
        int avgNumWords();
        ///get number of words indexed
        ///call AVLTree getSize() function
        ///\return number of nodes in AVLTree
        float getUniqueWords();
        ///get the total number of authors indexed
        ///call hashmap getNumElemnets function()
        ///\return number of elements in hashmap
        int getNumAuthors();
};


#endif //SEARCH_ENGINE_INDEXHANDLER_H
