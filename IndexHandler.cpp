
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include "include/porter2_stemmer/porter2_stemmer.h"
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "IndexHandler.h"
#include "document.h"

using namespace std;

IndexHandler::IndexHandler(){
    totalDocs = 0;
    totalWordsOverall = 0;
}

void IndexHandler::uploadData(string path){
    ifstream stopWordsFile("stopwords.txt");
    vector<string> stopWords;
    string s;
    if (stopWordsFile.is_open()){
        while ( getline (stopWordsFile, s) ){
            s.erase(s.size() - 1);
            stopWords.push_back(s);
        }
        stopWordsFile.close();
    }
    for(auto& p: filesystem::directory_iterator(path)){
        //check if file is correct to read
        string id = p.path().stem();
        totalDocs++;
        if(p.path().extension() == ".json" && id.substr(0, 2) != "~$"){
            if(totalDocs%100 == 0)
                cout << totalDocs << " " << id << endl;
            //open file and store into reader
            FILE* fp = fopen(p.path().c_str(), "rb");
            char readBuffer[65536];
            rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
            rapidjson::Document d;
            d.ParseStream(is);
            if(d["metadata"]["title"].IsString() && d["abstract"].IsArray() && d["metadata"]["authors"].IsArray() && d["body_text"].IsArray()){
                //get total number of words
                int totalWords = 0;
                istringstream stream(d["metadata"]["title"].GetString());
                while(stream){
                    stream >> s;
                    totalWords++;
                }
                const rapidjson::Value& at = d["abstract"];
                for (rapidjson::SizeType i = 0; i < at.Size(); i++)
                {
                    const rapidjson::Value& c = at[i];
                    istringstream stream2(c["text"].GetString());
                    while(stream2){
                        stream2 >> s;
                        totalWords++;
                    }
                }
                const rapidjson::Value& b = d["body_text"];
                for (rapidjson::SizeType i = 0; i < b.Size(); i++)
                {
                    const rapidjson::Value& c = b[i];
                    istringstream stream3(c["text"].GetString());
                    while(stream3){
                        stream3 >> s;
                        totalWords++;
                    }
                }
                totalWordsOverall += totalWords;
                //gather author information
                const rapidjson::Value& b1 = d["metadata"]["authors"];
                for (rapidjson::SizeType i = 0; i < b1.Size(); i++) {
                    const rapidjson::Value &c = b1[i];
                    document doc(id, b1.Size());
                    doc.incCount();
                    authorsToDocuments.insert(c["last"].GetString(), doc);
                }
                //loop through Title
                istringstream iss(d["metadata"]["title"].GetString());
                while(iss){
                    iss >> s;
                    for(int i=0;i<s.size();i++){
                        if(!isalnum(s.at(i))){
                            s = s.erase(i, 1);
                        }
                    }
                    std::for_each(s.begin(), s.end(), [](char & c){c = ::tolower(c);});
                    Porter2Stemmer::stem(s);
                    //change word to simple word
                    bool found = false;
                    for(int j=0;j<stopWords.size();j++){
                        if(s == stopWords.at(j)) {
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        //check if word already exists in AVL Tree
                        if(wordsToDocuments.contains(s)) {
                            //get vector of Documents including word
                            vector<document> &v = wordsToDocuments.get(s);
                            //check if word contains document
                            found = false;
                            for(int i=0;i<v.size();i++){
                                if(v.at(i).getID() == id){
                                    v.at(i).incCount();
                                    found = true;
                                }
                            }
                            if(!found){
                                document doc(id, totalWords);
                                doc.incCount();
                                v.push_back(doc);
                            }
                        }
                            //add word to tree
                        else {
                            vector<document> v;
                            document doc(id, totalWords);
                            doc.incCount();
                            v.push_back(doc);
                            wordsToDocuments.insert(s, v);
                        }
                    }
                }
                //loop through abstract
                const rapidjson::Value& b2 = d["abstract"];
                for (rapidjson::SizeType i = 0; i < b2.Size(); i++)
                {
                    const rapidjson::Value& c = b2[i];
                    istringstream iss3(c["text"].GetString());
                    while(iss3){
                        iss3 >> s;
                        //change word to simple word
                        for (int i = s.size()-1; i >= 0; i--) {
                            if (!isalnum(s.at(i))) {
                                s = s.erase(i, 1);
                            }
                        }
                        std::for_each(s.begin(), s.end(), [](char &c) { c = ::tolower(c); });
                        Porter2Stemmer::stem(s);
                        bool found = false;
                        for(int j=0;j<stopWords.size();j++){
                            if(s == stopWords.at(j)) {
                                found = true;
                                break;
                            }
                        }
                        if(!found) {
                            //check if word already exists in AVL Tree
                            if (wordsToDocuments.contains(s)) {
                                //get vector of Documents including word
                                vector<document> &v = wordsToDocuments.get(s);
                                //check if word contains document
                                bool found = false;
                                for (int i = 0; i < v.size(); i++) {
                                    if (v.at(i).getID() == id) {
                                        v.at(i).incCount();
                                        found = true;
                                    }
                                }
                                if (!found) {
                                    document doc(id, totalWords);
                                    doc.incCount();
                                    v.push_back(doc);
                                }
                            }
                                //add word to tree
                            else {
                                vector<document> v;
                                document doc(id, totalWords);
                                doc.incCount();
                                v.push_back(doc);
                                wordsToDocuments.insert(s, v);
                            }
                        }
                    }
                }
                const rapidjson::Value& bt = d["body_text"];
                for (rapidjson::SizeType i = 0; i < bt.Size(); i++)
                {
                    const rapidjson::Value& c = bt[i];
                    istringstream iss3(c["text"].GetString());
                    while(iss3){
                        iss3 >> s;
                        //change word to simple word
                        for (int i = s.size()-1; i >= 0; i--) {
                            if (!isalnum(s.at(i))) {
                                s = s.erase(i, 1);
                            }
                        }
                        std::for_each(s.begin(), s.end(), [](char &c) { c = ::tolower(c); });
                        Porter2Stemmer::stem(s);
                        bool found = false;
                        for(int j=0;j<stopWords.size();j++){
                            if(s == stopWords.at(j)) {
                                found = true;
                                break;
                            }
                        }
                        if(!found) {
                            //check if word already exists in AVL Tree
                            if (wordsToDocuments.contains(s)) {
                                //get vector of Documents including word
                                vector<document> &v = wordsToDocuments.get(s);
                                //check if word contains document
                                bool found = false;
                                for (int i = 0; i < v.size(); i++) {
                                    if (v.at(i).getID() == id) {
                                        v.at(i).incCount();
                                        found = true;
                                    }
                                }
                                if (!found) {
                                    document doc(id, totalWords);
                                    doc.incCount();
                                    v.push_back(doc);
                                }
                            }
                                //add word to tree
                            else {
                                vector<document> v;
                                document doc(id, totalWords);
                                doc.incCount();
                                v.push_back(doc);
                                wordsToDocuments.insert(s, v);
                            }
                        }
                    }
                }
            }
            fclose(fp);
        }
    }
}
void IndexHandler::createPersistentIndex(){
    wordsToDocuments.storeData();
}

void IndexHandler::upLoadFromPersistentIndex(){
    ifstream file("persistentIndex.txt");
    string s;
    while(getline(file, s)){
        istringstream iss(s);
        string word;
        iss >> word;
        vector<document> v;
        while(iss){
            string id;
            int occurances, totalWords;
            iss >> id >> occurances >> totalWords;
            document d(id, totalWords);
            d.setOccurances(occurances);
            v.push_back(d);
        }
        v.pop_back();
        wordsToDocuments.insert(word, v);
    }
}

bool IndexHandler::containsWord(string key){
    return wordsToDocuments.contains(key);
}
bool IndexHandler::containsAuthor(string key){
    return authorsToDocuments.contains(key);
}
vector<document>& IndexHandler::getWord(string key){
    vector<document> v;
    try{
        return wordsToDocuments.get(key);
    } catch (const std::logic_error& e){
        cout << key << " not found" << endl;
    }
}
vector<document> IndexHandler::getAuthor(string key){
    return authorsToDocuments.get_value(key);
}
void IndexHandler::clearIndex(){
    authorsToDocuments.clearData();
    wordsToDocuments.clear();
}
int IndexHandler::getTotalDocs(){
    return totalDocs;
}
int IndexHandler::avgNumWords(){
    return totalWordsOverall/totalDocs;
}
float IndexHandler::getUniqueWords(){
    return wordsToDocuments.getSize();
}
int IndexHandler::getNumAuthors(){
    return authorsToDocuments.getNumElemnets();
}