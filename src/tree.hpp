#pragma once

#include <conio.h>
#include <cstring>
#include <vector>

#include <utils.hpp>

struct DBDVertex
{
    List *element;
    int number;
    int balance;
    DBDVertex *left;
    DBDVertex *right;
    DBDVertex *equal;
};

void insertToBinaryTree(DBDVertex *&vertex, List **element, int &vr, int &hr, bool &isIncrease);
void fillNumbers(DBDVertex *vertex);
void printTree(DBDVertex *root, int treeSize);
void printTreeAsTable(vector <DBDVertex *> &array, int size, int pageNumber);
void fillTopToBottom(DBDVertex *vertex, vector<DBDVertex *> &array);
void fillLeftToRight(DBDVertex *vertex, vector<DBDVertex *> &array);
void fillBottomToTop(DBDVertex *vertex, vector<DBDVertex *> &array);
DBDVertex *findVertex(DBDVertex *vertex, char *searchKey);
void cycleFindVertex(DBDVertex *root);