//
// Author: Jack Tse
// Date of creation: 8/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ADDRESS_H
#define ALGORITEMIMPLEMENTATION_ADDRESS_H


// Import
// ...


// Define
#define getOffset(class_, member_) \
((intptr_t)( &(((class_*)0)->member_) ))


#define getTargetPtr(addr_, target_type_, offset_) \
((target_type_*)((intptr_t)addr_ + offset_))


#define casting(addr_, dst_type_, src_class_, src_member_) \
( getTargetPtr(addr_, dst_type_, getOffset(src_class_, src_member_)) )


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
// ...


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ADDRESS_H
