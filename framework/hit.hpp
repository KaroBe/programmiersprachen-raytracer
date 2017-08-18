
// Hit Struct

#include <glm/vec3.hpp>
#include <cmath>
#include "shape.hpp"

#ifndef HIT_HPP
#define HIT_HPP

struct Hit
{
	//default
	Hit() : 
		m_hit{false}
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{nullptr}
	{}

	//doesn't hit shape
	Hit(std::shared_ptr const& s) :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{s}
	{}

	Hit(bool h, double d, glm::vec3 const& i,
			std::shared_ptr<Shape> const& s) :
		m_hit{h},
		m_distance{d},
		m_intersection{i},
		m_shape{s}
	{}

	//add = operator overloading

	bool m_hit;
	double m_distance;
	glm::vec3 m_intersection;
	std::shared_ptr m_shape;
};

#endif HIT_HPP