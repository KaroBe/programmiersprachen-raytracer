
// Hit Struct

#ifndef HIT_HPP
#define HIT_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
#include <memory>

//bruachen wir diesen include?? WIE FUNKTIONIERT DAS GEGENSEITIGE INCLUDEN????
#include "shape.hpp"

class Shape;

struct Hit
{
	//default
	Hit() :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{nullptr}
	{};

	//doesn't hit shape
	Hit(std::shared_ptr<Shape> const& s) :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{s}
	{};

	Hit(bool h, float d, glm::vec3 const& i, std::shared_ptr<Shape> const& s) :
		m_hit{h},
		m_distance{d},
		m_intersection{i},
		m_shape{s}
	{};

	bool operator==(Hit const& other)
    {
        if(m_hit==other.m_hit and 
        	m_distance==other.m_distance and 
        	m_intersection==other.m_intersection and 
        	m_shape==other.m_shape)
        {
            return true;
        }
        else
        	return false;
    }
    
	bool m_hit;
	float m_distance;
	glm::vec3 m_intersection;
	std::shared_ptr<Shape> m_shape;

	friend std::ostream& operator<<(std::ostream& os, Hit const& hit)
    {
        os  << "hit: " << hit.m_hit << "\n"
            << "distance: " << hit.m_distance << "\n"
            << "intersection: " << hit.m_intersection.x << " " << hit.m_intersection.y << " " << hit.m_intersection.z << "\n"
            << "shape: " << hit.m_shape -> get_name() << "\n";
        return os;
    }
};

#endif //HIT_HPP
