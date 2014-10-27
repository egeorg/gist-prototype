#pragma once

#include <vector>
#include "gist/entry.h"


template <typename P>
class LeafEntry : public Entry<P> {
private:
    void* data;

    std::vector<Entry<P> *> getChildren() {
		return std::vector<Entry<P> *> ();
	}
};