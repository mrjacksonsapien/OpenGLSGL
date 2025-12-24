#include "Node.hpp"

Node::Node(const Transform& transform) : dirtyFlags(DIRTY_ALL), transform(transform) {}

void Node::setTransform(const Transform& newTransform) {
    transform = newTransform;
    markDirty(DIRTY_TRANSFORM);
}

bool Node::isFlagDirty(const DirtyFlags flag) const {
    return (dirtyFlags & flag) != 0;
}

void Node::markDirty(const DirtyFlags flag) {
    dirtyFlags |= flag;
}

void Node::cleanFlag(const DirtyFlags flag) {
    dirtyFlags &= ~flag;
}

const Transform& Node::getTransform() const {
    return transform;
}

void Node::syncDataWithRenderingAPI() {}
void Node::render() {}
