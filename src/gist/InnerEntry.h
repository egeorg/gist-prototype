#include "Entry.h"
#include "Node.h"

template <typename P>
class InnerEntry<P> : public Entry<P> {
private:
    Node<P> *node;
};