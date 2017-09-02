
// Hit Struct

#ifndef HIT_HPP
#define HIT_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
#include <memory>

//bruachen wir diesen include?? WIE FUNKTIONIERT DAS GEGENSEITIGE INCLUDEN????
//#include "shape.hpp"

class Shape;

struct Hit
{
	//default
	Hit() :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{nullptr},
		m_normale{glm::vec3{INFINITY}}
	{};

	//doesn't hit shape
	Hit(std::shared_ptr<Shape> const& s) :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{s},
		m_normale{glm::vec3{INFINITY}}
	{};

	Hit(bool h, float d, glm::vec3 const& i, std::shared_ptr<Shape> const& s) :
		m_hit{h},
		m_distance{d},
		m_intersection{i},
		m_shape{s},
		m_normale{glm::vec3{INFINITY}}
	{};

	// ggf mit swap / move dings ersetzen für mehr perfomanz ?
	Hit& operator=(Hit const& temp_hit)
	{
		if(this != &temp_hit)
		{
			m_hit = temp_hit.m_hit;
			m_distance = temp_hit.m_distance;
			m_intersection = temp_hit.m_intersection;
			m_shape = temp_hit.m_shape;
			m_normale = temp_hit.m_normale;
		}
		return *this;
	}

	bool operator==(Hit const& other)
    {
        if(m_hit==other.m_hit and 
        	m_distance==other.m_distance and 
        	m_intersection==other.m_intersection and 
        	m_shape==other.m_shape and
        	m_normale==other.m_normale)
        {
            return true;
        }
        else
        	return false;
    };

	friend std::ostream& operator<<(std::ostream& os, Hit const& hit)
    {
        os  << "hit: " << hit.m_hit << "\n"
            << "distance: " << hit.m_distance << "\n"
            << "intersection: " << hit.m_intersection.x << " " << hit.m_intersection.y << " " << hit.m_intersection.z << "\n"
            << "normale: " << hit.m_normale.x << " " << hit.m_normale.y << " " << hit.m_normale.z << "\n"; 
        if (hit.m_shape == nullptr)
        {
        	os << "nullptr";
        }
        else
        {
            os << "shape: " << hit.m_shape -> get_name() << "\n";
        }
        return os;
	}

	bool m_hit;
	float m_distance;
	glm::vec3 m_intersection;
	std::shared_ptr<Shape> m_shape;
	glm::vec3 m_normale;
};

#endif //HIT_HPP
