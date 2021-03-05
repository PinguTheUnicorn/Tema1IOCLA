#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//function that reverses an array of char
static char* reverseString(char* stringToReverse, char** location) {
	int i, size = strlen(stringToReverse);

	/*takes each character from the back of the initial array
	  and it puts it to the begginnig of the first one */
	for(i = 0; i < size; i++) {
		(*location)[i] = stringToReverse[size - 1 - i];
	}

	//it returns the array created
	return *location;
}

//function that creates the string form of a given integer positive number
static char* intPozToString(int number) {
	int i = 0;
	char *converted, *reverse;

	//memory allocation
	converted = (char *) calloc(15, sizeof(char));
	reverse = (char *) calloc(15, sizeof(char));

	/*takes each figure from the number and
	  puts it at the end of the first string*/
	while(number != 0) {
		reverse[i] = number % 10 + 48;
		i++; //increments the index for the next element of the string
		number = number / 10; //last figure is cut from the number
	}

	//the string obtained is then reversed
	reverseString(reverse, &converted);

	//the memory for the first string is freed
	free(reverse);

	//the string format of the number given is returned
	return converted;
}

//function that creates the string form of a given integer negative number
static char* intNegToString(int number) {
	int i = 0;
	char *converted, *reverse;

	//memory allocation
	converted = (char *) calloc(15, sizeof(char));
	reverse = (char *) calloc(15, sizeof(char));

	/*takes each figure from the number and
	  puts it at the end of the first string*/
	while(number != 0) {
		reverse[i] = (number % 10)  * (-1) + 48;
		i++; //increments the index for the next element of the string
		number = number / 10; //last figure is cut from the number
	}

	/*puts the '-' sign at the end so it will be
	  at the beginning when it's reversed*/
	reverse[i] = '-';

	//the string is reversed
	reverseString(reverse, &converted);

	//freeing the memory
	free(reverse);

	//the string format of the number given is returned
	return converted;
}

//function that creates the string form of a given integer number
static char* intToString(int number) {
	//if the number is negative
	if(number < 0) {
		//it calls the function for negative numbers
		return intNegToString(number);
	}
	else {
		//if it's positive, it calls the one for positive numbers
		return intPozToString(number);
	}
}

//function that creates the string form of a given unsigned number
static char* unsignedToString(unsigned number) {
	int i = 0;
	char *converted, *reverse;

	//memory allocation
	converted = (char *) calloc(15, sizeof(char));
	reverse = (char *) calloc(15, sizeof(char));

	/*takes each figure from the number and
	  puts it to the end of the first string*/
	while(number != 0) {
		reverse[i] = number % 10 + 48;
		i++; //increments the index for the next element of the string
		number = number / 10; //the last figure is cut from the number
	}

	//the string is reversed
	reverseString(reverse, &converted);

	//memory freed
	free(reverse);

	//the string format of the number given is returned
	return converted;
}

/*function that returns the string form of an
  unsigned number in its hexadecimal form*/
static char* hexToString(unsigned number) {
	int i = 0;
	char *reverse, *converted;

	//memory allocation
	reverse = (char *) calloc(15, sizeof(char));
	converted = (char *) calloc(15, sizeof(char));

	while(number != 0) {
		//takes the rest from dividing the number to 16
		int cifra = number % 16;

		//if it's smaller than 10, it's represented by a digit
		if(cifra < 10) {
			/*the character representing the digit
			  is put at the end of the string*/
			reverse[i] = cifra + 48;
			i++; //increments the index for the next element of the string
		}
		else {
			/*otherwise, the letter representing the
			  number is added at the end pf the string*/
			reverse[i] = cifra + 87;
			i++; //increments the index for the next element of the string
		}

		//the number is divided by 16, according to the algorithm
		number = number / 16;
	}

	//the string obtained is reversed
	reverseString(reverse, &converted);

	//memory freed
	free(reverse);

	//the resulted string is returned
	return converted;
}

//function that simulates printf's functionality from stdio
int iocla_printf(const char *format, ...)
{
	//the list of arguments is declared
	va_list args;
	va_start(args, format);

	//delcaring the index of the last position where '%' was found
	int i = 0;
	//the format is copied in order to be modified for output
	char *search = (char *) malloc((strlen(format) + 1) * sizeof(char));
	strcpy(search, format);

	//it modifies the string as long as there are '%' characters not checked
	while(strstr(search + i, "%") != NULL) {
		//it retains the addres where '%' is found
		char *poz = strstr(search + i, "%");
		//updates the last position where '%' was found
		i = poz - search;
		//the string that will overwrite the format is declared
		char *argument;

		//checks the conversion specificator
		switch(poz[1]) {
			//if it's '%', the specificator will be overwritten by '%'
			case '%': {
				argument = (char *) calloc(2, sizeof(char));
				argument[0] = '%';

				break;
			}

			//if it's 'd', the specificator will be overwritten by an integer
			case 'd': {
				//substract the argument, converted to integer
				int number = va_arg(args, int);

				//creates the string that will overwrite the specificator
				argument = intToString(number);

				break;
			}

			//if it's 'u', the specificator will be overwrtitten by an unsigned
			case 'u': {
				//substarct the argument, converted to unsigned
				unsigned number = va_arg(args, unsigned);

				//creates the string that will be overwrite the specificator
				argument = unsignedToString(number);

				break;
			}

			/*if it;s 'x', the specificator will be
			  overwritten by an hexadecimal number*/
			case 'x': {
				//substracts the argument, converted to unsigned
				unsigned int number = va_arg(args, unsigned int);

				//creates the string that will overwrite the specificator
				argument = hexToString(number);

				break;
			}

			//if it;s 'c', the specificator will be overwrtitten by a character
			case 'c': {
				//creates the string that will overwrite the specificator
				argument = (char *) calloc(2, sizeof(char));
				//substracts the character, converted to integer
				argument[0] = va_arg(args, int);

				break;
			}

			/*if it's 's', the specificator will be
			  overwritten by a character array*/
			case 's': {
				//substracts the argument, converted to an address of a string
				argument = va_arg(args, char *);

				break;
			}
		}

		//an auxiliary array is created
		char *aux = (char *) malloc((strlen(search) + 1 +
											strlen(search)) * sizeof(char));

		/*the first i characters that are before the
		  specificator are copied in the auxiliary string*/
		strncpy(aux, search, i);
		//the argument is put in the string
		strcpy(aux + i, argument);
		//the next position from which the search will continue is updated
		i += strlen(argument);
		//the rest of the string is copied after the argument
		strcpy(aux + i, poz + 2);

		//the memory for the search string is reallocated to match the new size
		search = (char *) realloc(search, (strlen(aux) + 1) * sizeof(char));
		//the string is copied from the auxiliary array to the search one
		strcpy(search, aux);
		//freed memory
		free(aux);
	}

	//when no specificator is found anymore, the final form of the displayed array is created
	const char* final = search;

	//the string is written to stdout by the function given in the skell
	write_stdout(final, strlen(final));

	//the lenght of of the printed string is returned
	return strlen(final);
}
