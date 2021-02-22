//
// Author: Jack Tse
// Date of creation: 22/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_TESTOPERATION_H
#define ALGORITEMIMPLEMENTATION_TESTOPERATION_H


// Import
#include <string>
#include <vector>
#include <functional>
#include <Utility.h>


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
    virtual int8 execute(void *parameter, const std::function<void(const std::string &)> *output = nullptr) {
    	return 0;
    }

// Operator Overload
public:
	// ...
};


class TestCluster {
// Data
public:
    std::vector<TestOperation*> operation_list;

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
