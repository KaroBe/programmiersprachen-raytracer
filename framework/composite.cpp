
// composite.cpp

#include "composite.hpp"

//Default Constructor
Composite::Composite() :
	m_name{"default_composite"},
	m_content{std::vector<Shape>}
{
	std::cout << "Empty Composite constructed\n";
}

//User Constructor
Composite::Composite(std::string const& name, std::vector<Shape> const& comp_content) :
	m_name{name},
	m_content{comp_content}
{
	std::cout << "Composite Construction done\n";
}

//Destructor
Composite::~Composite()
{
	std::cout << "Composite Destruction done\n";
}