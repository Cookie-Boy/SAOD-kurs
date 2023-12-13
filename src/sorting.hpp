#pragma once

#include <conio.h>

#include <utils.hpp>

#define SORT_START 0
#define SORT_END 49

typedef struct queue
{
    List *head;
    List *tail;
} Queue;

void digitalSort(List *&head);