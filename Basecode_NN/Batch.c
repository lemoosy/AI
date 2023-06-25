#include "Batch.h"

Batch* Batch_Import(char* path)
{
	FILE* file = fopen(path, "r");

	if (file == NULL)
	{
		printf("ERROR - Batch_Import() \n");
		printf("ERROR - fopen() \n");
		abort();
	}

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
		samples[i].x = (data*)calloc(xSize, sizeof(data));
		assert(samples[i].x);

		for (int j = 0; j < xSize; j++)
		{
			fscanf(file, "%f", &(samples[i].x[j]));
		}

		samples[i].y = (data*)calloc(ySize, sizeof(data));
		assert(samples[i].y);

		for (int j = 0; j < ySize; j++)
		{
			fscanf(file, "%f", &(samples[i].y[j]));
		}
	}

	fclose(file);

	Batch* batch = (Batch*)calloc(1, sizeof(Batch));
	assert(batch);

	batch->size = size;
	batch->xSize = xSize;
	batch->ySize = ySize;
	batch->samples = samples;

	return batch;
}

void Batch_Destroy(Batch* batch)
{
	if (!batch) return;

	int size = batch->size;

	Sample* samples = batch->samples;

	for (int i = 0; i < size; i++)
	{
		free(samples[i].x);
		free(samples[i].y);
	}

	free(batch->samples);
	free(batch);
}
