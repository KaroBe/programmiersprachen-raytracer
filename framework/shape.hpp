
//Interface for shapes

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <color.hpp>
#include <iostream>

class Shape
{
public:

	Shape(std::string const& name, Color const& color);

	virtual float area() const = 0;
	virtual float volume() const = 0;

	virtual std::string get_name() const; 
	virtual Color get_color() const;

	friend std::ostream& operator<<(std::ostream& os, Shape const& s);

	virtual std::ostream& print (std::ostream& os) const;
	
protected:
	std::string m_name;
	Color m_color;
};

#endif //BUW_SHAPE_HPP