#ifndef _STACK_
#define _STACK_

#include "logfile.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

typedef double type_el; // stack member type
typedef int sk_error;

size_t CAPACITY = 10; // start capacity

unsigned long long CANARY = 736845756857873; // CANARY'S VALUE

static bool stack_underflow = false;
static bool stack_overflow = false;

// -----------------------------------------------------------------
//! List of processed errors
// -----------------------------------------------------------------
enum stack_codes
{
	STACK_OK,
	STACK_NULL_OBJECT,
	STACK_NO_MEMORY,
	INVALID_DATA,
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	CAPACITY_SMALLER_THAN_SIZE
};

// -----------------------------------------------------------------
//! Stack structure
// -----------------------------------------------------------------
typedef struct stack 
{
	unsigned long long front_canary;

	type_el* ptr_body; 
	size_t size; 
	size_t capacity; 

	unsigned long long back_canary;

} stack;

// -----------------------------------------------------------------
//! Default constructor
//! 
//! @param [out] stack pointer
//!
// -----------------------------------------------------------------
stack* Sk_Creator();

// -----------------------------------------------------------------
//! Default destructor
//! 
//! @param [in] stack pointer
//! @param [out] destruction result 
//!
// -----------------------------------------------------------------
int Sk_Destructor(stack*);

// -----------------------------------------------------------------
//! Function to increase capacity
//! 
//! @param [in] stack pointer
//! @param [out] result of change capacity
//!
// -----------------------------------------------------------------
int Change_Capacity(stack*);

// -----------------------------------------------------------------
//! Function for displaying basic information about the stack
//!
//! @param [in] stack pointer
//! @param [out] output result
//!
// -----------------------------------------------------------------
int Sk_Print(stack*);

// -----------------------------------------------------------------
//! Function to add an item to the stack
//!
//! @param [in] stack pointer
//! @param [in] stack member type
//! @param [out] result of pushing an item onto the stack
//!
// -----------------------------------------------------------------
int Sk_Push(stack*, type_el);

// -----------------------------------------------------------------
//! Function to get the top of the stack
//!
//! @param [in] stack pointer
//! @param [out] element at the top of the stack
//!
// -----------------------------------------------------------------
type_el Sk_Pop(stack*);

// -----------------------------------------------------------------
//! Function to check the state of the stack
//!
//! @param [in] stack pionter
//! @param [out] error constant
//!
// -----------------------------------------------------------------
int Verifier(stack*);

// -----------------------------------------------------------------
//! Function for data validation
//!
//! @param [in] stack pointer
//! @param [out] error constant
//! 
//------------------------------------------------------------------
int Verifier_El(stack*);

// -----------------------------------------------------------------
//! Function for logging
//!
//! @param [in] stack pointer
// -----------------------------------------------------------------
void Sk_Dump(stack*);


stack* Sk_Creator()
{
	stack* Obj = (stack*)malloc(sizeof(stack));
	if (Obj == NULL)
	{
		return NULL;
	}

	Obj->ptr_body = (type_el*)calloc(CAPACITY, sizeof(type_el));
	if (Obj->ptr_body == NULL)
	{
		return NULL;
	}

	stack_underflow = false;
	stack_overflow = false;

	Obj->size = 0;
	Obj->capacity = CAPACITY;

	Obj->front_canary = CANARY;
	Obj->back_canary = CANARY;

	return Obj;
}

int Sk_Destructor(stack* Obj)
{
	if (Obj == NULL)
	{
		return STACK_NULL_OBJECT;
	}

	if (Obj->ptr_body != NULL)
	{
		free(Obj->ptr_body);
	}

	free(Obj);

	return STACK_OK;
}

int Change_Capacity(stack* Obj)
{
	if (Obj == NULL)
	{
		return STACK_NULL_OBJECT;
	}

	Obj->ptr_body = (type_el*)realloc(Obj->ptr_body, Obj->size + 1);
	if (Obj->ptr_body == NULL)
	{
		stack_overflow = true;
		return STACK_NO_MEMORY;
	}

	++Obj->size;
	++Obj->capacity;

	return STACK_OK;
}

int Sk_Print(stack* Obj)
{
	int error = Verifier(Obj);
	if (error != STACK_OK)
	{
		return error;
	}

	printf("\nSTACK\nSTACK_PTR = %p\n\tstack_size = %u\n\tstack_capacity = %u\n\tStack top: %f\n",
		Obj, Obj->size, Obj->capacity, Obj->ptr_body[Obj->size - 1]);
	
	return STACK_OK;
}

int Sk_Push(stack* Obj, type_el elem)
{
	if (Obj == NULL)
	{
		return STACK_NULL_OBJECT;
	}

	if (Obj->size == Obj->capacity)
	{
		int res_ch = Change_Capacity(Obj);
		if (res_ch != STACK_OK)
		{
			return res_ch;
		}
	}

	Obj->ptr_body[Obj->size] = elem;
	++Obj->size;
	
	return STACK_OK;
}

type_el Sk_Pop(stack* Obj)
{
	assert(Obj != NULL);

	if (Obj->size == 0)
	{
		stack_underflow = true;
		return STACK_NO_MEMORY;
	}

	type_el el_pop = Obj->ptr_body[Obj->size - 1];

	Obj->ptr_body = (type_el*)realloc(Obj->ptr_body, Obj->size - 1);
	assert(Obj->ptr_body != NULL || Obj->size == 1);

	--Obj->size;	

	return el_pop;
}

int Verifier(stack* Obj)
{
	if (Obj == NULL)
	{
		return STACK_NULL_OBJECT;
	}
	if (Obj->ptr_body == NULL)
	{
		return STACK_NO_MEMORY;
	}
	if (Verifier_El(Obj) != STACK_OK)
	{
		return INVALID_DATA;
	}
	if (stack_underflow == true)
	{
		return STACK_UNDERFLOW;
	}
	if (stack_overflow == true)
	{
		return STACK_OVERFLOW;
	}
	if (Obj->size > Obj->capacity)
	{
		return CAPACITY_SMALLER_THAN_SIZE;
	}
	if (Obj->front_canary != CANARY)
	{
		return STACK_UNDERFLOW;
	}
	if (Obj-> back_canary != CANARY)
	{
		return STACK_OVERFLOW;
	}

	return STACK_OK;
}

int Verifier_El(stack* Obj)
{
	assert(Obj != NULL);

	if (Obj->size == 0)
	{
		return STACK_NO_MEMORY;
	}
	else
	{
		for (size_t i = 0; i < Obj->size - 1; ++i)
		{
			if (!isfinite(Obj->ptr_body[i]))
			{
				return INVALID_DATA;
			}
		}
	}

	return STACK_OK;
}

void Sk_Dump(stack* Obj)
{
	assert(Obj != NULL);

	int error = Verifier(Obj);

	switch (error) {
	case STACK_OK:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
				 "STACK_PTR: %p\n"
				"\tstack_size: %u\n"
				"\tstack_capacity: %u\n"
				"\tstack_ptr_body: %p\n\n"
				"\tStack elements:\n",
				error, Obj, Obj->size, Obj->capacity, Obj->ptr_body);

		// Stack elements
		for (size_t i = 0; i < Obj->size; ++i)
		{
			put_log("\t\t*(Sk_Obj + %u) = %f\n\n", i, Obj->ptr_body[i]);
		}
		put_log("FRONT_CANARY: %llx\n", Obj->front_canary);
		put_log("BACK_CANARY: %llx\n", Obj->back_canary);
		put_log("\n\n");

		return;
	case STACK_NULL_OBJECT:
		// Main information about stack
		put_log("|STACK_STATUS: %d|\n"
			"STACK_PTR: %p\n",
			error, Obj);
		put_log("\n\n");

		return;
	case STACK_NO_MEMORY:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
				 "STACK_PTR: %p\n"
				"\tstack_size: %u\n"
				"\tstack_capacity: %u\n",
			error, Obj, Obj->size, Obj->capacity);
		put_log("\n\n");

		return;
	case INVALID_DATA:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
			"STACK_PTR: %p\n"
			"\tstack_size: %u\n"
			"\tstack_capacity: %u\n"
			"\tstack_ptr_body: %p\n\n"
			"\tStack elements:\n\n\n",
			error, Obj, Obj->size, Obj->capacity, Obj->ptr_body);

		return;
	case STACK_UNDERFLOW:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
			"STACK_PTR: %p\n"
			"\tstack_size: %u\n"
			"\tstack_capacity: %u\n"
			"\tstack_ptr_body: %p\n",
			error, Obj, Obj->size, Obj->capacity, Obj->ptr_body);

		put_log("FRONT_CANARY: %llx\n\n\n", Obj->front_canary);

		return;
	case STACK_OVERFLOW:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
			"STACK_PTR: %p\n"
			"\tstack_size: %u\n"
			"\tstack_capacity: %u\n"
			"\tstack_ptr_body: %p\n",
			error, Obj, Obj->size, Obj->capacity, Obj->ptr_body);

		put_log("BACK_CANARY: %llx\n\n\n", Obj->back_canary);

		return;
	case CAPACITY_SMALLER_THAN_SIZE:
		// Main information about stack
		put_log("|STACK_STATUS: %d| \n"
			"STACK_PTR: %p\n"
			"\tstack_size: %u\n"
			"\tstack_capacity: %u\n"
			"\tstack_ptr_body: %p\n\n",
			error, Obj, Obj->size, Obj->capacity, Obj->ptr_body);

		// Stack elements
		put_log("\tElements inside the stack:\n");
		for (size_t i = 0; i < Obj->capacity; ++i)
		{
			put_log("\t\t*(Sk_Obj + %u) = %f\n", i, Obj->ptr_body[i]);
		}
		put_log("\tElements outside the stack:\n");
		for (size_t i = Obj->capacity; i < Obj->size; ++i)
		{
			put_log("\t\t*(Sk_Obj + %u) = %f\n", i, Obj->ptr_body[i]);
		}
		put_log("\n\n");

		return;
	default:
		return;
	}
}


#endif _STACK_
