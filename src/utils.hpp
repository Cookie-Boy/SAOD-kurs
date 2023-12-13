#pragma once

#include <iostream>
#include <string>

#define FILE_NAME "utils/testBase4.dat"
#define SIZE 4000
#define PAGES (SIZE / 20)
#define NO_PAGE 201

using namespace std;

typedef struct node
{
    char name[32];
    char streetName[18];
    short int houseNumber;
    short int apartmentNumber;
    char settlementDate[10];
} Data;

typedef struct list
{
    list *next;
    union
    {
        Data data;
        uint8_t digit[sizeof(data)];
    };
} List;

int fillList(List **head);
int compare(char *a, char *b);
bool isNumber(string string);
int getPageNumber(int amount);
void printTableHeader(int number, bool isTree = false);
void printList(List *head, int number);