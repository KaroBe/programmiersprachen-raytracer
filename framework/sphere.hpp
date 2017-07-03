
//sphere header

#ifndef BUW_SPHERE_HPP
#define  BUW_SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape
{
public:
	//default constructor unit sphere
	Sphere(std::string const& name);

	//custom constructor
	Sphere(std::string const& name, Material const& material,
		glm::vec3 const& center, float radius);

	//override dtor
	~Sphere();
	
	//getter - enhances the range of methods the base class has
	glm::vec3 const& get_center() const;
	float const& get_radius() const;

	//override area
	float area () const override;

	//override volume
	float volume () const override;

	//override print
	std::ostream& print (std::ostream& os) const override;

	bool intersect(Ray const& ray, float& distance) override;

private:
	glm::vec3 	m_center;
	float 		m_radius;
};

#endif //BUW_SPHERE_HPP