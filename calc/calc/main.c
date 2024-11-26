#include <stdio.h>

#include "laba.h"

int main()
{
	int N = clipping_expressions();
	post_notation(N);
	calculating_value();

	return 0;
}