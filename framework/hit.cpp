
#include "hit.hpp"

//default
	Hit::Hit() :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{nullptr}
	{};

	//doesn't hit shape
	Hit::Hit(std::shared_ptr<Shape> const& s) :
		m_hit{false},
		m_distance{INFINITY},
		m_intersection{glm::vec3{INFINITY}},
		m_shape{s}
	{};

	Hit::Hit(bool h, float d, glm::vec3 const& i, std::shared_ptr<Shape> const& s) :
		m_hit{h},
		m_distance{d},
		m_intersection{i},
		m_shape{s}
	{};

	// ggf mit swap / move dings ersetzen für mehr perfomanz ?
	Hit& Hit::operator=(Hit const& temp_hit)
	{
		if(this != &temp_hit)
		{
			m_hit = temp_hit.m_hit;
			m_distance = temp_hit.m_distance;
			m_intersection = temp_hit.m_intersection;
			m_shape = temp_hit.m_shape;
		}
		return *this;
	};

	bool Hit::operator==(Hit const& other)
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
    };