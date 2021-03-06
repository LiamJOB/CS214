#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Calculates a value (c) based on the input parameters (a, b) and prints
 * out the result.
 *
 * @param a
 *     Input parameter a.
 *
 * @param b
 *     Input parameter b.
 */
void one(const int a, const int b) {
  int c = (a * a) + (b * b);
  printf("%d^2 + %d^2 = %d\n", a, b, c);
}

/**
 * Checks if the input parameter is a passing grade and prints out if
 * the grade is passing.
 *
 * @param grade
 *     The grade to check.
 */
void two(const char *grade) {
  // you may find the atoi function useful
	//atoi the string into an int
  if (atoi(grade) > 70)
    printf("%d passed!\n", atoi(grade));
  else
    printf("%d not passed!\n", atoi(grade));
}

/**
 * Assigns a pointer (int *p) the value of a stack variable (int x).
 */
void three() {
  int x = 4;
  //needed to malloc *p first
  int *p = malloc(sizeof(int));
  *p = x;

  printf("The value of p is: %d\n", *p);

  free(p);
}

/**
 * Prints out a specific message based on if the number is
 * between 0 and 1 (exclusive).
 *
 * @param value
 *     Value to test.
 */
void four(const float value) {

	//had to correct the if statement
	if (value > 0 && value < 1)
    printf("The value is between zero and one.\n");
  else
    printf("The value is not between zero and one.\n");
}

/**
 * Prints out a specific message based on if the two input parameters
 * are equal.
 *
 * @param x
 *     First input parameter.
 *
 * @param y
 *     Second input parameter.
 */
void five(const int *x, const int *y) {
	//added pointers to x and y
	if (*x == *y)
		printf("x and y are equal.\n");
	else{
		printf("x and y are different.\n");
	}
}


/**
 * Returns a new pointer (float *p) which contains the value of the
 * input pointer (int *x).
 *
 * @param x
 *     Input parameter, whose value will be returned as a (float *).
 *
 * @returns
 *     A new pointer, allocated on the heap and not freed, that
 *     contains the value of the input parameter.
 */
float *six(const int *x) {
	//Needed to malloc the size of float
	float *p = malloc(sizeof(float));
	*p = *x;
	return p;
}

/**
 * Takes an input a and checks whether a is an alphabet, it can be
 * both uppercase and lowercase
 *
 * @param a
 *     Input parameter a, which is a char*
 *
 */
void seven(const char *a)
{
	//need to check if the char is A-Z OR a-z
	if ((*a >= 'A' && *a <= 'Z') || (*a >= 'a' && *a <= 'z'))
	{
		printf("a is a letter.\n");
	}
  else{
	  printf("a is not a letter.\n");
  }
}

/**
 * Constructs a C-string, character by character, and prints out the full
 * string "Hello".
 */
void eight() {
	//needed to malloc an etra byte for null terminator
	char *s = malloc(6);
	s[0] = 'H';
	s[1] = 'e';
	s[2] = 'l';
	s[3] = 'l';
	s[4] = 'o';
	s[5] = '\0';
	printf("%s\n", s);

	free(s);
}

/**
 * Assigns a pointer (float *p) a numeric value (12.5).
 */
void nine() {
	//needed to malloc the size of a float
	float *p = malloc(sizeof(float));
	*p = 12.5;

	printf("The value of p is: %f\n", *p);
}

/**
 * Reset the value of x to zero.
 *
 * @param x
 *     Pointer to reset to 0.
 */

//needed to make x a pointer
void ten(int *x) { *x = 0; }

/**
 * Concatenates "Hello " and the parameter str, which is guaranteed to be a
 * valid c string, and
 * prints the concatenated string.
 */
void eleven(const char *str) {

	//created a s array of size 100, copy and cat the two strings, and print
	char s[100];
	strcpy(s, "Hello ");
	strcat(s, str);
	printf("%s\n", s);
}

/**
 * Creates an array of values containing the values {0.0, 0.1, ..., 0.9}.
 */
void twelve() {
	//created an array of size 10
	float values[10];

	int i, n = 10;
	for (i = 0; i < n; i++)
	{
		values[i] = (float)i / n;
	}

	//print all the values up to the last one, then print last one outside of loop
	for (i = 0; i < n-1; i++)
	{
		printf("%f ", values[i]);
	}

	printf("%f ", values[9]);
	printf("\n");


}

/**
 * Creates a 2D array of values and prints out the values on the diagonal.
 */
void thirteen(int a) {
  int **values;

  int i, j;

  //corrected the malloc for values
  values = malloc(sizeof(int*) * 10);

  //needed to malloc enough space for part of the array
  for (i = 0; i < 10; i++)
  {
	  values[i] = malloc(sizeof(int) * 10);
  }


  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      values[i][j] = i * j * a;

  //print all the values from 0-9, then print 9
  for (i = 0; i < 9; i++)
  {
    printf("%d ", values[i][i]);
  }
  printf("%d ", values[9][9]);
  printf("\n");

  //needed to free all of the entries of values
  for (i = 0; i < 10; i++)
  {
	  free(values[i]);
  }
  //finally free value
  free(values);
}

/**
 * Prints out a specific string based on the input parameter (s).
 *
 * @param s
 *     Input parameter, used to determine which string is printed.
 */

void fourteen(const char *s) {
	//create a temporary integer which is used to compare strings
	int temp = 2;

	//compares the string to orange. If true, change value of temp
	if(strcmp(s, "orange") == 0)
	{
		temp = 1;
	}

	//compares the string to blue. If true, change value of temp
	if(strcmp(s, "blue") == 0)
	{
		temp = 0;
	}

	switch (temp)
	{
		case 0:
			printf("Orange and BLUE!\n");
			break;

		case 1:
			printf("ORANGE and blue!\n");
			break;

		default:
			printf("orange and blue!\n");
			break;
	}
}


/**
 * Prints out a specific string based on the input parameter (value).
 *
 * @param value
 *     Input parameter, used to determine which string is printed.
 */
void fifteen(const int value)
{
	//switch statement was missing breaks after each case
	switch (value)
	{
	case 1:
		printf("You passed in the value of one!\n");
		break;

	case 2:
		printf("You passed in the value of two!\n");
		break;

	default:
		printf("You passed in some other value!\n");
		break;
	}
}

/**
 * Returns a newly allocated string on the heap with the value of "Hello".
 * This should not be freed.
 *
 * @returns
 *     A newly allocated string, stored on the heap, with the value "Hello".
 */
char *sixteen() {

	//similar to eight except print and free are done in main
	char *s = malloc(6);
	s[0] = 'H';
	s[1] = 'e';
	s[2] = 'l';
	s[3] = 'l';
	s[4] = 'o';
	s[5] = '\0';
	return s;
}

/**
 * Prints out the radius of a circle, given its diameter.
 *
 * @param d
 *     The diameter of the circle.
 */
void seventeen(const int d)
{
	//needed to cast the int as a float
	printf("The radius of the circle is: %f.\n", (float) d / 2);
}

/**
 * Manipulates the input parameter (k) and prints the result.
 *
 * @param k
 *     The input parameter to manipulate.
 */
void eighteen(const int k)
{
	//I set k to i to work with the integers
	int i = k;
	i = i * i;
	i +=i;
	i *= i;
	i -= 1;
  printf("Result: %d\n", i);
}

