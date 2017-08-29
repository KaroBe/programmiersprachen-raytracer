
//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Material const& material) :
    m_name{name},
    m_material{material}
{
    //std::cout << "Shape Construction\n";
}

//Destructor
Shape::~Shape()
{
    //std::cout << "Shape Destruction\n";
}

//Getter
std::string Shape::get_name() const
{
    return m_name;
}

Material Shape::get_material() const
{
    return m_material;
}

glm::mat4 Shape::get_world_transformation () const
{
    return m_world_transformation;
}

glm::mat4 Shape::get_world_transformation_inv() const
{
    return m_world_transformation_inv;
}

void Shape::set_world_transformation (glm::mat4 t_mat)
{
    m_world_transformation = t_mat;
    m_world_transformation_inv = glm::inverse(m_world_transformation);
}

std::ostream& Shape::print (std::ostream& os) const
{
    os  << "\nname:       " << m_name
        << "\nmaterial:      " << m_material;
    return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
        return s.print(os);
}
