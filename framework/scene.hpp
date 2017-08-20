
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
#include "composite.hpp"

struct Scene
{
    //Camera
    Camera m_camera;

    //Ambient Light
    Color m_ambient_light;

    //Lights
    std::vector<std::shared_ptr<Light>> m_lights;

    //Materials
    std::map<std::string, Material> m_materials;
    
    // der hat hier eigentlich nichts mehr verloren, da das
    //sammeln der Shapes in der eingelesenen datei aufgaben-
    //bereich des sdfloaders ist
    // ggf noch ändern, in map in sdfloader, die temporär die
    // objekte hält
    //Shapes
    std::vector<std::shared_ptr<Shape>> m_shapes;

    //Composite
    std::shared_ptr<Shape> m_composite;

    //height and width
    int m_x_res;
    int m_y_res;

    //fileout
    std::string m_fileOut;
};

#endif //BUW_SCENE_HPP