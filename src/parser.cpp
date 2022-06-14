#include "ts/parser.hpp"

#include "ts/exceptions.hpp"

namespace ts {

Parser::Parser() {
	parser = ts_parser_new();
}

Parser::~Parser() {
	ts_parser_delete(parser);
}

std::shared_ptr<Tree> Parser::parse(const string& source, Tree* old_tree, bool keep_text) const {
	TSTree *new_tree = ts_parser_parse_string(parser, old_tree != nullptr ? old_tree->tree : nullptr, source.c_str(), source.length());
	return Tree::create(new_tree, source, keep_text);
}

void Parser::setLanguage(const TSLanguage* language) {
	if (!language) {
		throw NullLanguageException();
	}
	unsigned version = ts_language_version(language);
	if (version < TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION || TREE_SITTER_LANGUAGE_VERSION < version) {
		throw IncompatibleLanguageVersionException();
	}
	ts_parser_set_language(parser, language);
}

}