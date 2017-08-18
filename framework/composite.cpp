
// composite.cpp

#include "composite.hpp"

//Default Constructor
Composite::Composite() :
    Shape{"default_composite", {}}, //Aufruf des Elternklassen-Konstruktors
    //Shape{"name", Material{}} -> ruft wiederum Material-Standardkonstruktor auf
    m_content{}
{}

//User Constructor
Composite::Composite(std::string const& name) :
    Shape{name, {}},
    m_content{}
{}

//Destructor
Composite::~Composite() {}

//area
float Composite::area() const
{
    std::cout << "This is a composite, call area() method of contained shapes please.";
    return 0.0f;
}

//volume
float Composite::volume() const
{
    std::cout << "This is a composite, call volume() method of contained shapes please.";
    return 0.0f;
}

//print
std::ostream& Composite::print (std::ostream& os) const
{
    os  << "\nshape type: composite"
        << "\nname:       " << m_name
        << "\nshapes contained:";

    //wichtig: muss auto sein, weil Typ Shape abstrakt
    // CONST ????
    for (auto s : m_content)
    {
        s->print(os);
    }
    return os;
}

//intersect
bool Composite::intersect(Ray const& ray, float& distance)
{
    float closest_dis = 0;
    std::shared_ptr<Shape> closest_shape;
    bool hit = false;

    for (auto shape : m_content)
    {
        float temp_dis;
        if (shape->intersect(ray, temp_dis) && temp_dis < closest_dis)
        {
            closest_dis = temp_dis;
            closest_shape = shape;
        }
    }   
}

//add shape
void Composite::add_shape(std::shared_ptr<Shape> const& shape)
{
    m_content.push_back(shape);
}

//remove shape
void Composite::remove_shape(std::shared_ptr<Shape> const& shape)
{
    //note: erase-remove idiom
    m_content.erase(std::remove(m_content.begin(), m_content.end(), shape), m_content.end());
}
