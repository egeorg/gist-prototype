#pragma once

#include <vector>
#include "gist/entry.h"


template <typename P>
class LeafEntry : public Entry<P> {
private:
    void* data;

public:
    LeafEntry() {
    }

    LeafEntry(void *data){
        this->data = data;
    }

    void *getData() {
        return data;
    }

private:
    std::vector<Entry<P> *> getChildren() {
		return std::vector<Entry<P> *> ();
	}
};