#include <sorting.hpp>

void digitalSort(List *&head)
{
    Queue Q[256];
    int start = SORT_START, end = SORT_END;
    for (int j = end; j >= start; j--)
    {
        for (int i = 0; i < 256; i++)
        {
            Q[i].tail = (List *)&Q[i].head;
        }
        List *p = head;
        while (p != NULL)
        {
            unsigned char d = p->digit[j];
            Q[(int)d].tail->next = p;
            Q[(int)d].tail = p;
            p = p->next;
        }
        p = (List *)&head;
        for (int i = 0; i < 256; i++)
        {
            if (Q[i].tail != (List *)&Q[i].head)
            {
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
    }
}