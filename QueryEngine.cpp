//
// Created by katie on 4/14/2021.
//
#include "include/porter2_stemmer/porter2_stemmer.h"
#include <sstream>
#include <stdexcept>
#include "QueryEngine.h"
#include "IndexHandler.h"

#define DEBUG false

QueryEngine::QueryEngine(){

}
vector<document> QueryEngine::runQuery(string query){
    tested = false;
    results.clear();
    stringstream s(query);
    string word;
    while (s >> word){
        if(word == "AND"){
            tested = true;
            vector<string> words;
            while(s >> word && word != "NOT" && word != "AUTHOR"){
                Porter2Stemmer::stem(word);
                words.push_back(word);
            }
            ANDfucntion(words);
        } else if(word == "OR"){
            tested = true;
            vector<string> words;
            while(s >> word && word != "NOT" && word != "AUTHOR"){
                Porter2Stemmer::stem(word);
                words.push_back(word);
            }
            ORfunction(words);
        } else {
            tested = true;
            vector<string> words;
            Porter2Stemmer::stem(word);
            words.push_back(word);
            ORfunction(words);
        }
        if(word == "NOT"){
            s >> word;
            Porter2Stemmer::stem(word);
            NOTfunction(word);
        }
        if(word == "AUTHOR"){
            s >> word;
            authorFunction(word);
        }
    }
    std::sort(results.begin(), results.end(),greater<document>());
    return results;
}
void QueryEngine::ANDfucntion(vector<string> words){
    if(DEBUG) cout << "AND function" << endl;
    for(int i=0;i<words.size();i++){
        if(IH.containsWord(words.at(i))){
            vector wordWorks = IH.getWord(words.at(i));
            if(results.empty()){
                for(int j=0;j<wordWorks.size();j++){
                    results.push_back(wordWorks.at(j));
                }
            } else {
                for(int l=results.size()-1;l>=0;l--) {
                    bool found = false;
                    for (int j = 0; j < wordWorks.size(); j++) {
                        if (wordWorks.at(j).getID() == results.at(l).getID())
                            found = true;
                    }
                    if (!found) {
                        results.erase(results.cbegin() + l);
                    }
                }
            }
        } else {
            results.clear();
            break;
        }
    }
}
void QueryEngine::ORfunction(vector<string> words){
    if(DEBUG) cout << "OR function" << endl;
    for(int i=0;i<words.size();i++){
        if(IH.containsWord(words.at(i))){
            vector wordWorks = IH.getWord(words.at(i));
            if(results.empty()){
                for(int j=0;j<wordWorks.size();j++){
                    results.push_back(wordWorks.at(j));
                }
            } else {
                for(int l=0;l<wordWorks.size();l++) {
                    bool found = false;
                    for (int j = 0; j < results.size(); j++) {
                        if (wordWorks.at(l).getID() == results.at(j).getID())
                            found = true;
                    }
                    if (!found) {
                        results.push_back(wordWorks.at(l));
                    }
                }
            }
        }
    }
}
void QueryEngine::NOTfunction(string word){
    if(DEBUG) cout << "NOT function" << endl;
    if(IH.containsWord(word)){
        vector v = IH.getWord(word);
        for(int i=results.size()-1;i>=0 && !results.empty();i--){
            for(int j=0;j<v.size();j++){
                if(results.at(i).getID() == v.at(j).getID()) {
                    results.erase(results.cbegin() + i);
                    break;
                }
            }
        }
    }
}
void QueryEngine::authorFunction(string A){
    if(DEBUG) cout << "AUTHOR function" << endl;
    if(IH.containsAuthor(A)){
        vector<document> authorWorks = IH.getAuthor(A);
        if(authorWorks.empty())
            cout << "No results" << endl;
        else if(results.empty() && !tested){
            for(int i=0;i<authorWorks.size();i++){
                results.push_back(authorWorks.at(i));
            }
        } else {
            for(int i=results.size()-1;i>=0;i--){
                bool found = false;
                for(int j=0;j<authorWorks.size();j++){
                    if(authorWorks.at(j).getID()==results.at(i).getID())
                        found = true;
                }
                if(!found){
                    results.erase(results.cbegin()+i);
                }
            }
        }
    } else {
        results.clear();
    }
}
void QueryEngine::clearIndex(){
    return IH.clearIndex();
}
void QueryEngine::parseIndex(string path){
    return IH.uploadData(path);
}
int QueryEngine::getTotalDocs(){
    return IH.getTotalDocs();
}
int QueryEngine::avgNumWords(){
    return IH.avgNumWords();
}
float QueryEngine::getUniqueWords(){
    return IH.getUniqueWords();
}
int QueryEngine::getNumAuthors(){
    return IH.getNumAuthors();
}
void QueryEngine::createPersistentIndex(){
    IH.createPersistentIndex();
}
void QueryEngine::loadPersistentIndex(){
    IH.upLoadFromPersistentIndex();
}