#pragma once

#include "Transform.hpp"
#include "EngineFlags.hpp"

class Node {
    private:
        uint32_t dirtyFlags;
        Transform transform;

    protected:
        Node(const Transform& transform);
        const bool isFlagDirty(DirtyFlags flag) const;
        void markDirty(DirtyFlags flag);
        void cleanFlag(DirtyFlags flag);

    public:
        virtual ~Node() = default;

        const Transform& getTransform() const;
        void setTransform(Transform& transform);

        // Optional implementations (only for things interacting with rendering API)
        virtual void syncDataWithRenderingAPI();
        virtual void render();
};