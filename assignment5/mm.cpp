#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <omp.h>

using namespace std;

#define BLOCK_SIZE 64

void serial_multiply(double **A, double **B, double **C, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiply(double **A, double **B, double **C, int size)
{
    for (int bi = 0; bi < size; bi += BLOCK_SIZE) {
        for (int bk = 0; bk < size; bk += BLOCK_SIZE) {
            #pragma omp parallel for
            for (int i = bi; i <  min(size, bi + BLOCK_SIZE); i++) {
                for (int k = bk; k <  min(size, bk + BLOCK_SIZE); k++) {
                    for (int j = 0; j < size; j++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }
}

void const printMatrix(double **A, int size)
{
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            cout << setprecision(3) << setw(8) << A[i][j] << "  ";
        }
        cout << endl;
    }
}

bool const verify(double **A, double **B, int size)
{
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (abs(A[i][j] - B[i][j]) > 0.001) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    if (argc != 2) {
        cout << "Usage: mm size" << endl;
        return 1;
    }

    int size = atoi(argv[1]);

    if (size <= 0) {
        cout << "Invalid size" << endl;
        cout << "Usage: mm size" << endl;
    }

    cout << "Initalizing the matricies...";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    double *dataA = new double[size*size];
    double *dataB = new double[size*size];
    double *dataC = new double[size*size];
    double *dataV = new double[size*size];

    double **A = new double*[size];
    double **B = new double*[size];
    double **C = new double*[size];
    double **V = new double*[size];

    for (int i = 0; i < size; i++)    {
        A[i] = &dataA[size*i];
        B[i] = &dataB[size*i];
        C[i] = &dataC[size*i];
        V[i] = &dataV[size*i];
        for (int j = 0; j < size; j++) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
            C[i][j] = 0;
            V[i][j] = 0;
        }
    }

    cout << "Done." << endl;

    //  cout << "Matrix A:" << endl;
    //  printMatrix(A, size);
    //  cout << "Matrix B:" << endl;
    //  printMatrix(B, size);

    cout << "Beginning multiply..." << endl;

    auto start = std::chrono::high_resolution_clock::now();

    multiply(A, B, C, size);

    auto end = std::chrono::high_resolution_clock::now();

    cout << "Done." << endl;

    cout << "Time " << (double)(end-start).count()/1e9 << " s" << endl;

    cout << "Verifying" << endl;
    serial_multiply(A, B, V, size);

    if (!verify(V, C, size)) {
        cout << "Error! failed to verify!" << endl;
    } else {
        cout << "Answer verified!" << endl;
    }

    //  cout << "Matrix C:" << endl;
    //  printMatrix(C, size);

    delete[] A;
    delete[] B;
    delete[] C;
    delete[] V;
    delete[] dataA;
    delete[] dataB;
    delete[] dataC;
    delete[] dataV;
}
