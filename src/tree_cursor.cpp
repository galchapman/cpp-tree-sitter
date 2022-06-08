#include "tree_cursor.hpp"
#include "node.hpp"

namespace ts {

TreeCursor::TreeCursor(Node node, std::shared_ptr<Tree> tree)
	: m_tree(tree), m_node(new Node(node)) {}

TreeCursor::TreeCursor(TreeCursor&& other)
	: m_tree(other.m_tree), m_node(nullptr), cursor(ts_tree_cursor_copy(&other.cursor)) {
}

TreeCursor::~TreeCursor() {
	if (m_node != nullptr) {
		delete m_node;
	}
	ts_tree_cursor_delete(&cursor);
}

Node TreeCursor::node() {
	if (!m_node) {
		m_node = new Node(ts_tree_cursor_current_node(&cursor), m_tree);
	}
	return *m_node;
}

const char* TreeCursor::getCurrectFieldName() const {
	return ts_tree_cursor_current_field_name(&cursor);
}

bool TreeCursor::gotoParent() {
	bool result = ts_tree_cursor_goto_parent(&cursor);
	if (result) {
		m_node = nullptr;
	}
	return result;
}

bool TreeCursor::gotoFirstChild() {
	bool result = ts_tree_cursor_goto_first_child(&cursor);
	if (result) {
		m_node = nullptr;
	}
	return result;
}

bool TreeCursor::gotoNextSibling() {
	bool result = ts_tree_cursor_goto_next_sibling(&cursor);
	if (result) {
		m_node = nullptr;
	}
	return result;
}

}