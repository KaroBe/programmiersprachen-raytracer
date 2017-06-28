
//Interface for shapes

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <color.hpp>
#include <iostream>

#include "ray.hpp"


//For Intersect Methods
# include <glm/glm.hpp>
# include <glm/gtx/intersect.hpp>

class Shape
{
public:

	Shape(std::string const& name, Color const& color);

	virtual ~Shape();

	//pure virtual methods (no implementation in base class)
	virtual float area() const = 0;
	virtual float volume() const = 0;

	//virtual methods
	virtual std::string get_name() const; 
	virtual Color get_color() const;

	//fried -> should normally be outside the class, but uses Shape
	//member variables, therefore marked as friend and able to 
	//access members directly
	//the operator takes an shape object and calls the objects
	//default or custom print function
	friend std::ostream& operator<<(std::ostream& os, Shape const& s);

	virtual std::ostream& print (std::ostream& os) const;
	
protected:
	std::string m_name;
	Color m_color;
};

#endif //BUW_SHAPE_HPP