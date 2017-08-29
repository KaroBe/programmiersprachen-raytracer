
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

    friend glm::vec3 invers_dir(Ray const& ray)
    {
        glm::vec3 invers{1.0f / ray.m_direction.x,
                        1.0f / ray.m_direction.y,
                        1.0f / ray.m_direction.z};
        return invers;
    }
};

//Hilfsfunktion
// ray_t = ray_o.transform(mat)
Ray transform_ray (glm::mat4 const& mat, Ray const& ray)
{
    //origin/direction in homogene Koordinaten umwandeln
    //Punkt mit 1 ergänzen
    glm::vec4 origin_mat {ray.m_origin, 1.0f};
    //Vector mit 0 ergänzen
    glm::vec4 direction_mat {ray.m_direction, 0.0f};

    //mit transformationsmatrix multiplizieren und bei Rück
    //gabe zurückumwandeln in vec3 s
    return {glm::vec3(origin_mat*mat), glm::vec3(direction_mat*mat)};
}

#endif