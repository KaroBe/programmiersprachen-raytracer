
// composite.cpp

#include "composite.hpp"

//Default Constructor
Composite::Composite() :
	Shape{"default_composite", {}}, //Aufruf des Elternklassen-Konstruktors
	m_content{}
{}

//User Constructor
Composite::Composite(std::string const& name) :
	Shape{name, {}},
	m_content{}
{}

//Destructor
Composite::~Composite() {}