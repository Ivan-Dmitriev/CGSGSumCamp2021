/* FILE NAME  : t01sort.cpp
 * PROGRAMMER : ID3
 * LAST UPDATE: 18.07.2021
 * PURPOSE    : Sort arrays program.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void ReadFile( char *Filename )
{
}
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

int main(void)
{
	double* arr;
	char FileName[1000];
	int NumberOfElements;
	//string FileName;

	cout << "Input file name:";
	cin >> FileName;
	fstream f, f_to_write;

	f.open(FileName, fstream::in);
	
	//f << "303030";

	f >> NumberOfElements;

	if ((arr = (double *)malloc(sizeof(double) * NumberOfElements)) == nullptr)
		return -1;
	int i = 0;
	while (i < NumberOfElements)
	{
		f >> arr[i];
		i++;
	}
	Sort(arr, NumberOfElements);
	f_to_write.open("out.txt", fstream::out);
	i = 0;
	while (i < NumberOfElements)
	{
		f_to_write << arr[i] << endl;
		i++;
	}
	f_to_write.close();
	f.close();
}

/* END OF 't01sort.cpp' FILE */