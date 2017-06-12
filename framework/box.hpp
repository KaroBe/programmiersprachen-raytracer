
//axis-parallel box

#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include <glm/vec3.hpp>

class Box : public Shape
{
public:
	//default constructor unit box
	Box();

	//custom constructor
	Box(glm::vec3 n_min, glm::vec3 n_max);

	//getter
	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;
	
	//override area
	flaot area () const override;

	//override volume
	float volume () const override;


private:
	glm::vec3	m_min;
	glm::vec3	m_max;
};

#endif //BUW_BOX_HPP
