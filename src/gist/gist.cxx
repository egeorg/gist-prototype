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
		//TODO
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
void Gist<P>::insert(Entry<P> E) {
    P predicate = E.getPredicate();
    std::stack<InnerEntry<P>*> path;

    for (InnerEntry<P> *curEntry = root;;) {
        path.push(curEntry);
        std::vector<Entry<P> *> children = curEntry->getChildren();
        Entry<P> *bestChild = *children.begin();

        if (bestChild->getChildren().empty()) {
            break;
        }

        double bestPenalty = predicate.penalty(bestChild->getPredicate());
        for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
            double curPenalty = predicate.penalty(static_cast<InnerEntry<P>*>(*child)->getPredicate());
            if (curPenalty < bestPenalty) {
                bestPenalty = curPenalty;
                bestChild = *child;
            }
        }
        curEntry = static_cast<InnerEntry<P>*>(bestChild);
    }

    for (InnerEntry<P> *L = path.top();; L = path.top()) {
        if (L->getChildren().size() < max_fanout) {
            L->insert(E);
            break;
        }
        path.pop();
        std::pair<std::vector<P &>, std::vector<P &> > sets = E.getPredicate().pickSplit(L->getSubpredicates());
        L->setChildren(sets.first);
        L->setPredicate(*(new P(L->getSubpredicates())));
        E = *(new InnerEntry<P> (sets.second));
    }

    for (InnerEntry<P>* curEntry = path.top(); !path.empty(); curEntry = path.top()) {
        curEntry->setPredicate(*(new P(curEntry->getSubpredicates())));
        path.pop();
    }
}

template <typename P>
void Gist<P>::deleteEntry(Entry<P> const &e) {
}