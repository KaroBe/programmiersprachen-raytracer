
//Composite

#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "shape.hpp"
#include <material.hpp>
#include <glm/vec3.hpp>

class Composite : public Shape
{
public:

	Composite();

	Composite(std::string const& name);

	~Composite() override;

private:
	std::string m_name;
	std::vector<std::shared_ptr<Shape>> m_content;
};

#endif //BUW_COMPOSITE_HPP