#pragma once

#include "gist/gist.h"

template <typename P>
Gist<P>::Gist(int u, int l) {
    max_fanout = u;
    min_fanout = l;
    root = new InnerEntry<P>();
}

template <typename P>
Gist<P>::~Gist() {
	if (root != nullptr) {
		// TODO
		delete root;
	}
}

template <typename P>
std::vector<LeafEntry<P> *> Gist<P>::search(const P &predicate) const {
    return this.root.find(predicate);
}

template <typename P>
void Gist<P>::insert(Entry<P> const &e) {
}

template <typename P>
void Gist<P>::deleteEntry(Entry<P> const &e) {
}