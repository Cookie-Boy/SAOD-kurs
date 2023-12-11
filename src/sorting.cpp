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

void cyclePrint(List *head, List *copy)
{
    while (true)
    {
        system("cls");
        cout << "What would you like to see? (sorted database - 1, unsorted - 2, exit - 0): ";

        char key = _getch();
        if (key == '1')
        {
            system("cls");
            printList(copy, 1);
            while (int number = getPageNumber(PAGES))
                printList(copy, number);
        }
        else if (key == '2')
        {
            system("cls");
            printList(head, 1);
            while (int number = getPageNumber(PAGES))
                printList(head, number);
        }
        else if (key == '0')
        {
            system("cls");
            return;
        }
    }
}