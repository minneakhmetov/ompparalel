// Tasks-6-8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <ostream>
#include <chrono>
// ...




class Task6
{
	

	const static int sizeA = 10;
	const static int sizeB = 10;
	
	int a[sizeA];
	int b[sizeB];

	private:
		void initialize_array(int a[], int increment, int arrayLength)
		{
			for (int i = 0; i < arrayLength; i++)
				a[i] = i + increment;
		}

	public:
		void execute()
		{
			int sumA = 0;
			int sumB = 0;

			initialize_array(a, 0, sizeA);
			initialize_array(b, 10, sizeB);

			#pragma omp parallel for \
						reduction(+:sumA)
				for (int i = 0; i < sizeA; i++)
					sumA += a[i];

			#pragma omp parallel for \
						reduction(+:sumB)
				for (int i = 0; i < sizeB; i++)
					sumB += b[i];
		
			
			sumA = sumA / sizeA;

			sumB = sumB / sizeB;

			if (sumA > sumB)
				printf("Avg A: %d, Avg B: %d, A > B \n", sumA, sumB);
			else if (sumA < sumB)
				printf("Avg A: %d, Avg B: %d, A < B \n", sumA, sumB);
			else
				printf("Avg A: %d, Avg B: %d, A = B \n", sumA, sumB);

		}
};

class Task7 
{

	const static int size = 12;
	

	int a[size];
	int b[size];
	int c[size];

	private:

		void print_array(int a[], int arrayLength)
		{
			printf("Array : ");

			for (int i = 0; i < arrayLength; i++) {
				printf("Thread num: %d, Number %d; ", omp_get_thread_num(), a[i]);
			}
			printf("\n");
		}

	public:
		void execute() 
		{
			

			printf("Number of threads: %d \n", omp_get_num_threads());

			#pragma omp parallel firstprivate(size)
			{
				for (int i = 0; i < size; i++) {
					a[i] = i + (rand() % 5);
					b[i] = i + (rand() % 5);
					printf("thread %d, A %d, B %d; \n", omp_get_thread_num(), a[i], b[i]);
				}
			}

			printf("----------------\n");

			omp_set_num_threads(4);

			#pragma omp parallel firstprivate(size)
			{
				for (int i = 0; i < size; i++) {
					c[i] = a[i] + b[i];
					printf("thread %d, number %d; \n", omp_get_thread_num(), c[i]);
				}
			}

		}
};


class Task8
{
	const static int size = 12;

	int ab[size][size];
	int c[size];
	int res1[size];
	int res2[size];


	public:
		

		void execute() 
		{
			for (int i = 0; i < size; i++) {
				for(int j = 0; j < size; j++)
					ab[i][j] = i + (rand() % 5);
				c[i] = i + (rand() % 5);
			}

			auto start = chrono::system_clock::now();


			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					res1[i] += ab[i][j] * c[j];
				}
			}
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed_seconds = end - start;

			printf("One core %.8f\n", elapsed_seconds.count());

			auto start1 = std::chrono::system_clock::now();

			#pragma omp parallel firstprivate(size)
			{
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						res2[i] += ab[i][j] * c[j];
					}
				}
			}

			auto end1 = std::chrono::system_clock::now();

			std::chrono::duration<double> elapsed_seconds1 = end1 - start1;

			printf("Not one core - %.8f\n", elapsed_seconds1.count());


		}


};


int main()
{
	printf("----------------TASK-6----------------\n");
	Task6 task6;
	task6.execute();

	printf("----------------TASK-7----------------\n");
	Task7 task7;
	task7.execute();

	printf("----------------TASK-8----------------\n");
	Task8 task8;
	task8.execute();





}






