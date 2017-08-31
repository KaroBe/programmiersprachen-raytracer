
//axis-parallel box

#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include "hit.hpp"
#include <glm/vec3.hpp>
#include <catch.hpp>

class Box : public Shape
{
public:
    //default constructor unit box
    Box(std::string const& name);

    //custom constructor
    Box(std::string const& name, Material const& material,
        glm::vec3 const& min, glm::vec3 const& max);

    //dtor
    ~Box();

    void sortMinMax();

    //getter - enhances the range of methods the base class has
    glm::vec3 const& get_min() const;
    glm::vec3 const& get_max() const;
    
    //override area
    float area () const override;

    //override volume
    float volume () const override;

    virtual void translate (glm::mat4 t_mat) override;
    virtual void rotate (float angle) override;
    virtual void scale (float factor) override;

    //override print
    std::ostream& print (std::ostream& os) const override;
    void print_definition (std::stringstream& s) const override;

    Hit intersect(Ray const& ray) const override;
   // glm::vec3 get_normale(Hit const& hit) const;

private:
    glm::vec3   m_min;
    glm::vec3   m_max;
};

#endif //BUW_BOX_HPP
