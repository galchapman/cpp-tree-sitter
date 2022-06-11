#include "tree.hpp"
#include "node.hpp"
#include "tree_cursor.hpp"
#include <iostream>

namespace ts {

Tree::Tree(TSTree* tree, const string& source, bool keep_text) {
	this->source = keep_text ? source : "";
	this->tree = tree;
}

Tree::~Tree() {
	std::cout << "deleted tree" << std::endl;
	ts_tree_delete(tree);
}

Node Tree::rootNode() {
	return Node(ts_tree_root_node(tree), shared_from_this());
}

const Node Tree::rootNode() const {
	return const_cast<Tree*>(this)->rootNode();
}

const string& Tree::text() const {
	if (source.empty()) {
		throw NullSourceException();
	}
	return source;
}

TreeCursor Tree::walk() {
	return TreeCursor(Node(ts_tree_root_node(tree), shared_from_this()), shared_from_this());
}

const TreeCursor Tree::walk() const {
	return const_cast<Tree*>(this)->walk();
}

void Tree::edit(TSInputEdit edit) {
	ts_tree_edit(tree, &edit);
	source = nullptr;
}

std::vector<Range> Tree::getChangedRanges(const Tree& newTree) const {
	uint32_t length = 0;
	TSRange *ranges = ts_tree_get_changed_ranges(tree, newTree.tree, &length);
	std::vector<Range> result;
	result.resize(length);
	for (size_t i = 0; i < length; i++) {
		result[i] = ranges[i];
	}
	free(ranges);
	return result;
}

}
