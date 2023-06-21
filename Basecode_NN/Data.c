#include "Data.h"

Data* Data_Import(char* path)
{
	FILE* file = fopen(path, "r");

	if (file == NULL)
	{
		printf("ERROR - Data_Import() \n");
		printf("ERROR - fopen() \n");
		abort();
	}

	Data* data = (Data*)calloc(1, sizeof(Data));
	assert(data);
	
	char buffer[CHAR_PER_LINE + 1] = { 0 };

	fgets(buffer, CHAR_PER_LINE, file);

	printf("%s \n", buffer);

	return data;
}

void Data_Destroy(Data* data)
{
	if (!data) return;

	free(data->samples);
	free(data);
}

void Data_Print(Data* data)
{

}
