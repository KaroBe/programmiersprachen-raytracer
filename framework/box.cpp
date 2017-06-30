
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
{
	sortMinMax();
}

void Box::sortMinMax()
{
	if(m_min.x > m_max.x)
	{
		float buffer = m_min.x;
		m_max.x = buffer;
		m_min.x = m_max.x;
	}
	
	if(m_min.y > m_max.y)
	{
		float buffer = m_min.y;
		m_max.y = buffer;
		m_min.y = m_max.y;
	}
	
	if(m_min.z > m_max.z)
	{
		float buffer = m_min.z;
		m_max.z = buffer;
		m_min.z = m_max.z;
	}
}

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
	
	//do stuff
	return true;
}