#include <iomanip>
#include <windows.h>

#include <encoding.hpp>
#include <queue.hpp>
#include <sorting.hpp>
#include <tree.hpp>
#include <utils.hpp>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ".866");
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    bool modes[6] = {false};
    modes[0] = true;
    int pages = PAGES;

    List *head = NULL;
    int count = fillList(&head);
    if (count == -1)
        return 1;

    List *copy = NULL;
    int copyCount = fillList(&copy);
    if (copyCount == -1)
        return 1;
    digitalSort(copy);

    List *indexArray[SIZE];
    fillIndexArray(copy, indexArray, SIZE);
    int queueSize = 0;
    List **queue = NULL;

    DBDVertex *root = NULL;
    int vr = 1, hr = 1, treeSize = 0;
    bool isIncrease = true;
    vector<DBDVertex *> vertexArray;
    vector<DBDVertex *> equalArray;

    int dbSize = -1;
    unsigned char *data = loadFile(&dbSize, FILE_NAME);

    vector<unsigned char> uniqSymbols;
    for (int i = 0; i < dbSize; i++)
    {
        if (!isInside(uniqSymbols, data[i]))
            uniqSymbols.push_back(data[i]);
    }
    int n = uniqSymbols.size();

    double P[n];
    getP(data, P, uniqSymbols, dbSize);
    insertSort(uniqSymbols, P, n);
    double Q[n + 1];
    int L[n];
    createGilbertMooreCode(P, Q, L, n);
    unsigned char **C = calculation(Q, L, n);

    int number = 1;

    while (number != 0)
    {
        system("cls");
        cout << "View Mode: ";
        if (modes[0])
        {
            pages = PAGES;
            cout << "regular database" << endl;
            printList(head, number);
        }
        else if (modes[1])
        {
            pages = PAGES;
            cout << "sorted database" << endl;
            printList(copy, number);
        }
        else if (modes[2])
        {
            cout << "queue" << endl;
            printQueue(queue, queueSize, number);
        }
        else if (modes[3])
        {
            cout << "search tree" << endl;
            printTreeAsTable(vertexArray, treeSize, number);
        }
        else if (modes[4])
        {
            cout << "finding a vertex in a tree" << endl;
            printTreeAsTable(equalArray, equalArray.size(), number);
        }
        else if (modes[5])
        {
            cout << "encoding" << endl;
            printCodeTable(uniqSymbols, C, P, L, n);
        }

        int result = getPageNumber(pages);

        if (result == -3)
        {
            if (!queueHandler(queue, indexArray, queueSize, pages))
                continue;
        }
        else if (result == -4)
        {
            if (queue != NULL)
            {
                root = deleteTree(root);
                for (int i = 0; i < queueSize; i++)
                {
                    insertToBinaryTree(root, &queue[i], vr, hr, isIncrease);
                    if (isIncrease)
                        treeSize++;
                    else
                        isIncrease = true;
                }
                fillNumbers(root);
                getTreeTraversal(root, vertexArray, treeSize, pages);
            }
            else
            {
                cout << "Error: you must build the queue first." << endl;
                cout << "Press any key to continue...";
                _getch();
                continue;
            }
        }
        else if (result == -5)
        {
            if (root != NULL)
            {
                findingVertexHandler(root, equalArray, pages);
                if (equalArray.size() == 0)
                    continue;
            }
            else
            {
                cout << "Error: you must build the tree first." << endl;
                cout << "Press any key to continue...";
                _getch();
                continue;
            }
        }

        if (result >= -6 && result < 0)
        {
            number = 1;
            for (int i = 0; i < 6; i++)
                if (modes[i])
                    modes[i] = false;
            modes[abs(result) - 1] = true;
        }
        else if (result != NO_PAGE)
        {
            number = result;
        }
    }

    return 0;
}