#pragma once

#include "ts.hpp"
#include "range.hpp"
#include "tree_cursor.hpp"
#include "node.hpp"
#include <vector>

namespace ts {

class Node;

class Tree : public std::enable_shared_from_this<Tree> {
public:
	Tree(TSTree* tree, const string& source, bool keep_text);
	~Tree();

	inline static std::shared_ptr<Tree> create(TSTree* tree, const string& source, bool keep_text) {
		return std::make_shared<Tree>(tree, source, keep_text);
	}

	Node rootNode();

	const string& text() const;

	TreeCursor walk();
	const TreeCursor walk() const;

	void edit(TSInputEdit);

	std::vector<Range> getChangedRanges(const Tree& newTree) const;
private:

	string source;
	TSTree* tree;

	friend class Node;
	friend class Parser;
};

}