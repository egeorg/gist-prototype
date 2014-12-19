#pragma once

#include "gist/entry.h"
#include "gist/node.h"
#include "leaf_entry.h"
#include <vector>

template <typename P>
class InnerEntry : public Entry<P> {
private:
    Node<P> *node;
public:
    InnerEntry<P> () {
        node = new Node<P>(std::vector<Entry<P> *>());
//        this->predicate = *(new P()); // TODO: Predicates should not be constructed this way
    }

    InnerEntry<P> (std::vector<Entry<P> *> entries) {
        node = new Node<P>(entries);
        this->predicate = *(new P(getSubpredicates()));
    }

    std::vector<Entry<P> *> getChildren() {
        return node->getEntries();
    }

    std::vector<PredicateHolder<P>*> getSubpredicates() {
        std::vector<Entry<P> *> children = getChildren();
        std::vector<PredicateHolder<P>*> result;
        for (typename std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
            result.push_back(new PredicateHolder<P>((*child) -> getPredicate()));
        }
        return result;
    }

    void setChildren (std::vector<Entry<P> *> entries) {
        node->setEntries(entries);
        //predicate = *(new P(this->getSubpredicates()));
    }

    void insert(const Entry<P> &E) {
        E.setParent(this);
        node->insert(E);
    }
};