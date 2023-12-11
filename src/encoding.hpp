#pragma once

#include <vector>
#include <cmath>
#include <sys\stat.h>

#include <utils.hpp>

void insertSort(vector<unsigned char> &symbols, double *P, int n);
unsigned char *loadFile(int *size, const char *name);
void getP(unsigned char *data, double *P, vector<unsigned char> &symbols, int size);
bool isInside(vector<unsigned char> &array, int element);
unsigned char **calculation(double *Q, int *L, int n);
void createGilbertMooreCode(double *P, double *Q, int *L, int n);
double sumP(double *P, int n);
double getEntropy(double *P, int n);
double getAverageLength(double *P, int *L, int n);