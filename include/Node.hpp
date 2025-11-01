#pragma once

#include "Transform.hpp"
#include "EngineFlags.hpp"

class Node {
    protected:
        uint32_t dirtyFlags = DIRTY_ALL;
        Transform transform;
};