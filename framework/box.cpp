
//box

#include "box.hpp"

//default constructor unit box
Box::Box(std::string const& name) :
	Shape{name, Material{"box_material", Color{0.0f,0.0f,0.0f},
						Color{0.0f,0.0f,0.0f},
						Color{0.0f,0.0f,0.0f},
						0.0f}},
	m_min{glm::vec3{0.0f}},
	m_max{glm::vec3{1.0f}}
{}

//custom constructor
Box::Box(std::string const& name, Material const& material,
	glm::vec3 const& min, glm::vec3 const& max) :
	
	Shape{name, material},
	m_min{min},
	m_max{max}
{}

//getter
glm::vec3 const& Box::get_min() const
{
	return m_min;
}

glm::vec3 const& Box::get_max() const
{
	return m_max;
}

//override area
float Box::area () const
{
	auto diff = m_max - m_min;
	return diff.x * diff.y * 2 + diff.x * diff.z * 2+ diff.y * diff.z * 2;
}

//override volume
float Box::volume () const
{
	auto diff = m_max - m_min;
	return diff.x * diff.y * diff.z;
}

//override print
std::ostream& Box::print (std::ostream& os) const
{
	os 	<< "\nshape type: box";
	//uses the default shape parent implementation of print on this instance
	//to print name and material
	Shape::print(os); //prints name and material
	os	<<   "min:        " << "(" << m_min.x << ", " << m_min.y << ", " << m_min.z << ")"
		<< "\nmax:        " << "(" << m_max.x << ", " << m_max.y << ", " << m_max.z << ")"
		<< "\n";
	return os;
}

//override intersect
bool Box::intersect(Ray const& ray, float& distance)
{
	bool hit = false;

	glm::vec3 shapehit{0.0f};	//coordinates of hit with shape
	glm::vec3 planehit{0.0f};	//coordiantes of hit with planes

	/* x - plane */
	if(ray.origin <= m_min.x
		||
		(ray.origin.x > m_min.x && ray.origin.x < m_max.x && ray.direction.x > 0))
	{

	}
	else if()
	{

	}

	/* y - plane */

	/* z - plane */

	return hit;
}