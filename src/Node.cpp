#include "Node.hpp"

Node::Node(const Transform& transform) : dirtyFlags(DIRTY_ALL), transform(transform) {}

void Node::setTransform(const Transform& t) {
    transform = t;
    dirtyFlags |= DIRTY_TRANSFORM;
}

const uint32_t& Node::getDirtyFlags() const {
    return dirtyFlags;
}

const Transform& Node::getTransform() const {
    return transform;
}