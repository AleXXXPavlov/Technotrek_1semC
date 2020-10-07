/* EQUIVALENTS OF STANDARD FUNCTIONS */

#ifndef mystring.h
#define mystring.h

#include <stdio.h>
#include <assert.h>
#include <string.h>

// ----------------------------------------------------------------------
//! Analog of strlen() in C
//! Function to count characters in a string
//!
//! @param [in] pointer to the string
//! @param [out] number of characters
//!
// ----------------------------------------------------------------------
size_t StrLength(const char*);

// ----------------------------------------------------------------------
//! Analog of strncpy() in C
//! Function copies up to n characters 
//! 
//! @param [in] pointer to the string to be inserted
//! @param [in] pointer to copy string
//! @param [in] number of copy characters
//! 
// ----------------------------------------------------------------------
void StrCopyN(char*, const char*, size_t);


// ----------------------------------------------------------------------
//! Analog of strncat() in C
//! Function for concatenating strings with limiting the length of the 
//! added string
//!
//! @param [in] pointer to the string to which the string will be added
//! @param [in] pointer to copy string 
//! @param [in] maximum number to characters 
//! @param [out] pointer to the string where the string is added
//!
// ----------------------------------------------------------------------
char* StrCatN(char*, const char*, size_t); // ----- run time


// ----------------------------------------------------------------------
//! Analog of strstr() in C
//! Function to find the first occurrence of one string within another
//!
//! @param [in] pointer to the string in which to enter the search
//! @param [in] pointer to the search string
//! @param [out] NULL / pointer to the first occurrence
//!
// ----------------------------------------------------------------------
char* StrStr(const char*, const char*);


// ----------------------------------------------------------------------
//! Analog of strtok() in C
//! Function for splitting a string into parts 
//!
//! @param [in] pointer to string to split
//! @param [in] pointer to string containing the delimiter character set
//! @param [out] NULL / Pointer to the first character of the selected 
//! part of the line
//!
// ----------------------------------------------------------------------
char* StrTok(char*, const char*);


// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

size_t StrLength(const char* ptr_s) {
	assert(ptr_s);

	size_t index = 0;
	while (ptr_s[index] != '\0')
		++index;

	return index;
}

void StrCopyN(char* destination, const char* source, size_t num) {
	assert(destination);
	assert(source);

	size_t i = 0;
	while (i != num && source[i] != '\0') {
		destination[i] = source[i];
		++i;
	}

	while (i != num)
		destination[i] = '0';
}

char* StrCatN(char* destination, const char* append, size_t num) {
	assert(destination);
	assert(append);

	size_t d_length = StrLength(destination);
	size_t a_length = StrLength(append);

	for (size_t i = 0; i < num && i < a_length; ++i)
		*(destination + d_length + i) = *(append + i);

	return destination;
}

char* StrStr(const char* strM, const char* strS) {
	assert(strM);
	assert(strS);

	size_t lenM = StrLength(strM);
	size_t lenS = StrLength(strS);

	int parametr = 0;
	for (size_t i = 0; i < lenM - lenS + 1; ++i) {
		if (strM[i] == strS[0]) {
			for (size_t j = 1; j < lenS; ++j) {
				if (strM[i + j] != strS[j]) {
					parametr = 0;
					break;
				}

				parametr = 1;
			}
		}

		if (parametr) {
			return strM + i;
		}
	}
	
	return NULL;
}

char* StrTok(char* str, const char* set) {
	assert(set);

	static char* ptr_str;
	if (str == NULL)
		str = ptr_str;

	str += strspn(str, set); 
	if (*str == '\0') {
		ptr_str = str;
		return NULL;
	}

	char* result = str;
	str = strpbrk(result, set); 
	if (str == NULL) {
		ptr_str = strchr(result, '\0');
	}
	else {
		*str = '\0';
		ptr_str = str + 1;
	}

	return result;
}

#endif mystring.h
