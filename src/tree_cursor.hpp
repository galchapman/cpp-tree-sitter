#pragma once

#include "ts.hpp"

namespace ts {

class Node;
class Tree;

class TreeCursor {
public:

	TreeCursor(Node node, std::shared_ptr<Tree> tree);
	TreeCursor(TreeCursor&&);
	~TreeCursor();

	Node node();

	const char* getCurrectFieldName() const;

	bool gotoParent();
	bool gotoFirstChild();
	bool gotoNextSibling();
private:
	TSTreeCursor cursor;
	Node *m_node;
	std::shared_ptr<Tree> m_tree;
};

}