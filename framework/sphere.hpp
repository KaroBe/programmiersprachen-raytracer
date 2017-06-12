
//sphere header

#ifndef BUW_SPHERE_HPP
#define  BUW_SPHERE_HPP

#include <glm/vec3.hpp>

class Sphere : public Shape
{
public:
	//default constructor unit sphere
	Sphere(glm::vec3 n_center, float n_radius);

	//custom constructor
	Sphere();

	//getter
	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;

	//override area
	flaot area () const override;

	//override volume
	float volume () const override;

private:
	glm::vec3 	m_center;
	float 		m_radius;
};

#endif //BUW_SPHERE_HPP