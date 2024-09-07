#include "../HPGML.h"

HPGML_vector2::HPGML_vector2(const queue& q, const Vector2* data, const unsigned long &size)
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
float* Length(queue &q, Vector2 *device_vec, float * device_float, unsigned long size)
{
	
	return NULL;
}