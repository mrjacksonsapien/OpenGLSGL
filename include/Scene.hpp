#pragma once

#include <vector>
#include "Mesh.hpp"
#include "Camera.hpp"

class Scene {
    private:
        std::vector<Mesh> meshes;
        Camera currentCamera;
};