#pragma once

#include <vector>

#include "gist/entry.h"

template <typename P>
class Node {
public:
    std::vector<Entry<P> *> entries;
};