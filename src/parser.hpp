#pragma once

#include "ts.hpp"
#include "tree.hpp"

namespace ts {

class Parser {
public: 
	Parser();
	~Parser();

	std::shared_ptr<Tree> parse(const string& source, Tree* old_tree=nullptr, bool keep_text=true) const;

	void setLanguge(const TSLanguage*);
private:
	TSParser *parser;
};

}
