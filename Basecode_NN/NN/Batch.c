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

	data* values;

	for (int i = 0; i < size; i++)
	{
		samples[i].X = Mat_Create(1, xSize);
		values = samples[i].X->values;

		for (int j = 0; j < xSize; j++)
		{
			fscanf(file, "%f", &values[j]);
		}

		samples[i].Y = Mat_Create(1, ySize);
		values = samples[i].Y->values;

		for (int j = 0; j < ySize; j++)
		{
			fscanf(file, "%f", &values[j]);
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
		Mat_Destroy(samples[i].X);
		Mat_Destroy(samples[i].Y);
	}

	free(samples);
	free(batch);
}
