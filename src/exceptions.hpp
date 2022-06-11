#pragma once

#include <exception>
#include "ts.hpp"

namespace ts {

class exception : public std::exception {
public:
	virtual const char* what() const noexcept = 0;
};

class NullNodeException : public exception {
public:
	virtual const char* what() const noexcept override {
		return "Null Node";
	}
};

class NullNameException : public exception {
public:
	virtual const char* what() const noexcept override {
		return "Null Name";
	}
};

class NullLanguageException : public exception {
public:
	virtual const char* what() const noexcept override {
		return "Language ID must not be null";
	}
};

class IncompatibleLanguageVersionException : public exception {
public:
	virtual const char* what() const noexcept override {
		return "Incompatible Language version";
	}
};

class NullSourceException : public exception {
public:
	virtual const char* what() const noexcept override {
		return "Source code is NULL";
	}
};

}