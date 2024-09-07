#include "Vector.hpp"
#include <iostream>
#include "HPGML.h"
#include <chrono>

#define N 100000000

int main()
{
	std::vector<Vector2> scalar;
	scalar.resize(N);
	for (int i = 0; i < N; i++)
		scalar[i] = (Vector2(i, i));
	std::vector<float> result;
	result.resize(N);

	queue q(gpu_selector_v);

	Vector2* vec_device = malloc_device<Vector2>(N, q);
	float* float_result = malloc_device<float>(N, q);
	q.memcpy(vec_device, scalar.data(), N * sizeof(Vector2)).wait();
	q.parallel_for(range<1>(N), [=](id<1> it) {
		Vector2 vec = vec_device[it];
		float_result[it] = sycl::sqrt(vec.x * vec.x + vec.y * vec.y);;
		});
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	q.wait();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	q.copy(float_result, result.data(), N).wait();

	std::cout << result[5] << std::endl;

	std::cout << "Time difference = " 
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() 
		<< "[µs]" << std::endl;
	//std::cout << "Time difference = " 
		//<< std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() 
		//<< "[ns]" << std::endl;
	//for (int i = 0; i < N; i++)

	std::vector<float> scalar_result;
	scalar_result.resize(N);

	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < N; i++)
		scalar_result[i] = scalar[i].Length();
	end = std::chrono::steady_clock::now();

	std::cout << scalar_result[5] << std::endl;

	std::cout << "Time difference = "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< "[µs]" << std::endl;
	//std::cout << "Time difference = "
		//<< std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()
		//<< "[ns]" << std::endl;

	

    return 0;
}
 