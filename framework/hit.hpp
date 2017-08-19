
// Hit Struct

#ifndef HIT_HPP
#define HIT_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
#include <memory>
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

	//add = operator overloading

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
