#include <tree.hpp>

void insertToBinaryTree(DBDVertex *&vertex, List **element, int &vr, int &hr, bool &isIncrease)
{
    if (vertex == NULL)
    {
        vertex = new DBDVertex;
        vertex->balance = 0;
        vertex->number = 0;
        vertex->element = (*element);
        vertex->left = NULL;
        vertex->right = NULL;
        vertex->equal = NULL;
        vr = 1;
    }
    else if (strncmp(vertex->element->data.settlementDate, (*element)->data.settlementDate, 2) > 0)
    // else if (compare(vertex->element->data.settlementDate, (*element)->data.settlementDate) > 0)
    {
        insertToBinaryTree(vertex->left, element, vr, hr, isIncrease);
        if (vr == 1)
        {
            if (vertex->balance == 0)
            {
                DBDVertex *q = vertex->left;
                vertex->left = q->right;
                q->right = vertex;
                vertex = q;
                q->balance = 1;
                vr = 0;
                hr = 1;
            }
            else
            {
                vertex->balance = 0;
                vr = 1;
                hr = 0;
            }
        }
        else
        {
            hr = 0;
        }
    }
    else if (strncmp(vertex->element->data.settlementDate, (*element)->data.settlementDate, 2) < 0)
    // else if (compare(vertex->element->data.settlementDate, (*element)->data.settlementDate) < 0)
    {
        insertToBinaryTree(vertex->right, element, vr, hr, isIncrease);
        if (vr == 1)
        {
            vertex->balance = 1;
            hr = 1;
            vr = 0;
        }
        else if (hr == 1)
        {
            if (vertex->balance == 1)
            {
                DBDVertex *q = vertex->right;
                vertex->balance = 0;
                q->balance = 0;
                vertex->right = q->left;
                q->left = vertex;
                vertex = q;
                vr = 1;
                hr = 0;
            }
            else
            {
                hr = 0;
            }
        }
    }
    else
    {
        DBDVertex *q = vertex;
        while (q->equal != NULL)
            q = q->equal;
        
        DBDVertex *equalVertex = new DBDVertex;
        equalVertex->balance = 0;
        equalVertex->number = 0;
        equalVertex->element = (*element);
        equalVertex->left = NULL;
        equalVertex->right = NULL;
        equalVertex->equal = NULL;

        q->equal = equalVertex;
        isIncrease = false;
    }
}

void fillNumbers(DBDVertex *vertex)
{
    vector<DBDVertex *> queue;
    queue.push_back(vertex);

    int count = 1;

    while (queue.size() > 0)
    {
        DBDVertex *currentNode = queue[0];
        queue.erase(queue.begin());
        if (currentNode->number == 0)
        {
            currentNode->number = count++;

            if (currentNode->left != NULL)
            {
                queue.push_back(currentNode->left);
                if (currentNode->left->balance == 1)
                {
                    queue.push_back(currentNode->left->right);
                }
            }

            if (currentNode->right != NULL)
            {
                queue.push_back(currentNode->right);
                if (currentNode->right->balance == 1)
                {
                    queue.push_back(currentNode->right->right);
                }
            }
        }
    }
}

void cycleFindVertex(DBDVertex *root)
{
    while (true)
    {
        system("cls");
        cout << "Enter search key (0 - back to the tree): ";
        string stringKey;
        getline(cin, stringKey);
        if (stringKey == "0")
            return;
        char *searchKey = new char[stringKey.length() + 1];
        strcpy(searchKey, stringKey.c_str());
        DBDVertex *foundVertex = findVertex(root, searchKey);

        if (foundVertex == NULL)
        {
            cout << endl << endl << "Error: vertex not found!";
            cout << endl << "Press any key to continue...";
            _getch();
        }
        else
        {
            vector<DBDVertex *> massiveToShow;
            while (foundVertex != NULL)
            {
                massiveToShow.push_back(foundVertex);
                foundVertex = foundVertex->equal;
            }

            int numberOfPages = massiveToShow.size() / 20;
            int mod = massiveToShow.size() % 20;
            if (mod > 0)
                numberOfPages++;

            printTreeAsTable(massiveToShow, massiveToShow.size(), 1);
            while (int number = getPageNumber(numberOfPages))
                printTreeAsTable(massiveToShow, massiveToShow.size(), number);
        }
    }
}

void printTree(DBDVertex *root, int treeSize)
{
    int numberOfPages = treeSize / 20;
    int mod = treeSize % 20;
    if (mod > 0)
        numberOfPages++;

    vector<DBDVertex *> massiveToShow;

    while (true)
    {
        massiveToShow.clear();
        system("cls");
        cout << "Select tree traversal: (Top to down - 1, left to right - 2, down to top - 3, find value - 4, exit - 0): ";

        char key = _getch();
        if (key == '1')
        {
            fillTopToBottom(root, massiveToShow);
        }
        else if (key == '2')
        {
            fillLeftToRight(root, massiveToShow);
        }
        else if (key == '3')
        {
            fillBottomToTop(root, massiveToShow);
        }
        else if (key == '4')
        {
            cycleFindVertex(root);
            continue;
        }
        else if (key == '0')
        {
            system("cls");
            return;
        }

        system("cls");
        printTreeAsTable(massiveToShow, treeSize, 1);
        while (int number = getPageNumber(numberOfPages))
            printTreeAsTable(massiveToShow, treeSize, number);
    }
}

void printTreeAsTable(vector <DBDVertex *> &array, int size, int pageNumber)
{
    if (!pageNumber)
        return;

    printTableHeader(pageNumber, true);

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
        cout << "\t" << count << "\t|\t";
        // if (array[count - 1]->number == 0)
        //     cout << "-" << "\t|\t";
        // else
        //     cout << array[count - 1]->number << "\t|\t";
        cout << array[count - 1]->element->data.name << "\t|\t";
        cout << array[count - 1]->element->data.streetName << "\b|\t";
        cout << array[count - 1]->element->data.houseNumber << "\t|\t";
        cout << "   " << array[count - 1]->element->data.apartmentNumber << "\t\t|\t";
        cout << array[count - 1]->element->data.settlementDate << endl << "  ";
    }
    cout << endl;
}

void fillTopToBottom(DBDVertex *vertex, vector<DBDVertex *> &array)
{
    DBDVertex *current = vertex;

    if (current != NULL)
    {
        array.push_back(current);
        fillTopToBottom(current->left, array);
        fillTopToBottom(current->right, array);
    }
}

void fillLeftToRight(DBDVertex *vertex, vector<DBDVertex *> &array)
{
    DBDVertex *current = vertex;

    if (current != NULL)
    {
        fillLeftToRight(current->left, array);
        array.push_back(current);
        fillLeftToRight(current->right, array);
    }
}

void fillBottomToTop(DBDVertex *vertex, vector<DBDVertex *> &array)
{
    DBDVertex *current = vertex;

    if (current != NULL)
    {
        fillBottomToTop(current->left, array);
        fillBottomToTop(current->right, array);
        array.push_back(current);
    }
}

DBDVertex *findVertex(DBDVertex *vertex, char *searchKey)
{
    if (vertex == NULL)
        return NULL;
    if (strncmp(vertex->element->data.settlementDate, searchKey, 2) > 0)
    // if (compare(vertex->element->data.settlementDate, searchKey) > 0)
        return findVertex(vertex->left, searchKey);
    else if (strncmp(vertex->element->data.settlementDate, searchKey, 2) < 0)
    // else if (compare(vertex->element->data.settlementDate, searchKey) < 0)
        return findVertex(vertex->right, searchKey);
    return vertex;
}