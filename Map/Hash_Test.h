//
// Author: Jack Tse
// Date of creation: 21/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_HASH_TEST_H
#define ALGORITEMIMPLEMENTATION_HASH_TEST_H


// Import
#include "UnorderedMap.h"
#include <string>
#include <functional>


// Namespace
namespace Algo {


// Enum
enum HashOperation {
	INSERT,
	ERASE,
	CLEAR,
	AT,
	NONE,
	SIZE_ENUM
};


// Data Structure
// ...


// Function - Prototype
template <class Key, class Value>
Pair<HashOperation, Pair<Key, Value>> maskHashOperation(
		HashOperation 	operation,
		Key 			key,
		Value 			value);


template <class Key, class Value>
int runHash(
		UnorderedMap<Key, Value> 							&hash_table,
		Pair<HashOperation, Pair<Key, Value>> *operation,
		int 											size_operation,
		const std::function<void(const std::string&)>	*func_log 				= nullptr,
		const std::function<std::string(const Key)> 	*func_key_to_string 	= nullptr,
		const std::function<std::string(const Value)>	*func_value_to_string 	= nullptr);


template <class Key, class Value>
std::string getOperationString(
		const Pair<HashOperation, Pair<Key, Value>>	&operation,
		const std::function<std::string(const Key)> 			*func_key_to_string,
		const std::function<std::string(const Value)>			*func_value_to_string);


// Function - Implementation
template <class Key, class Value>
Pair<HashOperation, Pair<Key, Value>> makeHashOperation(
		HashOperation 	operation,
		Key 			key,
		Value 			value) {

	// fix parameter
	switch (operation) {
		case HashOperation::INSERT:
			return Pair<HashOperation, Pair<Key, Value>>(operation, Pair<Key, Value>(key, value));
		case HashOperation::ERASE:
			return Pair<HashOperation, Pair<Key, Value>>(operation, Pair<Key, Value>(key, 0));
		case HashOperation::CLEAR:
			return Pair<HashOperation, Pair<Key, Value>>(operation, Pair<Key, Value>(0, 0));
		case HashOperation::AT:
			return Pair<HashOperation, Pair<Key, Value>>(operation, Pair<Key, Value>(key, value));
		default:
			return Pair<HashOperation, Pair<Key, Value>>(HashOperation::NONE, Pair<Key, Value>(0, 0));
	}
}


template <class Key, class Value>
int runHash(
		UnorderedMap<Key, Value> 							&hash_table,
		Pair<HashOperation, Pair<Key, Value>> *operation,
		int 											size_operation,
		const std::function<void(const std::string&)>	*func_log,
		const std::function<std::string(const Key)> 	*func_key_to_string,
		const std::function<std::string(const Value)>	*func_value_to_string) {

	// CONFIG
	Value temp;

	// CORE
	for (int i = 0; i < size_operation; ++i) {
		// string for logging
		std::string content;
		content += getOperationString(operation[i], func_key_to_string, func_value_to_string);

		// operation
		try {

			switch (operation[i].first) {
				// insert
				// [key, value(used to insert)]
				case HashOperation::INSERT:
					hash_table.insert(operation[i].second.first, operation[i].second.second);
					break;

				// erase
				// [key, ignore]
				case HashOperation::ERASE:
					hash_table.erase(operation[i].second.first);
					break;

				// clear
				// [ignore, ignore]
				case HashOperation::CLEAR:
					hash_table.clear();
					break;

				// at
				// [key, value(used to compare with table)]
				case HashOperation::AT:
					temp = hash_table.at(operation[i].second.first);
					if (temp != operation[i].second.second) throw;
					break;

				default:
					break;
			}

		} catch (...) {
			content += " => false";
			if (func_log != nullptr) (*func_log)(content);
			return i;
		}

		// log
		content += " => true";
		if (func_log != nullptr) (*func_log)(content);

	}

	// everything is fine
	return 0;
}


template <class Key, class Value>
std::string getOperationString(
		const Pair<HashOperation, Pair<Key, Value>>	&operation,
		const std::function<std::string(Key)> 					*func_key_to_string,
		const std::function<std::string(Value)>					*func_value_to_string) {

	// CHECK
	if (func_key_to_string == nullptr || func_value_to_string == nullptr) return std::string();

	// CONFIG
	std::string content;

	// CORE
	switch (operation.first) {
		// insert
		// [key, value (used to insert)]
		case HashOperation::INSERT:
			content += "insert: key: ";
			content += (*func_key_to_string)(operation.second.first);
			content += ", value: ";
			content += (*func_value_to_string)(operation.second.second);
			break;

		// erase
		// [key, ignore]
		case HashOperation::ERASE:
			content += "erase: key: ";
			content += (*func_key_to_string)(operation.second.first);
			break;

		// clear
		// [ignore, ignore]
		case 2:
			content += "clear";
			break;

		// at
		// [key, value(used to compare with table)]
		case 3:
			content += "at: key: ";
			content += (*func_key_to_string)(operation.second.first);
			content += ", value (for comparison): ";
			content += (*func_value_to_string)(operation.second.second);
			break;

		default:
			break;
	}

	return content;
}


// Namespace: Algo
};


#endif //ALGORITEMIMPLEMENTATION_HASH_TEST_H
