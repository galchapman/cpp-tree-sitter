#pragma once

#include <exception>
#include "ts.hpp"

namespace ts {

class execption : std::exception {
public:
	virtual const char* what() const noexcept = 0;
};

class NullNodeException : execption {
	virtual const char* what() const noexcept override {
		return "Null Node";
	}
};

class NullNameException : execption {
	virtual const char* what() const noexcept override {
		return "Null Name";
	}
};

class NullLanguageException : execption {
	virtual const char* what() const noexcept override {
		return "Language ID must not be null";
	}
};

class IncompatibleLanguageVersionException : execption {
	virtual const char* what() const noexcept override {
		return "Incompatible Language version";
	}
};

class NullSourceException : execption {
	virtual const char* what() const noexcept override {
		return "Source code is NULL";
	}
};

}