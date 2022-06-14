#pragma once

#include "ts/ts.hpp"

#include <memory>

extern "C" {

namespace ts {

class Node;
class Tree;

class Children {
public:
	Node operator[](uint32_t) const;

	uint32_t size() const;
	
	class iterator {
		uint32_t index;
		const Children &children;

		iterator(const Children&, uint32_t);
	public:
		// Go to next child of type
		iterator& nextOfType(TSSymbol);

		Node operator*() const;
		Node operator->() const;
		iterator& operator++();

		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;

		friend class Children;
	};

	iterator begin() const;
	iterator end() const;

private:
	TSNode parent;
	std::shared_ptr<Tree> tree;

	Children(TSNode parent, std::shared_ptr<Tree> tree);

	friend class Node;
};

}

}