#pragma once

#include "Node.hpp"

class Camera : Node {
    private:
        float near;
        float far;
        float fov;
};
