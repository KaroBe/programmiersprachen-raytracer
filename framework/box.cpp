
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
		m_min.x = m_max.x;
		m_max.x = buffer;
	}
	
	if(m_min.y > m_max.y)
	{
		float buffer = m_min.y;
		m_min.y = m_max.y;
		m_max.y = buffer;
	}
	
	if(m_min.z > m_max.z)
	{
		float buffer = m_min.z;
		m_min.z = m_max.z;
		m_max.z = buffer;
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
	//normalize ray
	Ray nray {ray.m_origin,ray.m_direction};
	nray.m_direction = glm::normalize(ray.m_direction);

	std::cout << ray << nray;;

	bool hit = false;

	//Parallelität zu Achsen

	//Alle Schnittpunkte mit Flächen durch Seiten der Box

/* NOTE: statt direction 1/direction verwenden, da sonst bei ray direction = 0
	ein Fehler auftritt?!
	http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection */

	float t0x = (m_min.x - nray.m_origin.x) / nray.m_direction.x;
	float t1x = (m_max.x - nray.m_origin.x) / nray.m_direction.x;

	float t0y = (m_min.y - nray.m_origin.y) / nray.m_direction.y;
	float t1y = (m_max.y - nray.m_origin.y) / nray.m_direction.y;

	float t0z = (m_min.z - nray.m_origin.z) / nray.m_direction.z;
	float t1z = (m_max.z - nray.m_origin.z) / nray.m_direction.z;

	//far und near Schnittpunkte mit Flächen durch Seiten der Box
	float tx_far = std::max(t0x,t1x);
	float tx_near = std::min(t0x,t1x);

	float ty_far = std::max(t0y,t1y);
	float ty_near = std::min(t0y,t1y);

	float tz_far = std::max(t0z,t1z);
	float tz_near = std::min(t0z,t1z);

	//Schnittpunkte mit Ebenen, die auf der Box liegen
	float tfar = std::min(tx_far, ty_far);
	float tnear = std::max(tx_near, ty_near);

	//Wenn der Schnittpunkt mit der weiter entfernten Seite kleiner ist,
	//wird Box nicht von ray getroffen
	if(tfar < tnear)
	{
		return false;
	}

	//Betrachtung in 3D
	tfar = std::min(tfar, tz_far);
	tnear = std::max(tnear, tz_near);

	if(tfar < tnear)
	{
		return false;
	}

	distance = tnear;

	return true;
}