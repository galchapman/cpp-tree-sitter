#include "ts/children.hpp"
#include "ts/tree.hpp"
#include "ts/node.hpp"

namespace ts {

Children::Children(TSNode parent, std::shared_ptr<Tree> tree)
	: parent(parent), tree(tree) {}

Node Children::operator[](uint32_t index) const {
	return Node(ts_node_child(parent, index), tree);
}

uint32_t Children::size() const {
	return ts_node_child_count(parent);
}

Children::iterator::iterator(const Children& children, uint32_t index)
	: children(children), index(index) {}

Node Children::iterator::operator*() const {
	return children[index];
}

Children::iterator& Children::iterator::operator++() {
	index++;
	return *this;
}

bool Children::iterator::operator==(const iterator& other) const {
	return (&children == &other.children) && (index == other.index);
}

bool Children::iterator::operator!=(const iterator& other) const {
	return (&children != &other.children) || (index != other.index);
}

Children::iterator Children::begin() const {
	return iterator(*this, 0);
}

Children::iterator Children::end() const {
	return iterator(*this, size());
}

}