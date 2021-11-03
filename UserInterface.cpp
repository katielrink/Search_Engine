
#include <iostream>
#include <sstream>
#include "UserInterface.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include "document.h"
#include "QueryEngine.h"

using namespace std;

void UserInterface::clearIndex(){
    QE.clearIndex();
}
void UserInterface::createPersistentIndex(){
    QE.createPersistentIndex();
}
void UserInterface::loadPersistentIndex(){
    QE.loadPersistentIndex();
}
void UserInterface::parseData(string path){
    documentPath = path;
    QE.parseIndex(path);
}
void UserInterface::query(string q){
    vector<document> v = QE.runQuery(q);
    if(v.size() == 0)
        cout << "No results" << endl;
    else{
        for(int i=0;i<v.size() && i<15;i++){
            cout << (i+1) << ") " << v.at(i).getID()  << endl;
            displayData(v.at(i).getID());
            cout << endl;
        }
        cout << "Enter the number of the article you would like to preview or 0 if you wish to view none:" << endl;
        int num;
        cin >> num;
        if(num != 0 && (num < v.size()+1 || v.size() >= 0))
            displayPreview(v.at(num-1).getID());
    }
}
//title, authors (at least the first), publication, date published
void UserInterface::displayData(string id){
    string doc = documentPath + "/" + id + ".json";
    FILE* fp = fopen(doc.c_str(), "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    cout << "Title: " << d["metadata"]["title"].GetString() << endl << "Author: ";
    const rapidjson::Value& b1 = d["metadata"]["authors"];
    for (rapidjson::SizeType i = 0; i < b1.Size(); i++) {
        const rapidjson::Value &c = b1[i];
        cout << c["last"].GetString() << " ";
    }
    cout << endl;
}
//display first 300 words
void UserInterface::displayPreview(string id){
    string doc = documentPath + "/" + id + ".json";
    FILE* fp = fopen(doc.c_str(), "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    const rapidjson::Value& bt = d["body_text"];
    string s;
    int cnt = 0;
    for (rapidjson::SizeType i = 0; i < bt.Size(); i++) {
        const rapidjson::Value &c = bt[i];
        istringstream iss(c["text"].GetString());
        while (iss && cnt<500) {
            cnt++;
            iss >> s;
            if(isalpha(s.at(0)) && cnt%15 != 1)
                cout << " " << s;
            else
                cout << s;
            if(cnt%15 == 0)
                cout << endl;
        }
    }
    cout << endl;
}
void UserInterface::printTotalDocuments(){
    cout << "Total Number of Documents : " << QE.getTotalDocs() << endl;
}
void UserInterface::printAverageNumberofWords(){
    cout << "Average number of words per document : " << QE.avgNumWords() << endl;
}
void UserInterface::printUniqueWords(){
    cout << "Number of unique words indexed : " << QE.getUniqueWords() << endl;
}
void UserInterface::printNumberofAuthors(){
    cout << "Number of authors indexed : " << QE.getNumAuthors() << endl;
}
void UserInterface::printOptions(){
    cout << "Enter [1] to clearIndex" << endl;
    cout << "Enter [2] to enter new Index" << endl;
    cout << "Enter [3] to create persistent index" << endl;
    cout << "Enter [4] to load from persistent index" << endl;
    cout << "Enter [5] to enter a search query" << endl;
    cout << "Enter [6] to show stats about index" << endl;
    cout << "Enter [7] to show options" << endl;
    cout << "Enter [-1] to exit" << endl;
}

UserInterface::UserInterface() {
    cout << "Welcome to the Search Engine::" << endl;
    printOptions();
    string answer;
    cin >> answer;
    string temp;
    getline(cin, temp);
    while(answer != "-1"){
        string path, q, id;
        if (answer == "1") {
            clearIndex();
            cout << "next choice :: " << endl;
        }
        else if (answer == "2") {
            cout << "Enter Path to Data :: " << endl;
            getline(cin, path);
            parseData(path);
            cout << "next choice :: " << endl;
        } else if(answer == "3") {
            createPersistentIndex();
            cout << "next choice :: " << endl;
        }else if (answer == "4") {
            loadPersistentIndex();
            cout << "next choice :: " << endl;
        }else if (answer == "5") {
                cout << "Please enter your search query :: " << endl;
                getline(cin, q);
                query(q);
                cout << "next choice :: " << endl;
        } else if(answer == "6") {
            printTotalDocuments();
            printAverageNumberofWords();
            printUniqueWords();
            printNumberofAuthors();
            cout << "next choice :: " << endl;
        }else if(answer == "7") {
            printOptions();
            cout << "next choice :: " << endl;
        } else {
            cout << "Please enter a valid number :: " << endl;
        }
        cin >> answer;
        getline(cin, temp);
    }
}