
//Composite

#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algori>

#include "shape.hpp"
#include <material.hpp>
#include <glm/vec3.hpp>

class Composite : public Shape
{
public:

    Composite();
    Composite(std::string const& name);
    ~Composite() override;

    float area() const override;
    float volume() const override;

    std::ostream& print (std::ostream& os) const override;

    //writes distance into variable distance outside the method!
    bool intersect(Ray const& ray, float& distance) override;

    //unique composite methods:
    void add_shape(std::shared_ptr<Shape> const& shape);
    void remove_shape(std::shared_ptr<Shape> const& shape);
    // get_children ??

private:
    std::string m_name;
    std::vector<std::shared_ptr<Shape>> m_content;
};

#endif //BUW_COMPOSITE_HPP