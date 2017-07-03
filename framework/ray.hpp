
//ray struct

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	// << Output Operator
    friend std::ostream& operator<<(std::ostream& os, Ray const& ray)
    {
        os  << "\norigin: " << ray.m_origin.x << ", "
        	<< ray.m_origin.y <<", "
        	<< ray.m_origin.z
        	<< "\ndirection: " << ray.m_direction.x << ", "
        	<< ray.m_direction.y <<", "
        	<< ray.m_direction.z;
        return os;
    }
};

#endif