#include <queue.hpp>

void fillIndexArray(List *head, List **array, int size)
{
    List *current = head;

    for (int i = 0; i < size; i++)
    {
        array[i] = current;
        current = current->next;
    }
}

int binarySearch(List **array, int size, const char *searchKey)
{
    int left = 0, right = size - 1;
    while (left < right)
    {
        int middle = (left + right) / 2;
        if (strncmp(array[middle]->data.name, searchKey, 3) < 0)
            left = middle + 1;
        else
            right = middle;
    }
    if (!strncmp(array[right]->data.name, searchKey, 3))
        return right;
    return -1;
}

int buildQueue(List **array, List **&queue, int index, const char *searchKey)
{
    int count = 0;
    for (int i = index; !strncmp(array[i]->data.name, searchKey, 3); i++)
    {
        count++;
    }
    queue = new List *[count];
    for (int i = index, j = 0; j < count; i++, j++)
        queue[j] = array[i];
    return count;
}

bool queueHandler(List **&queue, List **indexArray, int &queueSize, int &numberOfPages)
{
    while (true)
    {
        system("cls");
        cout << "Enter search key (first 3 letters of the last name, 0 - back to the menu): ";
        string stringKey;
        getline(cin, stringKey);
        if (stringKey == "0")
            return false;
        const char *searchKey = stringKey.c_str();
        int index = binarySearch(indexArray, SIZE, searchKey);

        if (index >= 0)
        {
            delete[] queue;
            queue = NULL;
            queueSize = buildQueue(indexArray, queue, index, searchKey);
            numberOfPages = queueSize / 20;
            int mod = queueSize % 20;
            if (mod > 0)
                numberOfPages++;
            return true;
        }
        cout << endl
             << endl
             << "Error: user not found!";
        cout << endl
             << "Press any key to continue...";
        _getch();
    }
}

void printQueue(List **queue, int size, int pageNumber)
{
    if (!pageNumber)
        return;

    printTableHeader(pageNumber);

    int numberOfPages = size / 20;
    int mod = size % 20;
    if (mod > 0)
        numberOfPages++;

    int end = 0, count = 0;

    if (pageNumber != numberOfPages)
    {
        end = pageNumber * 20;
        count = end - 20 + 1;
    }
    else
    {
        end = (pageNumber - 1) * 20 + mod;
        count = (pageNumber - 1) * 20 + 1;
    }

    for (count; count <= end; count++)
    {
        cout << count << "\t|\t";
        cout << queue[count - 1]->data.name << "\t|\t";
        cout << queue[count - 1]->data.streetName << "\b|\t";
        cout << queue[count - 1]->data.houseNumber << "\t|\t";
        cout << "   " << queue[count - 1]->data.apartmentNumber << "\t\t|\t";
        cout << queue[count - 1]->data.settlementDate << endl
             << "\t";
    }
    cout << endl;
}