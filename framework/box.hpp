
//axis-parallel box

#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape
{
public:
	//default constructor unit box
	Box(std::string const& name);

	//custom constructor
	Box(std::string const& name, Color const& color,
		glm::vec3 const& min, glm::vec3 const& max);

	//getter - enhances the range of methods the base class has
	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;
	
	//override area
	float area () const override;

	//override volume
	float volume () const override;

	//override print
	std::ostream& print (std::ostream& os) const override;

private:
	glm::vec3	m_min;
	glm::vec3	m_max;
};

#endif //BUW_BOX_HPP
