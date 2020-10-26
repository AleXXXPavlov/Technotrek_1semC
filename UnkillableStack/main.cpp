//* Main.c file for the project - implementation of the non - killable stack */
#include "stack.h"

int main()
{
	stack* sk1 = Sk_Creator();

	type_el list[] = { 1.34,2.0,-3.902,4.33333,5.34,-6.2,-7.54,8.35,9.542 };

	for (size_t i = 0; i < 9; ++i)
	{
		Sk_Push(sk1, list[i]);
	}

	printf("top - %f\n", Sk_Pop(sk1));
	printf("top - %f\n", Sk_Pop(sk1));

	int res_print = Sk_Print(sk1);
	if (res_print != STACK_OK)
	{
		return STACK_OK;
	}

	Sk_Dump(sk1);
	Sk_Destructor(sk1);
	return 0;
}
