#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "scene.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"

struct SDFloader
{

    Scene load(std::string const& inputFile);

};

#endif