//
// Author: Jack Tse
// Date of creation: 1/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_STRING_H
#define ALGORITEMIMPLEMENTATION_STRING_H


// Import
#include <List_Base.h>
#include <Vector.h>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
class String: public _List_<char> {
// Data
public:
    Vector<char> container;

// Function
public:
    // init and del
    String() {
    }

    ~String() {
    }

    // operation
    // modifier
	void push_back(const char &value) override {
    	container.push_back(value);
	}

	void pop_back() override {
		container.pop_back();
	}

	void push_front(const char &value) override {
    	container.push_front(value);
    }

    void pop_front() override {
    	container.pop_front();
    }

	void append(const String &str) {
    	append(str.container.data(), container.size());
    }

    void append(const char *s) {
    	unsigned int len = Algo::strlen(s);
    	append(s, len);
    }

    void append(const char *s, unsigned int n) {
    	if (n == 0) return;

    	container.reserve(container.size() + n);
    	memcpy(container.data() + container.size(), s, sizeof(char) * n);
    }

    String& assign(const String &str) {
    	container.assign(str.container.cbegin(), str.container.cend());
    	return *this;
    }

	String& assign(const char *s) {
    	Vector<char>::ConstIterator it_begin(s);
    	Vector<char>::ConstIterator it_end(s + strlen(s));
    	container.assign(it_begin, it_end);
    	return *this;
    }

    void swap(String &str) {
    	auto temp = str.container;
    	str.container 	= this->container;
    	this->container	= temp;
    }

	// data / element access - const
	const char &at(unsigned int index) const override {
		return container.at(index);
	}

	const char &front() const override {
		return container.back();
	}

	const char &back() const override {
		return container.back();
	}

	const char* data() const {
    	return container.data();
    }

	// data / element access - non const
	char &at(unsigned int index) override {
		return container.at(index);
	}

	char &front() override {
		return container.back();
	}

	char &back() override {
		return container.back();
	}

	char* data() {
		return container.data();
	}

	// capacity
	unsigned int size() const override {
		return container.size();
	}

	unsigned int length() const {
    	return container.size();
    }

	unsigned int max_size() const override {
		return container.max_size();
	}

	unsigned int capacity() const {
    	return container.capacity();
    }

	bool empty() const override {
		return container.empty();
	}

	void reserve(unsigned int n) {
    	container.reserve(n);
    }

	void clear() override {
		container.clear();
	}

	// string operation
	const char* c_str() const {
    	char *content = new char[container.size() + 1];
    	memcpy(content, container.data(), container.size());
    	content[container.size()] = 0;
    	return content;
    }

    String substr(unsigned int pos, unsigned len) const {
    	String content;
    	content.append(container.data() + pos, len);
    	return content;
    }

// Operator Overload
public:
	// a += b
	String& operator+= (const String &str) {
    	append(str);
    	return *this;
    }

    // a += b
    String& operator+= (const char *s) {
		append(s);
		return *this;
    }

    // a += b
    String &operator+= (char c) {
    	container.push_back(c);
    	return *this;
    }
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_STRING_H
