/*
 * reverseFaculty.c
 *
 *  Created on: Oct 8, 2016
 *      Author: bsdblack
 */

/*
 * [2016-10-03] Challenge #286 [Easy] Reverse Factorial
 */

/*
 * int reverseFactorial(int number)
 *
 * int number - takes argument of number to test
 * returns - factorial, if none, -1
 */

int reverseFactorial(int number)
{
	// variable declaration
	int faculty = 1;
	int isFaculty = 1;

	// code
	do {
		++faculty;

		if(0 != number % faculty)
		{
			isFaculty = 0;
		}
		else
		{
			number /= faculty;
		}

	} while(1 == isFaculty && number >= faculty);

	if(0 == isFaculty)
	{
		faculty = -1;
	}

	return faculty;
}
