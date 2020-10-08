/* All functions for Onegin */

#ifndef onegin
#define onegin

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

// --------------------------------------------------------------
//! Function for reading data from a file
//!
//! @param [in] name of the file to read
//! @param [in] file size in bytes
//! @param [out] pointer to character buffer
//!
// --------------------------------------------------------------
char* FileReader(char[], long long*);

// --------------------------------------------------------------
//! Function for splitting a character buffer into lines
//!
//! @param [in] pointer to character buffer
//! @param [in] pointer to the number of strings
//! @param [in] number of characters in the buffer
//! @param [out] buffer of pointers to the beginning of lines
//!
// --------------------------------------------------------------
char** StrSplitting(char*, long*, long long);

// --------------------------------------------------------------
//! Function to redefinition residual characters in the buffer
//! 
//! @param [in] pointer to character buffer
//! @param [in] number of characters in the buffer
//! @param [in] number of strings in the buffer
//!
// --------------------------------------------------------------
void Redefinition(char*, long long, long);

// --------------------------------------------------------------
//! Function to compare two strings
//!
//! @param [in] pointer to the first string
//! @param [in] pointer to the second string
//! @param [out] comparison result
//!
// --------------------------------------------------------------
int MyComparator(const void*, const void*);

// --------------------------------------------------------------
//! Function for writing an ascending poem to a file
//!
//! @param [in] buffer of pointers to the beginning of lines
//! @param [in] number of the strings
//! @param [in] file name
//!
// --------------------------------------------------------------
void PrintSortedPoem1(char**, long, char[]);

// --------------------------------------------------------------
//! Function for writing an descending poem to a file
//!
//! @param [in] buffer of pointers to the beginning of lines
//! @param [in] number of strings
//! @param [in] file name
//!
// --------------------------------------------------------------
void PrintSortedPoem2(char**, long, char[]);

// --------------------------------------------------------------
//! Function to write a poem to a file
//!
//! @param [in] pointer to the character buffer
//! @param [in] number of characters
//! @param [in] number of strings
//! @param [in] file name
//!
// --------------------------------------------------------------
void PrintPoem(char*, long long, long, char[]);


char* FileReader(char file_name[], long long* fsize) {
	FILE* f_poem = fopen(file_name, "r");
	assert(f_poem != NULL);

	fseek(f_poem, 0, SEEK_END);
	*fsize = ftell(f_poem) + 1;
	fseek(f_poem, 0, SEEK_SET);

	char* f_buff = (char*)malloc(*fsize * sizeof(char));

	assert(f_buff != NULL);
	fread(f_buff, sizeof(char), *fsize, f_poem);

	fclose(f_poem);

	return f_buff;
}

char** StrSplitting(char* buff, long* num_str, long long size) {
	for (int i = 0; i < size; ++i) {
		if (buff[i] == '\n')
			++(*num_str);
	}

	char** arr_addr = (char**)malloc(*num_str * sizeof(char*)); // array of strings' addresses
	arr_addr[0] = buff;

	long ai = 0;
	for (long long i = 0; i < size; ++i) {
		if (buff[i] == '\n') {
			arr_addr[++ai] = buff + i + 1;
			buff[i] = '\0'; // string's end
		}
	}

	return arr_addr;
}

void Redefinition(char* buff, long long b_size, long s_size) {
	for (int i = 0; i < s_size; ++i) {
		buff[b_size - i - 1] = '\0';
	}
}

int MyComparator(const void* str1, const void* str2) {
	assert(str1 != NULL);
	assert(str2 != NULL);

	char* ptr1 = *(char**)str1;
	char* ptr2 = *(char**)str2;

	while (ispunct(*ptr1))
		++ptr1;
	while (ispunct(*ptr2))
		++ptr2;

	unsigned char sym1,
		sym2;

	while ((sym1 = *(ptr1++)) == (sym2 = *(ptr2++))) {
		if (sym1 == '\0')
			return 0;
	}

	return sym1 - sym2;
}

void PrintSortedPoem1(char** buff_addr, long num_str, char file_name[]) {
	FILE* f_poem = fopen(file_name, "w");

	for (int i = 0; i < num_str; ++i) {
		fputs(buff_addr[i], f_poem);
		fputc('\n', f_poem);
	}

	fputc('\n', f_poem);

	fclose(f_poem);
}

void PrintSortedPoem2(char** buff_addr, long num_str, char file_name[]) {
	FILE* f_poem = fopen(file_name, "a");

	for (int i = num_str - 1; i > -1; --i) {
		fputs(buff_addr[i], f_poem);
		fputc('\n', f_poem);
	}

	fputc('\n', f_poem);

	fclose(f_poem);
}

void PrintPoem(char* buff_sym, long long num_sym, long num_str, char file_name[]) {
	FILE* f_poem = fopen(file_name, "a");

	for (long long i = 0; i < num_sym - num_str; ++i) {
		buff_sym[i] == '\0' ? fputc('\n', f_poem) : fputc(buff_sym[i], f_poem);
	}

	fclose(f_poem);
}


#endif onegin