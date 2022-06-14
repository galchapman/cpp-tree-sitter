#pragma once

#include "ts.hpp"
#include "node.hpp"

extern "C" {

namespace ts {

class Node;
class Tree;

class TreeCursor {
public:

	TreeCursor(Node, std::shared_ptr<Tree>);
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

}