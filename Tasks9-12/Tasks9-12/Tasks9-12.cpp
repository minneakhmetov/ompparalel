#include <iostream>
#include <omp.h>
#include <thread>
#include <chrono>

void task9() {
	const static int sizeA = 6;
	const static int sizeB = 8;
	int ab[sizeA][sizeB];

	int min = 99999999;

	int max = 0;

	for (int i = 0; i < sizeA; i++) {
		for (int j = 0; j < sizeB; j++) {
			ab[i][j] = i + (rand() % 5);
			printf("%d \n", ab[i][j]);
		}
	}

	omp_set_num_threads(4);

#pragma omp parallel for shared(min, max)
	for (int i = 0; i < sizeA; i++) {
		for (int j = 0; j < sizeB; j++) {
			#pragma omp critical 
			{
				if (ab[i][j] < min)
					min = ab[i][j];
				if (ab[i][j] > max) 
					max = ab[i][j];
			}
			printf("Thread %d \n", omp_get_thread_num());
		}
	}

	printf("result MIN %d \n", min);

	printf("result MAX %d \n", max);


}

void task10() {

	const static int size = 30;
	int a[size];

	int count = 0;

	for (int i = 0; i < size; i++) {
		a[i] = i + (rand() % 5);
		printf("%d \n", a[i]);
	}

#pragma omp parallel for shared(count)
	for (int i = 0; i < size; i++) 
	{
		if (a[i] % 9 == 0)
		{
			#pragma omp atomic 
				count++;
		}
		printf("Thread %d \n", omp_get_thread_num());
	}

	printf("Result %d \n", count);

}

void task11() {

	const static int size = 30;
	int a[size];

	int max = 0;

	for (int i = 0; i < size; i++) {
		a[i] = i + (rand() % 10);
		printf("%d \n", a[i]);
	}

#pragma omp parallel for shared(max)
	for (int i = 0; i < size; i++)
	{
		if (a[i] % 7 == 0 && a[i] > max)
		{
			#pragma omp critical 
			max = a[i];
		}
		printf("Thread %d \n", omp_get_thread_num());
	}

	printf("Result %d \n", max);
}

void task12() {

	int thread_num = 8;
	omp_set_num_threads(thread_num);

	
	
	omp_set_num_threads(thread_num);

	printf("----------------FIRST-SOLUTION---------------\n");
	//первый способ
	for (int i = thread_num - 1; i >= 0; i--)
	#pragma omp parallel
		if (i == omp_get_thread_num())
			printf("Hello world from %d thread of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);


	printf("----------------SECOND-SOLUTION---------------\n");
	//второй способ
	int count = thread_num - 1;
#pragma omp parallel shared(count)
	while (true)
	{
		if (count == omp_get_thread_num()) {
			printf("Hello world from %d thread of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);
			count--;
		}
		if (count < 0)
			break;
	}


	omp_set_dynamic(0);
	printf("----------------THIRD-SOLUTION---------------\n");

	#pragma omp parallel
	{
		std::this_thread::sleep_for(std::chrono::seconds(thread_num - omp_get_thread_num()));
		printf("Hello world from %d thread of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);

	}
	
	

}

int main()
{
	printf("----------------TASK-9----------------\n");
	task9();
	printf("----------------TASK-10----------------\n");
	task10();
	printf("----------------TASK-11----------------\n");
	task11(); 
	printf("----------------TASK-12----------------\n");
	task12();


}



