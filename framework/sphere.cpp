
//sphere

#include "sphere.hpp"

Sphere::Sphere() :
	m_center{glm::vec3{0,0f}},
	m_radius{1}
{}

Sphere::Sphere(glm::vec3 n_center, float n_radius) :
	m_center{n_center},
	m_radius{n_radius}
{}


