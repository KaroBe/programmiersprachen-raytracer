
//ray struct

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	// << Output Operator
    friend std::ostream& operator<<(std::ostream& os, Ray const& ray)
    {
        os  << "\norigin: " << ray.m_origin
        	<< "\ndirection: " << ray.m_direction;
        return os;
    }
};