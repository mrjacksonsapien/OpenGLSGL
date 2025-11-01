#include "Node.hpp"

Node::Node(const Transform& transform) : dirtyFlags(DIRTY_ALL), transform(transform) {}

void Node::setTransform(Transform& t) {
    transform = t;
    markDirty(DIRTY_TRANSFORM);
}

const bool Node::isFlagDirty(DirtyFlags flag) const {
    return (dirtyFlags & flag) != 0;
}

void Node::markDirty(DirtyFlags flag) {
    dirtyFlags |= flag;
}

void Node::cleanFlag(DirtyFlags flag) {
    dirtyFlags &= ~flag;
}

const Transform& Node::getTransform() const {
    return transform;
}

void Node::syncDataWithRenderingAPI() {}
void Node::render() {}