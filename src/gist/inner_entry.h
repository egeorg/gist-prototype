#pragma once

#include "gist/entry.h"
#include "gist/leaf_entry.h"
#include "gist/node.h"

template <typename P>
class InnerEntry : public Entry<P> {
private:
    Node<P> node;
    
    std::vector<LeafEntry<P> *> find(P const &predicate) {
    	if (!predicate.consistentWith(this.getPredicate())) {
    		return std::vector<LeafEntry<P> *> ();
    	}

    	std::vector<LeafEntry<P> *> result;
    	for (typename std::vector<Entry<P> *>::iterator child = this.node.entries.begin(); child != this.node.entries.end(); ++child) {
			std::vector<LeafEntry<P> *> child_result = (*child).find(predicate);
			result.insert(result.end(), child_result.begin(), child_result.end());	
		}    	
    
    	return result;
    }
};