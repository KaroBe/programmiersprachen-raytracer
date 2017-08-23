
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
    Scene() :
        m_camera{},
        m_ambient_light{},
        m_lights{},
        m_materials{},
        m_shapes{},
        m_composite{nullptr},
        m_x_res{0},
        m_y_res{0},
        m_fileOut{""}{}

    Scene(Camera const& camera, Color const& ambient, 
        std::vector<std::shared_ptr<Light>> const& lights, std::map<std::string, Material> const& materials,
        std::vector<std::shared_ptr<Shape>> const& shapes, std::shared_ptr<Composite> const& composite,
        unsigned int x, unsigned int y, std::string const& file) :
            m_camera{camera},
            m_ambient_light{ambient},
            m_lights{lights},
            m_materials{materials},
            m_shapes{shapes},
            m_composite{composite},
            m_x_res{x},
            m_y_res{y},
            m_fileOut{file}{}
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

    //Composite //changed dis from shape to composite!!!
    //hoffentlich nichts zerballert damit :O
    //sollte nicht, da trotzdem ein composite als shape
    //in diesem ober-composite gespeichert werden können sollte...
    std::shared_ptr<Composite> m_composite;

    //height and width
    unsigned int m_x_res;
    unsigned int m_y_res;

    //fileout
    std::string m_fileOut;
};

#endif //BUW_SCENE_HPP