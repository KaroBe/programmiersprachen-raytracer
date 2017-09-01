
//shape

#include "shape.hpp"

//Constructor
Shape::Shape (std::string const& name, Material const& material) :
    m_name{name},
    m_material{material},
    m_world_transformation{ 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0},
    m_world_transformation_inv{glm::inverse(m_world_transformation)}
{
    //std::cout << "Shape Construction\n";
}

//Destructor
Shape::~Shape()
{
    //std::cout << "Shape Destruction\n";
}

void Shape::translate(glm::vec3 vector)
{
    glm::mat4 T;
    T[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    T[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
    T[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
    T[3] = glm::vec4{vector.x, vector.y, vector.z, 1.0f};
    m_world_transformation = T * m_world_transformation;
    m_world_transformation_inv = glm::inverse(m_world_transformation);
}

void Shape::scale(glm::vec3 factor)
{
    glm::mat4 T;
    T[0] = glm::vec4{factor.x, 0.0f, 0.0f, 0.0f};
    T[1] = glm::vec4{0.0f, factor.y, 0.0f, 0.0f};
    T[2] = glm::vec4{0.0f, 0.0f, factor.z, 0.0f};
    T[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
    m_world_transformation = T * m_world_transformation;
    m_world_transformation_inv = glm::inverse(m_world_transformation);
}

void Shape::rotate(float angle, glm::vec3 vector)
{
    glm::mat4 T;
    T[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    T[1] = glm::vec4{0.0f, cos(angle), sin(angle), 0.0f};
    T[2] = glm::vec4{0.0f, -sin(angle), cos(angle), 0.0f};
    T[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
    m_world_transformation = T * m_world_transformation;
    m_world_transformation_inv = glm::inverse(m_world_transformation);
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