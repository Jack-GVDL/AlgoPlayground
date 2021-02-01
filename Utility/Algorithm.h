//
// Author: Jack Tse
// Date of creation: 28/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ALGORITHM_H
#define ALGORITEMIMPLEMENTATION_ALGORITHM_H


// Import
#include <algorithm>


// Namespace-Begin - Algo
namespace Algo {


// Macro
//#define max(a,b) (((a)>(b))?(a):(b))
//#define min(a,b) (((a)< b))?(a):(b))

#define max(a,b) std::max(a,b)
#define min(a,b) std::min(a,b)


// Data Structure
// ...


// Function Prototype
static inline unsigned int 	strlen(const char *s);
static inline int 			strcmp(const char *str_1, const char *str_2);
static inline const char* 	strchr(const char *str, int character);
static inline char* 		strchr(char *str, int character);
static inline void 			memcpy(void *dst, const void *src, unsigned int n);

static inline const char* 	_strchr_(const char *str, int character);


// Function - Implementation
static inline unsigned int strlen(const char *s) {
	const char *start = s;
	while (*s != 0) s++;
	return s - start;
}


static inline int strcmp(const char *str_1, const char *str_2) {
	while (*str_1 == *str_2 && *str_1 != 0) {
		str_1++;
		str_2++;
	}
	return *str_1 - *str_2;
}


static int strncmp(const char *str_1, const char *str_2, unsigned int num) {
	while (num > 0 && *str_1 == *str_2 && *str_1 != 0) {
		str_1++;
		str_2++;
		num--;
	}
	return *str_1 - *str_2;
}


static inline const char* strchr(const char *str, int character) {
	return _strchr_(str, character);
}


static inline char* strchr(char *str, int character) {
	return (char*)(_strchr_(str, character));
}


static inline const char* _strchr_(const char *str, int character) {
	while (*str != 0) {
		if (*str != character) {
			str++;
			continue;
		}
		return str;
	}
	return nullptr;
}


static inline void memcpy(void *dst, const void *src, unsigned int n) {
	char 		*dst_ = (char *)dst;
	const char 	*src_ = (const char*)src;

	while (n > 0) {
		*dst_ = *src_;
		dst_++;
		src_++;
		n--;
	}
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ALGORITHM_H
