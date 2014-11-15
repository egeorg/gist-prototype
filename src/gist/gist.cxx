#pragma once

#include "gist/gist.h"
#include <stack>
#include <utility>
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
	entryStack.push(root);
	while (!entryStack.empty()) {
		Entry<P> *curEntry = entryStack.top();
        entryStack.pop();
		std::vector<Entry<P> *> children = curEntry -> getChildren();

		if (children.empty()) {
			result.push_back(static_cast<LeafEntry<P>*> (curEntry));
			continue;
		}
		
		for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
			if (predicate.consistentWith((*child) -> getPredicate())) {
				entryStack.push(*child);
			}
		}
	}

	return result;
}

template <typename P>
InnerEntry<P> Gist<P>::chooseSubtree(LeafEntry<P> const &E) {
    P predicate = E.getPredicate();
    Entry<P> *curEntry = root;

	while (true) {
		std::vector<Entry<P> *> children = curEntry->getChildren();
		Entry<P> *bestChild = *children.begin();

		if (bestChild->getChildren().empty()) {
			return *static_cast<InnerEntry<P>*>(curEntry);
		}

		double bestPenalty = predicate.penalty(bestChild->getPredicate());
		for (typename std::vector<Entry<P> *>::iterator child = children.begin() + 1; child != children.end(); ++child) {
			double curPenalty = predicate.penalty(static_cast<InnerEntry<P>*>(*child)->getPredicate());
			if (curPenalty < bestPenalty) {
				bestPenalty = curPenalty;
				bestChild = *child;
			}
		}
		curEntry = bestChild;
	}
}

template <typename P>
void Gist<P>::split(InnerEntry<P> &L, Entry<P> const &E) {
    std::pair<std::vector<P &>, std::vector<P &> > sets = E.getPredicate().pickSplit(L.getSubpredicates());
    L.setChildren(sets.first);
    InnerEntry <P> N = *(new InnerEntry<P> (sets.second));

    InnerEntry<P> *R = L.getParent();
    if (R->getChildren().size() < max_fanout) {
        R->insert(N);
        return;
    }
}

template <typename P>
void Gist<P>::adjustKeys(InnerEntry<P> &L) {
	for (InnerEntry<P> curEntry = L; curEntry.getParent() != nullptr; curEntry = *(curEntry.getParent())) {
		curEntry.setPredicate(*(new P(curEntry.getSubpredicates())));
	}
}

template <typename P>
void Gist<P>::insert(const LeafEntry<P> &E) {
	InnerEntry<P> L = chooseSubtree(E);

	if (L.getChildren().size() < max_fanout) {
		L.insert(E);
		return;
	}

	split(L, E);
	adjustKeys(L);
}

template <typename P>
void Gist<P>::deleteEntry(Entry<P> const &e) {
}