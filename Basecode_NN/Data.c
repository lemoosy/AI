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
	
	char* informations = (char*)calloc(CHAR_PER_LINE + 1, sizeof(char));
	assert(informations);
	fgets(informations, CHAR_PER_LINE, file);

	int size = 0;
	fscanf(file, "%d", &size);

	int xSize = 0;
	fscanf(file, "%d", &xSize);

	int ySize = 0;
	fscanf(file, "%d", &ySize);

	Sample* samples = (Sample*)calloc(size, sizeof(Sample));
	assert(samples);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			fscanf(file, "%f", &(samples[i].x[j]));
		}

		for (int j = 0; j < ySize; j++)
		{
			fscanf(file, "%f", &(samples[i].y[j]));
		}
	}

	fclose(file);

	Data* data = (Data*)calloc(1, sizeof(Data));
	assert(data);

	data->informations = informations;
	data->size = size;
	data->xSize = xSize;
	data->ySize = ySize;
	data->samples = samples;

	return data;
}

void Data_Destroy(Data* data)
{
	if (!data) return;

	free(data->samples);
	free(data->informations);
	free(data);
}
