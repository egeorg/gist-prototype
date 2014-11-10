#pragma once

#include "gist/entry.h"
#include "gist/node.h"
#include <vector>

template <typename P>
class InnerEntry : public Entry<P> {
private:
    Node<P> node;
    InnerEntry<P>* parent;

public:
	InnerEntry<P>* getParent() {
		return parent;
	}

    std::vector<Entry<P> *> getChildren() {
        return node.getEntries();
    }

	std::vector<P*> getSubpredicates() {
		std::vector<Entry<P> *> children = getChildren();
		std::vector<P*> result;
		for (std::vector<Entry<P> *>::iterator child = children.begin(); child != children.end(); ++child) {
			result.push_back((*child) -> getPredicate());
		}	
		return result;
	}
};