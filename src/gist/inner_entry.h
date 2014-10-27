#pragma once

#include "gist/entry.h"
#include "gist/node.h"
#include <vector>

template <typename P>
class InnerEntry : public Entry<P> {
private:
    Node<P> node;
    
    std::vector<Entry<P> *> getChildren() {
    	return node.getEntries();
    }
};