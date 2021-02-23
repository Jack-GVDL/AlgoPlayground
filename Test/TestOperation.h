//
// Author: Jack Tse
// Date of creation: 22/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_TESTOPERATION_H
#define ALGORITEMIMPLEMENTATION_TESTOPERATION_H


// Import
#include <functional>
#include <Utility.h>
#include <string>
#include <vector>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
class TestOperation {
// Data
public:
    char 	*description	= nullptr;
    void	*config			= nullptr;

// Function
public:
    // init and del
    TestOperation() {
    }

    ~TestOperation() {
    }

    // operation
    virtual int8 execute(void *parameter, std::string *output = nullptr) {
    	return 0;
    }

// Operator Overload
public:
	// ...
};


class TestCluster: public TestOperation {
// Data
public:
    std::vector<TestOperation*> operation_list;
    std::vector<std::string>	log_list;  // one-item per each operation

// Function
public:
    // init and del
    TestCluster() {

    }

    ~TestCluster() {

    }

    // operation
    int8_t addOperation(TestOperation *operation) {
    	operation_list.push_back(operation);
    	return 0;
    }

	int8 execute(void *parameter, std::string *output = nullptr) override {
		// set output function
		// assumed: log_list is not empty
    	for (TestOperation *operation : operation_list) {
    		// execute operation
    		std::string content;
    		int8_t ret = operation->execute(parameter, &content);

    		// for ret < 0, which is testing error which testing must be stop
    		if (ret < 0) return ret;

    		// log
    		log_list.push_back(content);
		}

    	// push all the stuff to outer output
    	if (output == nullptr) return 0;
    	for (auto &log : log_list) *output += log;

    	// normal exit
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


#endif //ALGORITEMIMPLEMENTATION_TESTOPERATION_H
