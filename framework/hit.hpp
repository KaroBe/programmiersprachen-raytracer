
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
	Hit();

	//doesn't hit shape
	Hit(std::shared_ptr<Shape> const& s);

	Hit(bool h, float d, glm::vec3 const& i, std::shared_ptr<Shape> const& s);

	// ggf mit swap / move dings ersetzen für mehr perfomanz ?
	Hit& operator=(Hit const& temp_hit);

	bool operator==(Hit const& other);

	//Attribute
	bool m_hit;
	float m_distance;
	glm::vec3 m_intersection;
	std::shared_ptr<Shape> m_shape;
};

#endif //HIT_HPP
