
//Interface for shapes

#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <material.hpp>
#include <iostream>

#include "ray.hpp"

//For Intersect Methods
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>

struct Hit;

struct Hit;

class Shape
{
public:

    Shape(std::string const& name, Material const& material);

    virtual ~Shape();

    //pure virtual methods (no implementation in base class)
    virtual float area() const = 0;
    virtual float volume() const = 0;
    
    //VLL BESSER WENN NUR IN BOX UND SPHERE IMPLEMENTIERT?
    //weil so muss man auch in composite was implementieren und
    //das macht halt keinen Sinn
    virtual void translate (glm::mat4 t_mat) = 0;
    virtual void rotate (float angle) = 0;
    virtual void scale (float factor) = 0;

    //virtual methods
    virtual std::string get_name() const; 
    virtual Material get_material() const;

    virtual glm::mat4 get_world_transformation() const;
    virtual glm::mat4 get_world_transformation_inv() const;
    
    virtual void set_world_transformation(glm::mat4 t_mat);

    //fried -> should normally be outside the class, but uses Shape
    //member variables, therefore marked as friend and able to 
    //access members directly
    //the operator takes an shape object and calls the objects
    //default or custom print function
    friend std::ostream& operator<<(std::ostream& os, Shape const& s);

    virtual std::ostream& print (std::ostream& os) const;
   
    // ???? vll lösung für sdf creator programm 
    // std::ostream& print_definition (std::ostream& os) const = 0;

    //distance is overwritten with distance between origin and shape

    virtual Hit intersect(Ray const& ray) const = 0;
    
protected:
    std::string m_name;
    Material m_material;
    glm::mat4 m_world_transformation;
    glm::mat4 m_world_transformation_inv;
};

#endif //BUW_SHAPE_HPP