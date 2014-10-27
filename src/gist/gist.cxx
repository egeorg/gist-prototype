#pragma once

#include "gist/gist.h"
#include <stack>

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
    std::vector<LeafEntry<P> *> result;
	std::stack<Entry<P> *> entryStack;
	entryStack.push_back(root);
	while (!entryStack.empty()) {
		Entry<P> *curEntry = entryStack.pop_back();
		std::vector<Entry<P> *> children = curEntry -> getChildren();

		if (children.empty()) {
			result.push_back(curEntry);	
			continue;
		}
		
		for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
			if (predicate.consistentWith(child -> predicate)) {
				entryStack.push_back(child);
			}

		}
	}

	return result;
}

template <typename P>
void Gist<P>::insert(Entry<P> const &e) {
}

template <typename P>
void Gist<P>::deleteEntry(Entry<P> const &e) {
}