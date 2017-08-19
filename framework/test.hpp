//test struct

#ifndef TEST_HPP
#define TEST_HPP

#include "shape.hpp"
#include <memory>

struct Test
{
	Shape test_shape;
	std::shared_ptr<Shape> test_ptr;
};

#endif //TEST_HPP