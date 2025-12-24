#pragma once

#include "Vertex.hpp"

class Triangle {
public:
    Triangle(const Vertex& a, const Vertex& b, const Vertex& c);

    Vertex getVertexA() const;
    Vertex getVertexB() const;
    Vertex getVertexC() const;

private:
    Vertex a;
    Vertex b;
    Vertex c;
};
