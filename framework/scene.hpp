
//scene struct

#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

#include <glm/vec3.hpp>
#include <memory>
#include "material.hpp"
#include "shape.hpp"

struct Scene
{
    //Camera
    //Camera m_camera;

    //Ambient Light
    //Light m_ambient_light;

    //Lights
    //std::vector<Light> m_lights;

    //Materials
    std::vector<Material> m_materials;

    //Shapes
    std::vector<std::shared_ptr<Shape>> m_shapes;

    //Composites
    //std::vector<Composite> m_composites; 
};

#endif //BUW_SCENE_HPP