#include "ts/node.hpp"

#include "ts/tree.hpp"
#include "ts/tree_cursor.hpp"
#include "ts/exceptions.hpp"
#include "ts/children.hpp"

#include <ostream>

namespace ts {

static TSTreeCursor cursor;

Node::Node(TSNode node, std::shared_ptr<Tree> tree)
	: node(node), tree(tree), children(node, tree) {
	if (ts_node_is_null(node)) {
		throw NullNodeException();
	}
}


long Node::id() const {
	return *(const long*)node.id;
}

string Node::type() const {
	return ts_node_type(node);
}

TSSymbol Node::symbol() const {
	return ts_node_symbol(node);
}

string Node::text() const {
	return tree->text().substr(startByte(), endByte() - startByte());
}

TreeCursor Node::walk() const {
	return TreeCursor(*this, tree);
}

bool Node::isNamed() const {
	return ts_node_is_named(node);
}

bool Node::isMissing() const {
	return ts_node_is_missing(node);
}

bool Node::hasChanes() const {
	return ts_node_has_changes(node);
}

bool Node::hasError() const {
	return ts_node_has_error(node);
}

size_t Node::startByte() const {
	return (size_t)ts_node_start_byte(node);
}

size_t Node::endByte() const {
	return (size_t)ts_node_end_byte(node);
}

Point Node::startPoint() const {
	return ts_node_start_point(node);
}

Point Node::endPoint() const {
	return ts_node_end_point(node);
}

size_t Node::childrenCount() const {
	return ts_node_child_count(node);
}

size_t Node::namedChildrenCount() const {
	return ts_node_named_child_count(node);
}

std::vector<Node> Node::namedChildren() {
	size_t named_count = ts_node_named_child_count(node);
	std::vector<Node> result;
	result.reserve(named_count);
	for (const auto& child : children) {
		if (child.isNamed()) {
			result.emplace_back(child);
		}
	}
	return result;
}

std::vector<Node> Node::childrenByFieldID(TSFieldId id) {
	std::vector<Node> result;
	ts_tree_cursor_reset(&cursor, node);
    int ok = ts_tree_cursor_goto_first_child(&cursor);
	while (ok) {
		if (ts_tree_cursor_current_field_id(&cursor) == id) {
			result.emplace_back(Node(
				ts_tree_cursor_current_node(&cursor), tree));
		}
		ok = ts_tree_cursor_goto_next_sibling(&cursor);
	}

	return result;
} 

std::vector<Node> Node::childrenByFieldName(const string& name) {
	const TSLanguage *lang = ts_tree_language(tree->tree);
	TSFieldId field_id = ts_language_field_id_for_name(lang, name.data(), name.length());
	return childrenByFieldID(field_id);
}

string Node::sexp() const {
	char *sexp = ts_node_string(this->node);
	string result(sexp);
	free(sexp);
	return result;
}

Node Node::getChildByFieldID(TSFieldId field_id) {
	return Node(ts_node_child_by_field_id(node, field_id), tree);
}

Node Node::getChildByFieldName(string name) {
	return Node(ts_node_child_by_field_name(node, name.c_str(), name.length()), tree);
}

const Node Node::getChildByFieldID(TSFieldId field_id) const {
	return Node(ts_node_child_by_field_id(node, field_id), tree);
}

const Node Node::getChildByFieldName(string name) const {
	return Node(ts_node_child_by_field_name(node, name.c_str(), name.length()), tree);
}

string Node::getChildFiledName(size_t index) const {
	return ts_node_field_name_for_child(node, index);
}

Node Node::nextSibling() {
	return Node(ts_node_next_sibling(node), tree);
}

Node Node::nextNamedSibling() {
	return Node(ts_node_next_named_sibling(node), tree);
}

Node Node::parent() {
	return Node(ts_node_parent(node), tree);
}

Node Node::prevSibling() {
	return Node(ts_node_prev_sibling(node), tree);
}

Node Node::prevNamedSibling() {
	return Node(ts_node_prev_named_sibling(node), tree);
}

}

std::ostream& operator<<(std::ostream& os, const ts::Node& node) {
	if (node.isNamed()) {
		return os << "<ts::Node type=" << node.type() << ", start_point=" << node.startPoint() << ", " << node.endPoint() << '>';
	} else {
		return os << "<ts::Node type=\"" << node.type() << "\", start_point=" << node.startPoint() << ", " << node.endPoint() << '>';
	}
}