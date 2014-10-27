#pragma once

#include <vector>

#include "gist/entry.h"

template <typename P>
class LeafEntry<P> : public Entry<P> {
private:
    void* data;
};