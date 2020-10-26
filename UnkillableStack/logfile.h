#ifndef _LOG_FILE_
#define _LOG_FILE_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

FILE* log_f = fopen("logfile.txt", "a");

#define put_log(text, ...) fprintf(log_f, text, __VA_ARGS__);
				
#endif _LOG_FILE