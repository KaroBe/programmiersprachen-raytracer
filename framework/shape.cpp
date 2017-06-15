
//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Color const& color) :
	m_name{name},
	m_color{color}
{}

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
	os << "shape name: " << m_name << "\nshape color: " << m_color;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
    return s.print(os);
}
