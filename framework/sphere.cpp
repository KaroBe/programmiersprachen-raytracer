
//sphere

#include "sphere.hpp"
#include <math.h>

//default constructor unit sphere
Sphere::Sphere(std::string const& name) :
	Shape{name, Color{0.0f,0.0f,0.0f}},
	m_center{glm::vec3{0.0f}},
	m_radius{1}
{}

//custom constructor
Sphere::Sphere(std::string const& name, Color const& color,
	glm::vec3 const& center, float radius) :
	
	Shape{name,color},
	m_center{center},
	m_radius{radius}
{}

//getter
glm::vec3 const& Sphere::get_center() const
{
	return m_center;
}

float const& Sphere::get_radius() const
{
	return m_radius;
}

//override area
float Sphere::area () const
{
	return 4*M_PI*m_radius*m_radius;
}

//override volume
float Sphere::volume () const
{
	return (4.0f/3.0f)*M_PI*pow(m_radius,3.0f);
}