#include "../HPGML.h"

HPGML_vector2::HPGML_vector2(queue& q, const Vector2* data, const unsigned long &size)
	: q(q), size(size)
{
	host_array = malloc_host<Vector2>(this->size, this->q);
	device_array = malloc_device<Vector2>(this->size, this->q);
	float_result = malloc_device<float>(this->size, this->q);

	this->q.copy(data, host_array, this->size).wait();
	this->q.copy(host_array, device_array, this->size).wait();
}

HPGML_vector2::~HPGML_vector2()
{
	free(host_array, q);
	free(device_array, q);
	free(float_result, q);
}
float *HPGML_vector2::Length(float *result)
{
    Vector2 *device_array = this->device_array;
    float *float_result = this->float_result;
    // for(unsigned int i = 0; i < 16; i++)
    const int number_jobs = 768 + 100;
    const unsigned long size = this->size;
        q.parallel_for(number_jobs, [=](item<1> it)
        {
            for(unsigned int i = it.get_id(0); i < size; i+=number_jobs)
                float_result[i] = sqrt(device_array[i].x * device_array[i].x + device_array[i].y * device_array[i].y);
       });
   	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    q.wait();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
		<< "[us]" << std::endl;
    q.copy(float_result, result, size).wait();
    return result;
}
