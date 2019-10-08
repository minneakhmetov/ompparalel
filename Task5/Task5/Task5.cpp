// Task5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

int main()
{
	const int x = 6;
	const int y = 8;

	int a[x][y];

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			a[i][j] = rand();
		}
	}

	#pragma omp parallel firstprivate(a)
	{

		
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("Thread: %i \n", omp_get_thread_num());
				int sum = 0;
				int count = 0;

				for (int i = 0; i < x; i++)
				{
					for (int j = 0; j < y; j++)
					{
						sum += a[i][j];
						count++;
					}
				}
				printf("Avg: %i \n", sum/count);
			}

			#pragma omp section
			{
				printf("Thread: %i \n", omp_get_thread_num());
				int min = 9999999999999;
				int max = 0;

				for (int i = 0; i < x; i++)
				{
					for (int j = 0; j < y; j++)
					{
						if(min > a[i][j])
							min = a[i][j];

						if (max < a[i][j])
							max = a[i][j];
						
					}
				}
				printf("Min: %i \n", min);
				printf("Max: %i \n", max);
			}

			#pragma omp section
			{
				printf("Thread: %i \n", omp_get_thread_num());
				int threeCount = 0;

				for (int i = 0; i < x; i++)
				{
					for (int j = 0; j < y; j++)
					{
						if (a[i][j] % 3 == 0)
							threeCount++;
					}
				}
				printf("ThreeCount: %i \n", threeCount);
			}
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
