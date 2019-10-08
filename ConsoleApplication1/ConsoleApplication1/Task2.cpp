#include <iostream>
#include <omp.h>

int main()

{
	omp_set_num_threads(3);
	int x = omp_get_num_threads();

#pragma omp parallel if (x)
	if (omp_get_num_threads() > 1)
	{
		std::cout << " Total " << omp_get_num_threads() << " Proc  " << omp_get_thread_num();

	}

	omp_set_num_threads(1);

#pragma omp parallel if (x)
	if (omp_get_num_threads() > 1)
	{
		std::cout << " Total " << omp_get_num_threads() << " Proc " << omp_get_thread_num();
	}
}

