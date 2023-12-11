#include <encoding.hpp>

void insertSort(vector<unsigned char> &symbols, double *P, int n)
{
    for (int i = 1; i < n; i++)
    {
        double temp = P[i];
        char tempData = symbols[i];
        int j = i - 1;
        while ((j >= 0) && (temp > P[j]))
        {
            P[j + 1] = P[j];
            symbols[j + 1] = symbols[j];
            j = j - 1;
        }
        P[j + 1] = temp;
        symbols[j + 1] = tempData;
    }
}

unsigned char *loadFile(int *size, const char *name)
{
    FILE *file = fopen(name, "rb");
    if (file == NULL)
    {
        printf("??? ???? ???.\n");
        exit(1);
    }
    struct stat Stat;
    int error = fstat(fileno(file), &Stat);
    if (error != 0)
    {
        printf("???? ??????? stat ???: %d\n", error);
        exit(1);
    }
    *size = Stat.st_size;
    unsigned char *data = new unsigned char[*size];
    fread(data, *size, 1, file);
    fclose(file);
    return data;
}

void getP(unsigned char *data, double *P, vector<unsigned char> &symbols, int size)
{
    for (int i = 0; i < symbols.size(); i++)
    {
        int frequency = 0;
        for (int j = 0; j < size; j++)
            if (data[j] == symbols[i])
                frequency++;

        P[i] = (double)frequency / size;
    }
}

bool isInside(vector<unsigned char> &array, int element)
{
    if (array.size() == 0)
        return false;

    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

unsigned char **calculation(double *Q, int *L, int n)
{
    unsigned char **C = new unsigned char *[n];
    for (int i = 0; i < n; i++)
    {
        int Li = L[i];
        unsigned char *str = C[i] = new unsigned char[Li + 1];
        str[Li] = 0;
        for (int j = 0; j < Li; j++)
        {
            Q[i] *= 2;
            str[j] = Q[i] >= 1 ? '1' : '0';
            if (Q[i] >= 1)
                Q[i]--;
        }
    }
    return C;
}

void createGilbertMooreCode(double *P, double *Q, int *L, int n)
{
    double pSum = 0;
    for (int i = 0; i < n; i++)
    {
        Q[i] = pSum + P[i] / 2;
        pSum += P[i];
        L[i] = -floor(log2f(P[i])) + 1;
    }
}

double sumP(double *P, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i];
    return sum;
}

double getEntropy(double *P, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += P[i] * log2f(P[i]);
    }

    return sum * (-1);
}

double getAverageLength(double *P, int *L, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i] * L[i];
    return sum;
}