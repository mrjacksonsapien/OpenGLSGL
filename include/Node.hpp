#pragma once

#include "Transform.hpp"
#include "EngineFlags.hpp"

class Node {
    private:
        uint32_t dirtyFlags;
        Transform transform;

    protected:
        /* 
        transform is copied through the reference, member is not set to reference so dont worry.
        If you would've put the member as Transform&, then it would put the reference inside instead of copying.
        */
        Node(const Transform& transform);

    public:
        void setTransform(const Transform& transform);
        const uint32_t& getDirtyFlags() const; // First const means read-only return value, second const means can call this method on a const Node
        const Transform& getTransform() const;
};