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

Children::iterator::iterator(TSNode parent, std::shared_ptr<Tree> tree, uint32_t index)
	: parent(parent), tree(tree), index(index) {}

Children::iterator& Children::iterator::findSymbol(TSSymbol symbol) {
	for (; index != ts_node_child_count(parent) && ts_node_symbol(ts_node_child(parent, index)) != symbol; ++index)
		;
	return *this;
}

Node Children::iterator::operator*() const {
	return Node(ts_node_child(parent, index), tree);
}

std::unique_ptr<Node> Children::iterator::operator->() const {
	return std::make_unique<Node>(ts_node_child(parent, index), tree);
}

Children::iterator& Children::iterator::operator++() {
	index++;
	return *this;
}

bool Children::iterator::operator==(const iterator& other) const {
	return (this->parent.id == other.parent.id) && (index == other.index);
}

bool Children::iterator::operator!=(const iterator& other) const {
	return (this->parent.id != other.parent.id) || (index != other.index);
}

Children::iterator Children::begin() const {
	return iterator(parent, tree, 0);
}

Children::iterator Children::end() const {
	return iterator(parent, tree, size());
}

}