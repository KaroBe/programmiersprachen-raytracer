
//box

#include "box.hpp"

//default constructor unit box
Box::Box() :
	m_min{glw::vec3{0.0f}},
	m_max{lgw::vec3{1.0f}}
{}

//custom constructor
Box::Box(glm::vec3 n_min, glm::vec3 n_max) :
	m_min(n_min),
	m_max(n_max)
{}

