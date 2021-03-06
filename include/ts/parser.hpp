#pragma once

#include "ts.hpp"
#include "tree.hpp"

extern "C" {

namespace ts {

class Parser {
public: 
	Parser();
	Parser(const TSLanguage*);
	~Parser();

	std::shared_ptr<Tree> parse(const string& source, Tree* old_tree=nullptr, bool keep_text=true) const;

	void setLanguage(const TSLanguage*);
private:
	TSParser *parser;
};

}

}