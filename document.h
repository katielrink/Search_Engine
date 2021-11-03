
#ifndef SEARCH_ENGINE_DOCUMENT_H
#define SEARCH_ENGINE_DOCUMENT_H

#include <iostream>
#include <string>

using namespace std;

class document {
    private:
        string id;
        //term-frequency/inverse document frequency metric
        double occurances;
        double totalWords;
    public:
        document(string, int);
        document(const document&);
        ~document();
        void operator= (const document&);
        bool operator== (const document&);
        bool operator> (const document&) const;
        //getters
        string getID();
        double getFrequency();
        double getOccurances();
        double getTotalWords();

        //modifiers
        void incCount();
        void setOccurances(int);
        void setTotalWords(int);

        friend std::ostream& operator<< (std::ostream&, const document&);
};


#endif //SEARCH_ENGINE_DOCUMENT_H
