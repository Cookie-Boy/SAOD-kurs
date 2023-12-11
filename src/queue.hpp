#pragma once

#include <cstring>

#include <utils.hpp>

void fillIndexArray(List *head, List **array, int size);
int binarySearch(List **array, int size, const char *searchKey);
int buildQueue(List **array, List **&queue, int index, const char *searchKey);
List **getFinalQueue(List **indexArray, int &queueSize);
void printQueue(List **queue, int size, int pageNumber);