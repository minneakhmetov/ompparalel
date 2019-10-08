// Task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

int main()
{
	int a = 0;
	int b = 0;

	omp_set_num_threads(2);

	printf("Before: A : %i, B: %i \n", a, b);

	#pragma omp parallel private(a) firstprivate(b)
		{
		a = 0; b = 0;
			int i = omp_get_thread_num();
			a += i; b += i;
			printf("A : %i, B: %i \n", a, b);
		}	

	printf("After: A : %i, B: %i \n", a, b);

	omp_set_num_threads(4);

	printf("Before: A : %i, B: %i \n", a, b);

	#pragma omp parallel shared(a) private(b)
		{
			b = 0;
			int i = omp_get_thread_num();
			a -= i; b -= i;
			printf("A : %i, B: %i \n", a, b);
		}

	printf("After: A : %i, B: %i \n", a, b);
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
