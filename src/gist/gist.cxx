#ifndef H_GRANDFATHER
#define H_GRANDFATHER

#include "gist/gist.h"
#include <stack>
#include <utility>

template <typename P>
Gist<P>::Gist(int u, int l) {
    max_fanout = u;
    min_fanout = l;
    global_nsn = 1;
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
	std::stack<std::pair<Entry<P> *, int>> entryStack;
	entryStack.push(std::make_pair(root, global_nsn));
	while (!entryStack.empty()) {
		Entry<P> *curEntry = entryStack.top().first;
        int curNSN = entryStack.top().second;
        entryStack.pop();

        if (curNSN < curEntry -> getNSN()) {
            // add right-link with curNSN version
        }

		std::vector<Entry<P> *> children = curEntry -> getChildren();

		if (children.empty()) {
			result.push_back(static_cast<LeafEntry<P>*> (curEntry));
			continue;
		}
		
        int curr_global_nsn = global_nsn;
		for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
			if (predicate.consistentWith((*child) -> getPredicate())) {
				entryStack.push(std::make_pair(*child, curr_global_nsn));
			}
		}
	}

	return result;
}

template <typename P>
void Gist<P>::insert(LeafEntry<P> E) {
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
void Gist<P>::deleteEntry(LeafEntry<P> const &e) {
}
#endif
