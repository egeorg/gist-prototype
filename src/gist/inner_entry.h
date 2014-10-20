#pragma once

#include "gist/entry.h"
#include "gist/node.h"

template <typename P>
class InnerEntry<P> : public Entry<P> {
private:
    Node<P> *node;
};