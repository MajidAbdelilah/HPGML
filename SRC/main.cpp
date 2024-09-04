#include "Vector.hpp"
#include <iostream>

int main()
{
    Vector3* arr = new Vector3[4096];
	for (int i = 0; i < 4096; i++)
	{
		arr[i] = Vector3(i, i * 3, i / 3);
	}

	for (int i = 0; i < 4096; i++)
		for (int j = i+1; j < 4096; j++)
		{
			arr[i] = arr[j].Normalize();
		}
	std::cout << arr[0].x << " " << arr[0].y << " " << arr[0].z << std::endl;
    return 0;
}
 