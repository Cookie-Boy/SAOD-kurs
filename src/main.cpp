#include <windows.h>
#include <iomanip>

#include <utils.hpp>
#include <sorting.hpp>
#include <queue.hpp>
#include <tree.hpp>
#include <encoding.hpp>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ".866");
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    List *head = NULL;
    int count = fillList(&head);
    if (count == -1)
        return 1;
    printList(head, 1);

    while (int number = getPageNumber(PAGES))
        printList(head, number);

    system("cls");

    List *copy = NULL;
    int copyCount = fillList(&copy);
    if (copyCount == -1)
        return 1;

    digitalSort(copy);
    cout << "Database successfully sorted by citizen name and street name." << endl;
    cout << "Press any key to continue...";
    _getch();
    cyclePrint(head, copy);

    List *indexArray[SIZE];
    fillIndexArray(copy, indexArray, SIZE);

    int queueSize = 0;
    List **queue = getFinalQueue(indexArray, queueSize);

    DBDVertex *root = NULL;
    int vr = 1, hr = 1;

    int treeSize = 0;
    bool isIncrease = true;

    for (int i = 0; i < queueSize; i++)
    {
        insertToBinaryTree(root, &queue[i], vr, hr, isIncrease);
        if (isIncrease)
            treeSize++;
        else
            isIncrease = true;
    }
    fillNumbers(root);
    printTree(root, treeSize);

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
    cout.precision(7);

    cout << "Энтропия\tИзбыточость\tСумма вероятностей\tКол-во символов" << endl;
    double entropy = getEntropy(P, n);
    cout << entropy << "\t";
    cout << getAverageLength(P, L, n) - entropy << "\t\t";
    cout << sumP(P, n) << "\t\t";
    cout << n << endl << endl;


    cout << "Символ" << setw(20) << "Вероятность" << setw(20) << "Код.Слово" << setw(30) << "Длина код.слова" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << uniqSymbols[i];
        cout << setw(25) << P[i];
        string string;
        for (int j = 0; j < L[i]; j++)
            string.push_back(C[i][j]);
        cout << setw(20) << string;
        cout << setw(25) << L[i] << endl;
    }

    return 0;
}