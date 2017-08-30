
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
        << "\nname: " << m_name
        << "\n\ncontains the following shapes:\n";

    //content enthält shape ptr
    //darin stecken box/shape/composite
        //WARUM AUCH IMMMER werden bei einem Composite in einem
        //Composite tlw Inhalte nicht angezeigt???
        //und beim printen eines Vektors von shapes, wo ja
        //

    if(m_content.size() == 0)
    {
        os << "no shapes contained";
    }
    for (std::shared_ptr<Shape> s : m_content)
    {
        os << *s;
    }
    return os;
}

//intersect
Hit Composite::intersect(Ray const& ray) const
{
    Hit closest_hit;

    //iterate all 
    for (std::shared_ptr<Shape> shape : m_content)
    {
        Hit current_hit = shape->intersect(ray);

        if (current_hit.m_hit == true && 
            current_hit.m_distance < closest_hit.m_distance)
        {
            closest_hit = current_hit;
        }
    }

    return closest_hit;
}

/*
glm::vec3 Composite::get_normal(Hit const& hit) const
{
    //print normal for every shape?
}
*/

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

std::vector<std::shared_ptr<Shape>> Composite::get_children()
{
    return m_content;
}

void Composite::translate (glm::mat4 t_mat)
{
    //do nothing? 
}

void Composite::rotate (float angle)
{
    //do nothing? 
}

void Composite::scale (float factor)
{
    //do nothing? 
}
