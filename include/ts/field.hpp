#pragma once

#include "tree_sitter/api.h"

extern "C" {

namespace ts {

class Field {
public:
	constexpr Field(TSFieldId id, const char* name)
		: id(id), name(name) {}

	inline operator TSFieldId() const {
		return id;
	}

	TSFieldId id;
	const char* name;
};

}

}