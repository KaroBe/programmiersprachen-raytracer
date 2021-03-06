
//Composite

#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

#include "shape.hpp"
#include "hit.hpp"
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
    void print_definition (std::stringstream& s) const override;
    void print_all_definitions (std::fstream& fs) const;

    //writes distance into variable distance outside the method!
    Hit intersect(Ray const& ray) const override;
   // glm::vec3 get_normal(Hit const& hit) const;

    //unique composite methods:
    void add_shape(std::shared_ptr<Shape> const& shape);
    void remove_shape(std::shared_ptr<Shape> const& shape);

    //per referenz übergeben?
    std::vector<std::shared_ptr<Shape>> get_children();

private:
    std::vector<std::shared_ptr<Shape>> m_content;
};

#endif //BUW_COMPOSITE_HPP