//
// Author: Jack Tse
// Date of creation: 21/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_MAP_TEST_H
#define ALGORITEMIMPLEMENTATION_MAP_TEST_H


// Import
#include "UnorderedMap_Base.h"
#include <Test.h>
#include <string>
#include <functional>


// Namespace
namespace Algo {


// Enum
// ...


// Data Structure
template <class Key, class Value>
class TestOperation_UnorderedMap_Base: public TestOperation {
// Class
public:
	struct Parameter {
	public:
		_UnorderedMap_<Key, Value>	*unordered_map;
	};

// Data
public:
	std::function<std::string(const Key)>	*func_key_to_string		= nullptr;
	std::function<std::string(const Value)>	*func_value_to_string 	= nullptr;

// Function
public:
    // init and del
    TestOperation_UnorderedMap_Base()
    {
    }

    ~TestOperation_UnorderedMap_Base() {
    }

    // operation
    // ...

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class TestOperation_UnorderedMap_Insert: public TestOperation_UnorderedMap_Base<Key, Value> {
// Class
public:
	struct Config {
	public:
		Key		key;
		Value	value;
	};

// Data
public:
	Config config;

// Function
public:
    // init and del
    TestOperation_UnorderedMap_Insert(const Config &config):
    TestOperation_UnorderedMap_Base<Key, Value>(),
    config(config)
    {
    }

    TestOperation_UnorderedMap_Insert(Key key, Value value):
    config({key, value})
	{
	}

    ~TestOperation_UnorderedMap_Insert() {
    }

    // operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
    	auto *parameter =
				(typename TestOperation_UnorderedMap_Base<Key, Value>::Parameter*)object;

    	// operation
    	if (parameter->unordered_map == nullptr) return -1;
		parameter->unordered_map->insert(config.key, config.value);

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_key_to_string == nullptr || this->func_value_to_string == nullptr) return 0;

		*output += "Insert key: ";
		*output += (*this->func_key_to_string)(config.key);
		*output += ", value: ";
		*output += (*this->func_value_to_string)(config.value);
		*output += '\n';

		return 0;
	}

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class TestOperation_UnorderedMap_Erase: public TestOperation_UnorderedMap_Base<Key, Value> {
// Class
public:
	struct Config {
	public:
		Key		key;
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_UnorderedMap_Erase(const Config &config):
			TestOperation_UnorderedMap_Base<Key, Value>(),
			config(config)
	{
	}

	TestOperation_UnorderedMap_Erase(Key key):
			config({key})
	{
	}

	~TestOperation_UnorderedMap_Erase() {
	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_UnorderedMap_Base<Key, Value>::Parameter*)object;

		// operation
		if (parameter->unordered_map == nullptr) return -1;
		parameter->unordered_map->erase(config.key);

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_key_to_string == nullptr || this->func_value_to_string == nullptr) return 0;

		*output += "Erase key: ";
		*output += (*this->func_key_to_string)(config.key);
		*output += '\n';

		return 0;
	}

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class TestOperation_UnorderedMap_At: public TestOperation_UnorderedMap_Base<Key, Value> {
// Class
public:
	struct Config {
	public:
		Key		key;
		Value	value;
		bool	is_present;
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_UnorderedMap_At(const Config &config):
	TestOperation_UnorderedMap_Base<Key, Value>(),
	config(config)
	{
	}

	TestOperation_UnorderedMap_At(Key key, Value value, bool is_present = true):
	config({key, value, is_present})
	{
	}

	~TestOperation_UnorderedMap_At() {
	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_UnorderedMap_Base<Key, Value>::Parameter*)object;

		// operation
		if (parameter->unordered_map == nullptr) return -1;
		Value value = parameter->unordered_map->at(config.key);

		// observe
		int8_t ret = 0;
		if ((value == config.value) != config.is_present) ret = 1;

		// result
		if (output == nullptr) return 0;
		if (this->func_key_to_string == nullptr || this->func_value_to_string == nullptr) return 0;

		*output += "At key: ";
		*output += (*this->func_key_to_string)(config.key);
		*output += ", value: ";
		*output += (*this->func_value_to_string)(value);
		*output += ", (";
		*output += ret == 0 ? "true" : "false";
		*output += ")\n";

		return ret;
	}

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class TestOperation_UnorderedMap_Clear: public TestOperation_UnorderedMap_Base<Key, Value> {
// Class
public:
	struct Config {
	public:
		// ...
	};

// Data
public:
	Config config;

// Function
public:
	// init and del
	TestOperation_UnorderedMap_Clear(const Config &config):
	TestOperation_UnorderedMap_Base<Key, Value>(),
	config(config)
	{
	}

	TestOperation_UnorderedMap_Clear()
	{
	}

	~TestOperation_UnorderedMap_Clear() {
	}

	// operation
	int8 execute(void *object, std::string *output = nullptr) override {
		if (object == nullptr) return -1;
		auto *parameter =
				(typename TestOperation_UnorderedMap_Base<Key, Value>::Parameter*)object;

		// operation
		if (parameter->unordered_map == nullptr) return -1;
		parameter->unordered_map->clear();

		// observe
		// ...

		// result
		if (output == nullptr) return 0;
		if (this->func_key_to_string == nullptr || this->func_value_to_string == nullptr) return 0;

		*output += "Clear ";
		*output += "\n";

		return 0;
	}

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace: Algo
}


#endif //ALGORITEMIMPLEMENTATION_MAP_TEST_H
