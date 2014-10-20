#include "Entry.h"
#include <vector>

template <typename P>
class LeafEntry<P> : public Entry<P> {
private:
    std::vector<void*> data;
};            