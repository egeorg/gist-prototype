#pragma once

#include <vector>

#include "gist/entry.h"

template <typename P>
class Node {
private:
    std::vector<Entry<P> *> entries;

public:
	std::vector<Entry<P> *> getEntries() {
		return entries;
	}
};