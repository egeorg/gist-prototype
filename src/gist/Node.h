#include "Entry.h"
#include <vector>

template <typename P>
class Node {
private:
    std::vector<Entry<P> *> entries;
};