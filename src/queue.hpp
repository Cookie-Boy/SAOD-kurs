#pragma once

#include <conio.h>
#include <cstring>


#include <utils.hpp>

void fillIndexArray(List *head, List **array, int size);
int binarySearch(List **array, int size, const char *searchKey);
int buildQueue(List **array, List **&queue, int index, const char *searchKey);
bool queueHandler(List **&queue, List **indexArray, int &queueSize, int &numberOfPages);
void printQueue(List **queue, int size, int pageNumber);