
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
	bool hit = false;

	glm::vec3 boxhit{7.0f};	//coordinates of hit with shape
	glm::vec3 planehit{7.0f};	//coordiantes of hit with planes that are "seen" first by ray

	/*
	*	Choose which sides (xmin-plane or xmax plane and so on) of the box
	*	could be hit by ray, and write x/y/z Koordinates of those planes
	*	to planehit
	*/

	/* x - plane */
	// if min - plane is seen first
	if(ray.m_origin.x <= m_min.x || (ray.m_origin.x > m_min.x && ray.m_origin.x < m_max.x && ray.m_direction.x < 0))
	{
		planehit.x = m_min.x;
		std::cout << "\nhit plane x at min x = " << m_min.x;
	}
	//if max - plane is seen first
	else if(ray.m_origin.x >= m_max.x || (ray.m_origin.x > m_min.x && ray.m_origin.x < m_max.x && ray.m_direction.x > 0))
	{
		planehit.x = m_max.x;  
		std::cout << "\nhit plane x at max x = " << m_max.x;
	}

	/* y - plane */
	// if min - plane is seen first
	if(ray.m_origin.y <= m_min.y || (ray.m_origin.y > m_min.y && ray.m_origin.y < m_max.y && ray.m_direction.y < 0))
	{
		planehit.y = m_min.y;  
		std::cout << "\nhit plane y at min y = " << m_min.y;
	}
	//if max - plane is seen first
	else if(ray.m_origin.y >= m_max.y || (ray.m_origin.y > m_min.y && ray.m_origin.y < m_max.y && ray.m_direction.y > 0))
	{
		planehit.y = m_max.y; 
		std::cout << "\nhit plane y at max y = " << m_max.y;
	}

	/* z - plane */
	// if min - plane is seen first
	if(ray.m_origin.z <= m_min.z || (ray.m_origin.z > m_min.z && ray.m_origin.z < m_max.z && ray.m_direction.z < 0))
	{
		planehit.z = m_min.z; 
		std::cout << "\nhit plane z at min z = " << m_min.z;
	}
	// if max - plane is seen first
	else if(ray.m_origin.z >= m_max.z || (ray.m_origin.z > m_min.z && ray.m_origin.z < m_max.z && ray.m_direction.z > 0))
	{
		planehit.z = m_max.z;  
		std::cout << "\nhit plane z at max z = " << m_max.z;
	}

	/*
	*	Calculate hits of vector with the planes with the before calculated x, y or z
	*	coordiantes
	*	If the hit lies in the boundaries of the box, the hit with the box is found!
	*/

	float t = 0.0f;

	/* Check wheter x plane hit is hit with box */

	//calculate distance to hit with x-plane
	t = (planehit.x - ray.m_origin.x) / ray.m_direction.x;
	std::cout << "\ndistance to x plane: " << t;
	//calculate other koordinates of the hit
	boxhit.y = ray.m_origin.y + t * ray.m_direction.y;
	boxhit.z = ray.m_origin.z + t * ray.m_direction.z;
	std::cout << "\nHit : (" << planehit.x << ", "
		<< boxhit.y << ", " << boxhit.z<< ")";

	//check position of hit
	if( boxhit.x >= m_min.x && planehit.x <= m_max.x &&
		boxhit.y >= m_min.y && boxhit.y <= m_max.y &&
		boxhit.z >= m_min.z && boxhit.z <= m_max.z &&
		t >= 0 //warum überprüfen wir das nochmal??
		)
	{
		distance = t;
		hit = true;
	}

	/* Check wheter y plane hit is hit with box */
	
	//calculate distance to hit with x-plane
	t = (planehit.y - ray.m_origin.y) / ray.m_direction.y;
	std::cout << "\ndistance to y plane: " << t;
	//calculate other koordinates of the hit
	boxhit.x = ray.m_origin.x + t * ray.m_direction.x;
	boxhit.z = ray.m_origin.z + t * ray.m_direction.z;
	std::cout << "\nHit : (" << boxhit.x << ", "
		<< planehit.y << ", " << boxhit.z << ")";

	//check position of hit
	if( boxhit.x >= m_min.x && boxhit.x <= m_max.x &&
		boxhit.y >= m_min.y && planehit.y <= m_max.y &&
		boxhit.z >= m_min.z && boxhit.z <= m_max.z &&
		t >= 0 //warum überprüfen wir das nochmal??
		)
	{
		distance = t;
		hit = true;
	}		

	/* Check wheter z plane hit is hit with box */
	
	//calculate distance to hit with x-plane
	t = (planehit.z - ray.m_origin.z) / ray.m_direction.z;
	std::cout << "\ndistance to z plane: " << t;
	//calculate other koordinates of the hit
	boxhit.x = ray.m_origin.x + t * ray.m_direction.x;
	boxhit.y = ray.m_origin.y + t * ray.m_direction.y;
	
	std::cout << "\nHit : (" << boxhit.x << ", "
		<< boxhit.y << ", " << planehit.z << ")";

	std::cout << "\n" << m_min.x << "<=" << boxhit.x << "<=" << m_max.x;
	std::cout << "\n" << m_min.y << "<=" << boxhit.y << "<=" << m_max.y;
	std::cout << "\n" << m_min.z << "<=" << planehit.z << "<=" << m_max.z;


	//check position of hit
	if( boxhit.x >= m_min.x && boxhit.x <= m_max.x &&
		boxhit.y >= m_min.y && boxhit.y <= m_max.y &&
		boxhit.z >= m_min.z && planehit.z <= m_max.z &&
		t >= 0 //warum überprüfen wir das nochmal??
		)
	{
		distance = t;
		hit = true;
	}

	return hit;
}