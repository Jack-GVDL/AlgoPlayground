//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_LIST_TEST_H
#define ALGORITEMIMPLEMENTATION_LIST_TEST_H


// Import
#include "List_Base.h"
#include <Test.h>
#include <string>
#include <functional>


// Namespace-Begin - Algo
namespace Algo {


// Enum
// ...


// Data Structure
template <class Value>
class TestOperation_List_Base: public TestOperation {
// Class
public:
	struct Parameter {
	public:
		_List_<Value>	*list;
	};

// Data
public:
	std::function<std::string(const Value)>	*func_value_to_string 	= nullptr;

// Function
public:
    // init and del
    TestOperation_List_Base() {

    }

    ~TestOperation_List_Base() {

    }

    // operation
    // ...

// Operator Overload
public:
	// ...
};


template <class Value>
class TestOperation_List_PushBack: public TestOperation_List_Base<Value> {
// Class
public:
	struct Config {
	public:
		Value value;
	};

// Data
public:
    Config config;

// Function
public:
    // init and del
    TestOperation_List_PushBack(Value value):
    config({value})
    {
    }

    ~TestOperation_List_PushBack() {

    }

    // operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_List_Base<Value>::Parameter*)object;

		// operation
		if (parameter->list == nullptr) return -1;
		parameter->list->push_back(config.value);

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_value_to_string == nullptr) return 0;

		*output += "PushBack: ";
		*output += (*this->func_value_to_string)(config.value);
		*output += "\n";

		return 0;
	}

// Operator Overload
public:
	// ...
};


template <class Value>
class TestOperation_List_PopBack: public TestOperation_List_Base<Value> {
// Class
public:
	struct Config {
	public:
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_List_PopBack():
	config({})
	{
	}

	~TestOperation_List_PopBack() {
	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_List_Base<Value>::Parameter*)object;

		// operation
		if (parameter->list == nullptr) return -1;
		parameter->list->pop_back();

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_value_to_string == nullptr) return 0;

		*output += "PopBack";
		*output += "\n";

		return 0;
	}

// Operator Overload
public:
	// ...
};


template <class Value>
class TestOperation_List_Clear: public TestOperation_List_Base<Value> {
// Class
public:
	struct Config {
	public:
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_List_Clear():
	config({})
	{
	}

	~TestOperation_List_Clear() {

	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_List_Base<Value>::Parameter*)object;

		// operation
		if (parameter->list == nullptr) return -1;
		parameter->list->clear();

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_value_to_string == nullptr) return 0;

		*output += "Clear";
		*output += "\n";

		return 0;
	}

// Operator Overload
public:
	// ...
};


template <class Value>
class TestOperation_List_At: public TestOperation_List_Base<Value> {
// Class
public:
	struct Config {
	public:
		int		index;
		Value	value;
		bool	is_present;
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_List_At(int index, Value value, bool is_present = true):
	config({index, value, is_present})
	{
	}

	~TestOperation_List_At() {
	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_List_Base<Value>::Parameter*)object;

		// operation
		if (parameter->list == nullptr) return -1;
		Value value = parameter->list->at(config.index);

		// observe
		int8_t ret = 0;
		if ((value == config.value) != config.is_present) ret = 1;

		// result
		if (output == nullptr) return 0;
		if (this->func_value_to_string == nullptr) return 0;

		*output += "At: index: ";
		*output += std::to_string(config.index);
		*output += ", value: ";
		*output += (*this->func_value_to_string)(config.value);
		*output += ", (";
		*output += ret == 0 ? "true" : "false";
		*output += ")\n";

		return 0;
	}

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_LIST_TEST_H
