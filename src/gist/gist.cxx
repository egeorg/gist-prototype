#ifndef H_GRANDFATHER
#define H_GRANDFATHER

#include "gist/gist.h"
#include <iostream>

template <typename P>
Gist<P>::Gist(int u, int l) {
    max_fanout = u;
    min_fanout = l;
    global_nsn = 1;
    root = new InnerEntry<P>(global_nsn);
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
        std::lock_guard<std::recursive_mutex> lock(*curEntry->getMutex());

        int curNSN = entryStack.top().second;
        entryStack.pop();

        if (curNSN < curEntry->getNSN()) {
            if (curEntry->getRightEntry() != nullptr) {
                entryStack.push(std::make_pair(curEntry->getRightEntry(), curNSN));
            }
        }

        std::vector<Entry<P> *> children = curEntry->getChildren();

        if (children.empty()) {
            result.push_back(static_cast<LeafEntry<P> *> (curEntry));
            continue;
        }

        int curr_global_nsn = global_nsn;
        for (auto child : children) {
            if (predicate.consistentWith(*(child->getPredicate()))) {
                entryStack.push(std::make_pair(child, curr_global_nsn));
            }
        }
    }

    return result;
}

template <typename P>
void Gist<P>::chooseSubtree(const P &predicate, std::stack<std::pair<InnerEntry<P>*, int>> *path) {
    int curr_nsn = global_nsn;
    InnerEntry<P> *curEntry = root;
    int curr_global_nsn = global_nsn;
    while (true) {
        path->push(std::make_pair(curEntry, curr_nsn));
        std::lock_guard<std::recursive_mutex> lockCurEntry(*curEntry->getMutex());

        std::vector<Entry<P> *> children = curEntry->getChildren();
        if (children.size() == 0) {
            break;
        }

        Entry<P> *bestChild = *children.begin();

        if (bestChild->getChildren().empty()) {
            break;
        }

        if (curr_global_nsn < curEntry->getNSN()) {
            // p = node with smallest insert penalty in rightlink chain delimited by p-NSN;
        }

        double bestPenalty = predicate.penalty(*(bestChild->getPredicate()));
        for (auto child : children) {
            std::lock_guard<std::recursive_mutex> lockChild(*child->getMutex());

            double curPenalty = predicate.penalty(*(child->getPredicate()));
            if (curPenalty < bestPenalty) {
                bestPenalty = curPenalty;
                bestChild = child;
            }
        }
        curEntry = static_cast<InnerEntry<P>*>(bestChild);
        curr_nsn = curEntry->getNSN();
        curr_global_nsn = global_nsn;
    }
}

template <typename P>
std::vector<Entry<P>*> Gist<P>::covariant_cast(const std::vector<PredicateHolder<P>*> &p) {
    std::vector<Entry<P>*> result;
    for (auto holder : p) {
        result.push_back(static_cast<Entry<P> *>(holder));
    }

    return result;
}

template <typename P>
void Gist<P>::insert(LeafEntry<P> E) {
    Entry<P> *S = static_cast<Entry<P>*>(&E);
    P predicate = *(S->getPredicate());
    std::stack<std::pair<InnerEntry<P>*, int>> path;

    chooseSubtree(predicate, &path);

    while (!path.empty()) {
        InnerEntry<P> *L = path.top().first;
        std::lock_guard<std::recursive_mutex> lockL(*L->getMutex());

        if (L->getChildren().size() < max_fanout) {
            L->insert(S);
            break;
        }
        path.pop();
        std::pair<std::vector<PredicateHolder<P>*>, std::vector<PredicateHolder<P>*>> sets = S->getPredicate()->pickSplit(L->getSubpredicateHolders());
        L->setChildren(covariant_cast(sets.first));
        L->setPredicate(new P(L->getSubpredicates()));
        S = new InnerEntry<P> (covariant_cast(sets.second));

        S->setNSN(L->getNSN());
        global_nsn++;
        L->setNSN(global_nsn);

        Entry<P> *lParent = L->getRightEntry();
        L->setRightEntry(S);
        S->setRightEntry(lParent);
    }

    while (!path.empty()) {
        InnerEntry<P> *curEntry = path.top().first;
        curEntry->setPredicate(new P(curEntry->getSubpredicates()));
        path.pop();
    }
}

template <typename P>
void Gist<P>::deleteEntry(LeafEntry<P> const &e) {
}

#endif
