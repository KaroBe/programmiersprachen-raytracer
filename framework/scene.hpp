
//scene struct

#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <glm/vec3.hpp>
#include <memory>
#include <map>
#include "material.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "shape.hpp"

struct Scene
{
    //Camera
    //Camera m_camera;

    //Ambient Light
    Color m_ambient_light;

    //Lights
    //std::vector<Light> m_lights;

    //Materials
    std::map<std::string, Material> m_materials;

    //Shapes
    std::vector<std::shared_ptr<Shape>> m_shapes;

    //Composites
    //std::vector<Composite> m_composites;
};

#endif //BUW_SCENE_HPP