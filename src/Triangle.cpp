#include "Triangle.hpp"

Triangle::Triangle(const Vertex& a, const Vertex& b, const Vertex& c)
    : a(a), b(b), c(c) {}

Vertex Triangle::getVertexA() const {
    return a;
}

Vertex Triangle::getVertexB() const {
    return b;
}

Vertex Triangle::getVertexC() const {
    return c;
}
