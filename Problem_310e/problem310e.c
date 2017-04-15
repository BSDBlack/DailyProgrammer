// problem310e.c
//

// date: 12.04.2017
// author: bsdblack

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define inputsize 1024

uint8_t count_entries(char *, char);
char** split(char *, char);
char** draw(char **, int, int);
int contains(int, int *, int);

int main(void)
{
	/* variable declaration */
	char input[inputsize];
	char **table;
	char **map;
	uint8_t entries, i;
	int number_row;
	
	/* read studentnames and count of students per row */
	fgets(input, inputsize, stdin);
	input[strlen(input)-1] = '\0';
	entries = count_entries(input, ';');
	scanf("%d", &number_row);

	if( number_row > (entries - 1) )
	{
		printf("Too much students per row. Aborting.\n");
		return 1;
	}
	
	table = split(input, ';');
	map = draw(table, entries, number_row);
	
	for(i = 0; i < entries; ++i)
	{
		printf("%s\n", *(map+i));
		free(*(table+i));
		free(*(map+i));
	}
		
	free(table);
	free(map);
	
	return 0;
}

uint8_t count_entries(char *str, char c)
{
	/* variable declaration */
	uint8_t count = 0;
	
	while('\0' != *str)
	{
		if(c == *str)
		{
			/* if marker found, increase entries */
			++count;
		}
		++str;
	}
	
	return count;
}

char** split(char *str, char c)
{
	/* variable declaration */
	char **result, **temp, *new_string;
	uint8_t entries = count_entries(str, c);
	uint8_t i;
	uint32_t substr, length;
	
	length = strlen(str);
	
	/* allocate memory and copy string for processing */
	new_string = (char *) malloc( sizeof(char) * length );
	memcpy(new_string, str, length);
	
	/* allocate memory for results table */
	result = (char **) malloc( sizeof(char *) * entries );
	
	temp = result;
	
	
	for(i = 0; i < entries; ++i)
	{
		/* get span until next ; */
		substr = strcspn(new_string, ";");
		/* acquire memory */
		*(temp+i) = (char *) malloc( sizeof(char) * substr);
		/* copy until next ; into new memory */
		memcpy( *(temp+i), new_string, substr);
		/* add string end */
		*(*(temp+i)+substr+1) = '\0';
		
		/* move contents to new beginning */
		memmove(new_string, new_string+(substr+1), (length-substr));
	}
	
	free(new_string);
	
	return result;
}

char** draw(char **table, int entries, int rowsize)
{
	/* variable declaration */
	char **result_table;
	int *drawn;
	uint8_t i, j, temp;
	uint32_t complete_length = 0;
	char line[] = {" > "};
	char entry_end[] = {";"};
	
	/* allocate memory for resulting table */
	result_table = (char **) malloc( sizeof(char *) * entries);
	
	/* generate list for each student */
	for(i = 0; i < entries; ++i)
	{
		/* initalize row */
		complete_length = strlen(*(table+i)) + 3;
		*(result_table+i) = (char *) calloc(sizeof(char) * complete_length + 3, sizeof(char));
		strcat(*(result_table+i), *(table+i));
		strcat(*(result_table+i), line);
				
		/* allocate memory for drawn array */
		drawn = (int *) calloc(rowsize + 1, sizeof(int));
		*(drawn+rowsize) = i + 1;
		
		for(j = 0; j < rowsize; ++j)
		{
			do {
				/* generate randomnumber between 1 and rowsize */
				temp = (rand() % entries) +1;
			} while(1 == contains(temp, drawn, rowsize + 1));
			
			/* add drawn number to already drawn */
			*(drawn+j) = temp;
			
			/* compute length of entry and allocate memory */
			complete_length += strlen(*(table + ( *(drawn+j) - 1)));
			*(result_table+i) = (char *) realloc(*(result_table+i), sizeof(char) * ++complete_length);
			
			/* concatenate existing memory contents with entry */
			strcat(*(result_table+i), *(table + ( *(drawn+j) - 1)));
			strcat(*(result_table+i), entry_end);
		}
		
		free(drawn);
	}
	
	return result_table;
}

int contains(int val, int *array, int size)
{
	/* variable declaration */
	uint8_t i;
	
	/* walk through array and search if element already exists */
	for(i = 0; i < size; ++i)
	{
		if(val == *(array+i))
		{
			/* return 1 if found */
			return 1;
		}
	}
	
	/* return -1 if not found */
	return -1;
}
