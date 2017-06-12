
//Interface for shapes

class Shape
{
	//pure virtual methods area and volume

public:
	virtual float area() const = 0;
	virtual float volume() const = 0;
};