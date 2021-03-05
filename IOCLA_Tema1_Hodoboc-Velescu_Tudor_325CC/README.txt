1. iocla_printf
The function simulates the capability of standard printf function. It gets at
least one argument, the format of the output. After that, it searches for
conversion specificators. If there are any, the specific part will be replaced
by the current argument in a human-readable format, an array of characters. The
argument is first converted to the specific type and transposed in string form.
The special character "%" is only printed if it's preceded by itself. When the
search is over and there are no specificators, the output is printed to stdout
using the auxiliary function write_stdout given. The function returns the
number of characters printed.

2. reversedString
This is an auxiliary function created to reverse the order of a the elements of
a char array. It has 2 arguments, the original string and the new location
where the elements are to be placed. The original array is traversed backwards
and every character is put at the end of the new string. The function returns
the new string created.

3. intPozToString
This function converts an integer positive number to a string. It takes each
digit from the end of the number and puts its representative character to the
end of a temporary array. After there are no more digits in the number, the
array is converted and returned.

4. intNegToString
This function converts an integer negative number to a string. It takes each
digit from the end of the number and puts its representative to the end of a
temporary array. After there are no more digits in the number, the minus sign
is also added at the end. The array is converted and returned.

5. intToString
This function converts an integer number to a string. If the number is positive
the function calls the auxiliary intPozToString function, otherwise it calls
intNegToString and returns the output of the auxiliary function.

6.unsignedToString
As the names implies, the function gets an unsigned number as the argument and
returns the string format of it. It takes each digit and adds it at the end of
a string. After that, the string is reversed and returned.

7. hexToString
The function gets an unsigned number as the argument. Following the algorithm,
it gets the rest from repeated division to 16 and adds at the end of an array
of characters. The resulted string is reversed and returned.
