#include <utils.hpp>

int fillList(List **head)
{
    List *current = new List;
    List *prev;
    *head = current;
    int count = 0;
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL)
    {
        cout << "Error: failed to open file!" << endl;
        fclose(file);
        return -1;
    }
    while (fread(&current->data, sizeof(current->data), 1, file) == 1)
    {
        List *next = new List;
        current->next = next;
        next->next = NULL;
        prev = current;
        current = next;
        count++;
    }
    current = prev;
    current->next = NULL;
    fclose(file);
    return count;
}

int compare(char *a, char *b)
{
    if (a[6] < b[6])
        return -1;
    if (a[6] > b[6])
        return 1;
    if (a[6] == b[6])
    {
        if (a[7] < b[7])
            return -1;
        if (a[7] > b[7])
            return 1;
    }
    return 0;
}

bool isNumber(string string)
{
    if (!string.length())
        return false;

    for (char symbol : string)
        if (!isdigit(symbol))
            return false;

    return true;
}

int getPageNumber(int numberOfPages)
{
    while (true)
    {
        cout << "Enter page number (0 to exit): ";
        string key;
        int number = -1;
        getline(cin, key);

        bool result = isNumber(key);

        if (result)
            number = stoi(key);

        if (!result || number > numberOfPages)
        {
            cout << "Error: expected number between 1 and " << numberOfPages << "." << endl;
            continue;
        }

        return number;
    }
}

void printTableHeader(int number, bool isTree)
{
    system("cls");
    cout << "Page number " << number << endl
         << endl;
    cout << "\t\b\bIndex\t|\t";
    cout << "Full name of the citizen\t|\t";
    cout << "Street name\t|\t";
    cout << "\b\bHouse\t|\t";
    cout << "Apartment\t|\t";
    cout << "\b\b\bSettlement date" << endl;
    for (int i = 0; i < 150; i++)
        cout << "-";

    if (!isTree)
        cout << endl
             << "\t";
    else
        cout << endl
             << "  ";
}

void printList(List *head, int number)
{
    List *current = head;

    if (!number)
        return;

    printTableHeader(number);

    int end = number * 20;
    int count = end - 20 + 1;

    for (int i = 1; i < count; i++)
        current = current->next;

    for (count; count <= end; count++)
    {
        cout << count << "\t|\t";
        cout << current->data.name << "\t|\t";
        cout << current->data.streetName << "\b|\t";
        cout << current->data.houseNumber << "\t|\t";
        cout << "   " << current->data.apartmentNumber << "\t\t|\t";
        cout << current->data.settlementDate << endl
             << "\t";
        current = current->next;
    }
    cout << endl;
}