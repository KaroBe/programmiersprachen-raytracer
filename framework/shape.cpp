
//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Color const& color) :
	m_name{name},
	m_color{color}
{
	std::cout << "Shape Construction\n";
}

//Destructor
Shape::~Shape()
{
	std::cout << "Shape Destruction\n";
}

//Getter
std::string Shape::get_name() const
{
	return m_name;
}

Color Shape::get_color() const
{
	return m_color;
}

std::ostream& Shape::print (std::ostream& os) const
{
	os  << "\nname:       " << m_name
		<< "\ncolor:      " << m_color;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    return s.print(os);
}
