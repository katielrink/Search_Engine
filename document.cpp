/*!
 * \class document
 * store the id of the file, the number of words, the number of words, the number of times the word appeared
 */

#include "document.h"

/*!
 * \fn constructor
 * \param i id of file
 * \param words total words in a file
 */
document::document(string i, int words){
    id = i;
    occurances = 0;
    totalWords = words;
}

/*!
 * \fn copy constructor
 * \param d document to copy all data from
 */
document::document(const document& d){
    id = d.id;
    occurances = d.occurances;
    totalWords = d.totalWords;
}
/*!
 * \fn destructor
 */
document::~document(){
    id = "";
    occurances = 0;
    totalWords = 0;
}
/*!
 * \fn override assignment operator
 * \param d document to copy all information from
 */
void document::operator= (const document& d){
    id = d.id;
    occurances = d.occurances;
    totalWords = d.totalWords;
}
/*!
 * \fn override equal operator
 * compare ids of documents to determine equality
 * \param d document to compare to
 * \return whether documents are equal
 */
bool document::operator== (const document& d){
    if(id == d.id)
        return true;
    return false;
}
/*!
 * \fn getter for ID
 * \return ID fo document
 */
string document::getID(){
    return id;
}
/*!
 * \fn get frequency word appears in document
 * divide the occurances by the total number of words
 * \return frequency of word
 */
double document::getFrequency(){
    return occurances/totalWords;
}
/*!
 * \fn getter for occurances
 * \return occurances
 */
double document::getOccurances(){
    return occurances;
}
/*!
 * \fn getter for total words
 * \return total words
 */
double document::getTotalWords(){
    return totalWords;
}
/*!
 * \fn increase the number of occurances of word
 */
void document::incCount(){
    occurances++;
}
/*!
 * \fn set the number of occurances of a word
 * \param n number of occurances
 */
void document::setOccurances(int n){
    occurances = n;
}
/*!
 * \fn set the number of total words
 * \param n total words
 */
void document::setTotalWords(int n){
    totalWords = n;
}
/*!
 * \fn override > operator
 * compare frequencies of word
 * \param doc document to compare to
 * \return whether frequency was greater or not
 */
bool document::operator> (const document& doc) const{
    return (occurances/totalWords > doc.occurances/doc.totalWords);
}
template <class a, class b>
std::ostream& operator<< (std::ostream& out, const document& d){
    out << d.id << " " << d.totalWords << " " << d.occurances;
    return out;
}

