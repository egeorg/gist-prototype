#pragma once

#include <vector>
#include "gist/entry.h"


template <typename P>
class LeafEntry : public Entry<P> {
private:
    void* data;

    std::vector<LeafEntry<P> *> find(P const &predicate) {
		if (!predicate.consistentWith(this.getPredicate())) {
			return std::vector<LeafEntry<P> *> ();
		}

		std::vector<LeafEntry<P> *> result;
		result.push_back(this);

		return result;
	}

};