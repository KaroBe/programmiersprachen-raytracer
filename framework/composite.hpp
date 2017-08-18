
//Composite

#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP

#include <iostream>

#include <material.hpp>
#include <glm/vec3.hpp>

class Composite : public Shape
{
public:

	Composite();

	Composite(std::string const& name, std::vector<Shape> const& comp_content);

	virtual ~Composite();

/*
	//pure virtual methods (no implementation in base class)
	virtual float area() const = 0;
	virtual float volume() const = 0;

	//virtual methods
	virtual std::string get_name() const; 
	virtual Material get_material() const;

	//fried -> should normally be outside the class, but uses Shape
	//member variables, therefore marked as friend and able to 
	//access members directly
	//the operator takes an shape object and calls the objects
	//default or custom print function
	friend std::ostream& operator<<(std::ostream& os, Shape const& s);

	virtual std::ostream& print (std::ostream& os) const;

	//distance is overwritten with distance between origin and shape
	virtual bool intersect(Ray const& ray, float& distance) = 0;
*/	

	// PROTECTED ODER PRIVATE??
private:
	std::string m_name;
	std::vector<Shape> m_content;
};

#endif //BUW_COMPOSITE_HPP