#pragma once

#include <string>
#include <memory>
#include "ts.hpp"
#include "children.hpp"
#include "point.hpp"
#include "ts.hpp"

namespace ts {

class Tree;
class TreeCursor;

class Node {
public:

	Node(TSNode, std::shared_ptr<Tree>);
	Node(const Node&);
	~Node() = default;


	long id() const;
	string type() const;
	string text() const;

	TreeCursor walk();
	const TreeCursor walk() const;

	bool isNamed() const;
	bool isMissing() const;
	bool hasChanes() const;
	bool hasError() const;

	bool operator==(const Node&) const;

	size_t startByte() const;
	size_t endByte() const;

	Point startPoint() const;
	Point endPoint() const;

	size_t childrenCount() const;
	size_t namedChildrenCount() const;

	std::shared_ptr<Children> children();
	Children namedChildren();
	Children childrenByFieldID(TSFieldId);
	Children childrenByFieldName(const string& name);

	string sexp() const;

	Node getChildByFieldID(TSFieldId field_id);
	Node getChildByFieldName(string name);

	const Node getChildByFieldID(TSFieldId field_id) const;
	const Node getChildByFieldName(string name) const;

	string getChildFiledName(size_t index) const;

	Node nextSibling();
	Node nextNamedSibling();
	Node parent();
	Node prevSibling();
	Node prevNamedSibling();
private:
	TSNode node;
	std::shared_ptr<Children> m_children = nullptr;
	std::shared_ptr<Tree> tree;
};

}

std::ostream& operator<<(std::ostream& os, const ts::Node&);