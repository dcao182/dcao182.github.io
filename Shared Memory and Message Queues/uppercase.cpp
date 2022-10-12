#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	// The string length
	int len = -1;
	
	// The pointer for the capitalized string buffer
	char* capStringBuff = NULL;
		
	// Sanity checks
	if(argc < 2)
	{
		fprintf(stderr, "Please provide a string you would like to capitalize!\n");
		exit(-1);
	}

	// Get the string length
	len = strlen(argv[1]);
		
	// Create a buffer to store the string (need the +1 for the Null terminator)
	capStringBuff = new char[len + 1];
	
	// Make sure the memory allocation succeeded	
	if(!capStringBuff)
	{
		fprintf(stderr, "Could not allocate the string buffer!\n");
		exit(-1);
	}

	// Capitalize each letter
	for(int index = 0; index < len; ++index)
	{
		capStringBuff[index] = toupper(argv[1][index]);
	}
	
	// NULL terminate the string
	capStringBuff[len] = '\0';
	
	// Print the string	
	fprintf(stderr, "The capitalized string is %s\n", capStringBuff);
	
	// Deallocate the heap memory
	delete[] capStringBuff;
	
	return 0;

}
