
//box

#include "box.hpp"

//default constructor unit box
Box::Box(std::string const& name) :
    Shape{name, Material{"box_material", Color{0.0f,0.0f,0.0f},
                        Color{0.0f,0.0f,0.0f},
                        Color{0.0f,0.0f,0.0f},
                        0.0f}},
    m_min{glm::vec3{0.0f}},
    m_max{glm::vec3{1.0f}}
{}

//custom constructor
Box::Box(std::string const& name, Material const& material,
    glm::vec3 const& min, glm::vec3 const& max) :
    
    Shape{name, material},
    m_min{min},
    m_max{max}
{
    sortMinMax();
}

//Destructor
Box::~Box()
{
    //std::cout << "Box Destruction\n";
}

void Box::sortMinMax()
{
    if(m_min.x > m_max.x)
    {
        float buffer = m_min.x;
        m_min.x = m_max.x;
        m_max.x = buffer;
    }
    
    if(m_min.y > m_max.y)
    {
        float buffer = m_min.y;
        m_min.y = m_max.y;
        m_max.y = buffer;
    }
    
    if(m_min.z > m_max.z)
    {
        float buffer = m_min.z;
        m_min.z = m_max.z;
        m_max.z = buffer;
    }
}

//getter
glm::vec3 const& Box::get_min() const
{
    return m_min;
}

glm::vec3 const& Box::get_max() const
{
    return m_max;
}

//override area
float Box::area () const
{
    auto diff = m_max - m_min;
    return diff.x * diff.y * 2 + diff.x * diff.z * 2+ diff.y * diff.z * 2;
}

//override volume
float Box::volume () const
{
    auto diff = m_max - m_min;
    return diff.x * diff.y * diff.z;
}

//override print
std::ostream& Box::print (std::ostream& os) const
{
    os  << "\nshape type: box";
    //uses the default shape parent implementation of print on this instance
    //to print name and material
    Shape::print(os); //prints name and material
    os  <<   "min:        " << "(" << m_min.x << ", " << m_min.y << ", " << m_min.z << ")"
        << "\nmax:        " << "(" << m_max.x << ", " << m_max.y << ", " << m_max.z << ")"
        << "\n";
    return os;
}

//override intersect
Hit Box::intersect(Ray const& ray) const
{
    auto ptr = std::make_shared<Box>(*this);
    Hit hit(ptr);

    Ray nray {ray.m_origin,ray.m_direction};
    nray.m_direction = glm::normalize(ray.m_direction);

    float t0x = (m_min.x - ray.m_origin.x) / nray.m_direction.x;
    float t1x = (m_max.x - ray.m_origin.x) / nray.m_direction.x;
    float tmin = std::min(t0x, t1x);
    float tmax = std::max(t0x, t1x);

    float t0y = (m_min.y - ray.m_origin.y) / nray.m_direction.y;
    float t1y = (m_max.y - ray.m_origin.y) / nray.m_direction.y;
    tmin = std::max(tmin, std::min(t0y, t1y));
    tmax = std::min(tmax, std::max(t0y, t1y));

    float t0z = (m_min.z - ray.m_origin.z) / nray.m_direction.z;
    float t1z = (m_max.z - ray.m_origin.z) / nray.m_direction.z;
    tmin = std::max(tmin, std::min(t0z, t1z));
    tmax = std::min(tmax, std::max(t0z, t1z));

    if(tmax > std::max(tmin, 0.0f))
    {
        glm::vec3 intersect
            {ray.m_origin.x + tmin*ray.m_direction.x,
            ray.m_origin.y + tmin*ray.m_direction.y,
            ray.m_origin.z + tmin*ray.m_direction.z};

        hit.m_hit = true;
        hit.m_distance = tmin;
        hit.m_intersection = intersect;
    

        //finds the side of the box where the ray intersects and gets normale
        if((hit.m_intersection.x) == Approx(m_min.x))
        {
           hit.m_normale = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_intersection.x) == Approx(m_max.x))
        {
            hit.m_normale = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_min.y))
        {
            hit.m_normale = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_max.y))
        {
            hit.m_normale = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_min.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_max.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, 1.0f};
        }
        else
        {
            std::cout << "if klappt nicht " << std::endl;
        }

        return hit;

    }
    else
    {
        return hit;
    }
}
/*
glm::vec3 Box::get_normale(Hit const& hit) const
{
     //finds the side of the box where the ray intersects and gets normale
        if((hit.m_intersection.x) == Approx(m_min.x))
        {
           hit.m_normale = glm::vec3{-1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_intersection.x) == Approx(m_max.x))
        {
            hit.m_normale = glm::vec3{1.0f, 0.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_min.y))
        {
            hit.m_normale = glm::vec3{0.0f, -1.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_max.y))
        {
            hit.m_normale = glm::vec3{0.0f, 1.0f, 0.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_min.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, -1.0f};
        }
        else if((hit.m_intersection.y) == Approx(m_max.z))
        {
            hit.m_normale = glm::vec3{0.0f, 0.0f, 1.0f};
        }
        else
        {
            std::cout << "if klappt nicht " << std::endl;
        }
}
*/