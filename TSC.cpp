#include <iostream>
#include "TimeKeeper.h"


int main()
{
	int i = 0;
	{
		TimeKeeper keeper;
		for (int j = 0; j < 10000; j++)
		{
			i *= j;
		}
	}

	std::cin >> i;
	return 0;
}
