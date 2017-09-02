
//ray struct

#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <math.h>

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

    friend glm::vec3 invers_dir(Ray const& ray)
    {
        glm::vec3 invers{1.0f / ray.m_direction.x,
                        1.0f / ray.m_direction.y,
                        1.0f / ray.m_direction.z};
        return invers;
    }


    //Hilfsfunktion
    // ray_t = ray_o.transform(mat)
    friend Ray transform_ray(glm::mat4 const& mat, Ray const& ray)
    {
        //origin/direction in homogene Koordinaten umwandeln
        //Punkt mit 1 ergänzen
        glm::vec3 newOrigin(mat * glm::vec4{ray.m_origin, 1.0f});
        glm::vec3 newDirection(mat * glm::vec4{ray.m_direction, 0.0f});

        Ray newRay{newOrigin, newDirection};

        //return {glm::vec3(origin_mat*mat), glm::vec3(direction_mat*mat)};
        return newRay;

    }
    
    friend glm::vec3 transform_vec(glm::mat4 const& mat, glm::vec3 const& vec)
    {
        glm::vec3 newVec(mat* glm::vec4{vec, 0.0f});
        return newVec;
    }
};
#endif