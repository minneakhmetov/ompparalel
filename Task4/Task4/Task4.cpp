// Task4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	int sizeA = 10;
	int sizeB = 10;

	omp_set_num_threads(2);

#pragma omp parallel firstprivate(a, b, sizeA, sizeB)
	{
		int thread = omp_get_thread_num();
		if (thread == 0) {
			int min = 99999;
			for (int i = 0; i < sizeA; i++) {
				if (a[i] < min)
					min = a[i];
			}
			printf("Min of A %i \n", min);
		}
		if (thread == 1) {
			int max = 0;
			for (int i = 0; i < sizeB; i++) {
				if (b[i] > max)
					max = b[i];
			}
			printf("Max of B %i \n", max);
		}
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
