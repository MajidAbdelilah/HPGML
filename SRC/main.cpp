#include "Vector.hpp"
#include <iostream>
#include "Quaternion.h"

int main()
{

	Quaternion q1(Vector3(0, 1, 0), 90);
	Quaternion q2(Vector3(1, 0, 0), 45);
	Quaternion q3 = q2 * q1;
	std::cout << q1.w << " " << q1.v.x << " " << q1.v.y << " " << q1.v.z << std::endl;
	std::cout << q2.w << " " << q2.v.x << " " << q2.v.y << " " << q2.v.z << std::endl;
	std::cout << q3.w << " " << q3.v.x << " " << q3.v.y << " " << q3.v.z << std::endl;
    return 0;
}
 