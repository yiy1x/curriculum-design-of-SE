#ifndef KMPSEARCH_H
#define KMPSEARCH_H

#include "Word.h"
#include "HalfFindWord.h"
#include "mystack.h"
#include "myqueue.h"

#define true 1
#define false 0

class KmpSearch
{


public:
    KmpSearch();
    ~KmpSearch();

    int searchSentence(char *);

    char *getSentence1();
    char *getSentence2();

    bool isEmpty();


private:
    //字母表
    char alphabet[26];

    char *fileName;

    Word word;

    HalfFindWord halfFindWord;

    void setNext(char* );

    int kmp(char *, char *);

    int next[SIZEOFWORD];

    char WordForUse[SIZEOFWORD];

    MyQueue stackSentence1;
    MyQueue stackSentence2;

};

inline char ChangToLitter(char ch)
{
    if (ch <= 90 && ch >= 65)
    {
        ch = ch + 32;
    }
    return ch;
}

#endif // KMPSEARCH_H
