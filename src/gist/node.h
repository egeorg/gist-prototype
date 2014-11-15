#pragma once

#include <vector>

#include "gist/entry.h"

template <typename P>
class Node {
private:
    std::vector<Entry<P> *> entries;

public:
    Node (std::vector<Entry<P> *> entries) {
        this->entries = entries;
    }
	std::vector<Entry<P> *> getEntries() {
		return entries;
	}

    void setEntries(std::vector<Entry<P> *> entries) {
        this->entries = entries;
    }

    void insert(const Entry<P> &E) {
        entries.push_back(E);
    }
};