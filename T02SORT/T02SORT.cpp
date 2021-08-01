/* FILE NAME  : t02sort.cpp
 * PROGRAMMER : ID3        
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Sorting arrays program.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename Type>
void Swap(Type* A, Type* B)
{
    Type tmp = *A;
    *A = *B;
    *B = tmp;
}

template<typename Type>
void Sort(Type* A, int N)
{
    int b = 0, e = N - 1;
    Type x;

    if (N < 2)
        return;
    x = A[N / 2];
    while (b <= e)
    {
        while (A[b] < x)
            b++;
        while (A[e] > x)
            e--;
        if (b <= e)
        {
            if (b != e)
                Swap(&A[b], &A[e]);
            b++;
            e--;
        }
    }
    Sort(A, e + 1);
    Sort(A + b, N - b);
}

template<typename Type>
struct my_array {
    int NumberOfElements;
    fstream f_out;
    
    Type *mas;
    my_array(void)
    {
        mas = nullptr;
        NumberOfElements = 0;
    }
    ~my_array(void)
    {
        NumberOfElements = 0;
        if (mas != nullptr)
          delete[] mas;
    }
    void sort(void)
    {
        Sort(mas, NumberOfElements);
    }
    void load(const string& FileName)
    {
        if (mas != nullptr)
            delete[] mas, mas = nullptr, NumberOfElements = 0;
        fstream f_in;

        f_in.open(FileName, fstream::in);
        f_in >> NumberOfElements;

        try
        {
            mas = new Type[NumberOfElements];
            for (int i = 0; i < NumberOfElements; i++)
              f_in >> mas[i];
        }
        catch ( bad_alloc & )
        {
            cout << "No memory\n";
        }
        f_in.close();
    }
    void save(const string& FileName)
    {
        int i = 0;
        fstream f_out;

        f_out.open("out.txt", fstream::out);
        while (i < NumberOfElements)
        {
            f_out << mas[i] << endl;
            i++;
        }
        f_out.close();
    }
    void rand_fill( int N )
    {
        int i;
        
        if (mas != nullptr)
          delete[] mas, mas = nullptr;
        mas = new double[N];
        NumberOfElements = N;
        for (i = 0; i < N; i++)
          mas[i] = (rand() - (double)RAND_MAX / 2) / 102.0;
    }
    my_array( const my_array &val ) : NumberOfElements(val.NumberOfElements), mas(new Type[NumberOfElements])
    {
      for (int i = 0; i < NumberOfElements; i++)
        mas[i] = val.mas[i];
    }
    my_array & operator=( const my_array &val )
    {
      if (mas != nullptr)
        delete[] mas;
      NumberOfElements = val.NumberOfElements;
      mas = new float[NumberOfElements];
      for (int i = 0; i < NumberOfElements; i++)
        mas[i] = val.mas[i];
      return *this;
    }
};

int main( void )
{
    char FileName[1000];
    my_array<double> mas;
    
     //cout << "Input file name:";
    //cin >> FileName;
    //mas.load(FileName);
    mas.rand_fill(10000);
    mas.sort();
    mas.save("out.txt");
    my_array<double> f1(mas);

    return 0;
}

/* END OF 't02sort.cpp' FILE */