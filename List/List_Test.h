//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_LIST_TEST_H
#define ALGORITEMIMPLEMENTATION_LIST_TEST_H


// Import
#include "List_Base.h"
#include <string>
#include <functional>


// Namespace-Begin - Algo
namespace Algo {


// Enum
enum class ListOperation {
	PUSH_BACK,
	POP_BACK,
	CLEAR,
	AT,
	NOT_AT,
	NONE,
//	SIZE_ENUM
};


// Data Structure
// ...


// Function - Prototype
template <class Value>
Pair<ListOperation, Pair<int, Value>> maskListOperation(
		ListOperation	operation,
		int				position,
		Value			value);


template <class Value>
int runOperation_List(
		_List_<Value>									&list,
		Pair<ListOperation, Pair<int, Value>>			*operation,
		int												size_operation,
		const std::function<void(const std::string&)>	*func_log				= nullptr,
		const std::function<std::string(const int)>		*func_key_to_string		= nullptr,
		const std::function<std::string(const Value)>	*func_value_to_string 	= nullptr);


template <class Value>
std::string getOperationString(
		const Pair<ListOperation, Pair<int, Value>>		&operation,
		const std::function<std::string(const int)>		*func_key_to_string,
		const std::function<std::string(const Value)>	*func_value_to_string);


// Function - Implementation
template <class Value>
Pair<ListOperation, Pair<int, Value>> makeListOperation(
		ListOperation 	operation,
		int 			position,
		Value 			value) {

	// fix parameter
	switch (operation) {
		case ListOperation::PUSH_BACK:
			return Pair<ListOperation, Pair<int, Value>>(operation, Pair<int, Value>(0, value));
		case ListOperation::POP_BACK:
			return Pair<ListOperation, Pair<int, Value>>(operation, Pair<int, Value>(0, 0));
		case ListOperation::CLEAR:
			return Pair<ListOperation, Pair<int, Value>>(operation, Pair<int, Value>(0, 0));
		case ListOperation::AT:
			return Pair<ListOperation, Pair<int, Value>>(operation, Pair<int, Value>(position, value));
		case ListOperation::NOT_AT:
			return Pair<ListOperation, Pair<int, Value>>(operation, Pair<int, Value>(position, value));
		default:
			return Pair<ListOperation, Pair<int, Value>>(ListOperation::NONE, Pair<int, Value>(0, 0));
	}
}


template <class Value>
int runOperation_List(
		_List_<Value>									&list,
		Pair<ListOperation, Pair<int, Value>>			*operation_list,
		int												size_operation,
		const std::function<void(const std::string&)>	*func_log,
		const std::function<std::string(const int)>		*func_key_to_string,
		const std::function<std::string(const Value)>	*func_value_to_string) {

	// CONFIG
	Value temp;

	// CORE
	for (int i = 0; i < size_operation; ++i) {
		// get operation
		auto &operation = operation_list[i];

		// string for logging
		std::string content;
		content += getOperationString(operation, func_key_to_string, func_value_to_string);

		// run operation
		try {

			switch (operation.first) {
				case ListOperation::PUSH_BACK:
					// push_back
					// [ignore, value(used to insert)]
					list.push_back(operation.second.second);
					break;

				case ListOperation::POP_BACK:
					// erase
					// [ignore, ignore]
					list.pop_back();
					break;

				case ListOperation::CLEAR:
					// clear
					// [ignore, ignore]
					list.clear();
					break;

				case ListOperation::AT:
					// at
					// [position, value(used to compare with list)]
					temp = list.at(operation.second.first);
					if (temp != operation.second.second) throw std::runtime_error("");
					break;

				case ListOperation::NOT_AT:
					// not at
					// [position, value(used to compare with list)]
					temp = list.at(operation.second.first);
					if (temp == operation.second.second) throw std::runtime_error("");
					break;

				default:
					break;
			}

		} catch(...) {
			content += " => false";
			if (func_log != nullptr) (*func_log)(content);
			return i;
		}

		// log
		content += " => true";
		if (func_log != nullptr) (*func_log)(content);
	}

	// RET
	// everything is fine
	return 0;

}


template <class Value>
std::string getOperationString(
		const Pair<ListOperation, Pair<int, Value>>		&operation,
		const std::function<std::string(const int)>		*func_key_to_string,
		const std::function<std::string(const Value)>	*func_value_to_string) {

	// CHECK
	if (func_key_to_string == nullptr || func_value_to_string == nullptr) return std::string();

	// CONFIG
	std::string content;

	// CORE
	switch (operation.first) {
		case ListOperation::PUSH_BACK:
			// push_back
			// [ignore, value(used to insert)]
			content += "push_back: value: ";
			content += (*func_value_to_string)(operation.second.second);
			break;

		case ListOperation::POP_BACK:
			// pop_back
			// [ignore, ignore]
			content += "pop_back";
			break;

		case ListOperation::CLEAR:
			// clear
			// [ignore, ignore]
			content += "clear";
			break;

		case ListOperation::AT:
			// at
			// [position, value(used to compare with list)]
			content += "at: position: ";
			content += (*func_key_to_string)(operation.second.first);
			break;

		case ListOperation::NOT_AT:
			// at
			// [position, value(used to compare with list)]
			content += "not at: position: ";
			content += (*func_key_to_string)(operation.second.first);
			break;
			break;

		default:
			break;
	}

	// RET
	return content;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_LIST_TEST_H
