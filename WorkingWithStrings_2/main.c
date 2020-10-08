/* SORTING THE POEM */

#include "onegin.h"
#include <locale.h>

int main() {
	setlocale(LC_ALL, "RUS");

	/* Initial parametrs */
	char file_name[] = "Onegin.txt";

	/* File reading */
	long long size = 0;
	char* main_buffer = FileReader(file_name, &size);

	/* Sorting */
	long num_str = 1;
	char** buff_addr = StrSplitting(main_buffer, &num_str, size);

	Redefinition(main_buffer, size, num_str);

	assert(buff_addr != NULL);
	qsort(buff_addr, num_str, sizeof(char*), MyComparator);

	/* Entering results into a file */
	PrintSortedPoem1(buff_addr, num_str, file_name);
	PrintSortedPoem2(buff_addr, num_str, file_name);
	PrintPoem(main_buffer, size, num_str, file_name);

	return 0;
}