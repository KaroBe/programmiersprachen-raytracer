
//sphere

#include "sphere.hpp"
#include <math.h>

//default constructor unit sphere
Sphere::Sphere(std::string const& name) :
	Shape{name,
		  Material{"sphere_material", Color{0.0f,0.0f,0.0f},
				Color{0.0f,0.0f,0.0f},
				Color{0.0f,0.0f,0.0f},
				0.0f}},
	m_center{glm::vec3{0.0f}},
	m_radius{1}
{
	//std::cout << "Sphere constructor\n";
}

//custom constructor
Sphere::Sphere(std::string const& name, Material const& material,
	glm::vec3 const& center, float radius) :
	
	Shape{name,material},
	m_center{center},
	m_radius{radius}
{
	//std::cout << "Sphere constructor\n";
}

//dtor
Sphere::~Sphere()
{
	//std::cout << "Sphere Destructor\n";
}

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

//override print
std::ostream& Sphere::print (std::ostream& os) const
{
	os 	<< "\nshape type: sphere";
	//uses the default shape parent implementation of print on this instance
	//to print name and material
	Shape::print(os); //prints name and material
	os	<<   "center:     " << "(" << m_center.x << ", " << m_center.y << ", " << m_center.z << ")"
		<< "\nradius:     " << m_radius
		<< "\n";
	return os;
}
void Sphere::print_definition (std::stringstream& s) const
{
		s << "define shape sphere " << m_name << " " 
        << m_center.x << " " << m_center.y << " " << m_center.z << " "
        << m_radius << " "
        << m_material.m_name << "\n";
}

Hit Sphere::intersect(Ray const& ray_in) const
{
	float distance = INFINITY;
	auto ray = transform_ray(m_world_transformation_inv, ray_in);
	auto normal_direction = glm::normalize(ray.m_direction);
	bool x = glm::intersectRaySphere(
		ray.m_origin, normal_direction,
		m_center,
		m_radius * m_radius,
		distance);
	glm::vec3 intersection = ray_in.m_origin + normal_direction * distance;
	auto ptr = std::make_shared<Sphere>(*this);
	Hit hit(x, distance, intersection, ptr);

	//get normale
	hit.m_normale = glm::normalize(this -> get_normale(hit));

	glm::mat4 transposed = glm::transpose(m_world_transformation_inv);
	glm::vec3 transformedNormale(transposed * glm::vec4{hit.m_normale, 0.0f});
	hit.m_normale = glm::normalize(transformedNormale);
	
	return hit;
}

glm::vec3 Sphere::get_normale(Hit const& hit) const
{
	//std::cout << "\nI changed normal to : \n" << (hit.m_intersection - m_center).x << (hit.m_intersection - m_center).y 
	//<< (hit.m_intersection - m_center).z;
	return hit.m_intersection - m_center;
}