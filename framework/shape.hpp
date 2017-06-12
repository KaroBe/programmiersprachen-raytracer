
//Interface for shapes

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

class Shape
{
public:
	virtual float area() const = 0;
	virtual float volume() const = 0;
};

#endif //BUW_SHAPE_HPP