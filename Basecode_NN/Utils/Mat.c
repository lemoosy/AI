#include "Mat.h"

Mat* Mat_New(int w, int h)
{
	assert((w > 0) && (h > 0));

	Mat* mat = (Mat*)calloc(1, sizeof(Mat));
	assert(mat);

	mat->w = w;
	mat->h = h;

	mat->values = (data*)calloc(w * h, sizeof(data));
	assert(mat->values);

	return mat;
}

Mat* Mat_Copy(Mat* m)
{
	if (!m) return NULL;

	Mat* res = Mat_New(m->w, m->h);

	memcpy(res->values, m->values, sizeof(data) * m->w * m->h);

	return res;
}

void Mat_Copy2(Mat* m, Mat* res)
{
	memcpy(res->values, m->values, sizeof(data) * m->w * m->h);
}

void Mat_Destroy(Mat* m)
{
	if (!m) return;

	free(m->values);
	free(m);
}

data Mat_Get(Mat* m, int i, int j)
{
	assert((0 <= i) && (i < m->w));
	assert((0 <= j) && (j < m->h));

	return m->values[m->w * j + i];
}

void Mat_Set(Mat* m, int i, int j, data value)
{
	assert((0 <= i) && (i < m->w));
	assert((0 <= j) && (j < m->h));

	m->values[m->w * j + i] = value;
}

void Mat_Print(Mat* m)
{
	if (m)
	{
		for (int j = 0; j < m->h; j++)
		{
			for (int i = 0; i < m->w; i++)
			{
				printf("%.2f ", Mat_Get(m, i, j));
			}

			putchar('\n');
		}
	}
	else
	{
		printf("matrix = NULL \n");
	}
}

void Mat_Operation(Mat* m1, Mat* m2, data (*funcOperation)(data, data))
{
	assert((m1->w == m2->w) && (m1->h == m2->h));

	int size = m1->w * m2->h;

	data* v1 = m1->values;
	data* v2 = m2->values;

	for (int i = 0; i < size; i++)
	{
		v1[i] = funcOperation(v1[i], v2[i]);
	}
}

void Mat_Scale(Mat* m, data s)
{
	int size = m->w * m->h;

	data* v = m->values;

	for (int i = 0; i < size; i++)
	{
		v[i] *= s;
	}
}

Mat* Mat_Multiply(Mat* m1, Mat* m2)
{
	int w = m1->w;
	int h = m2->h;
	
	assert(w == h);

	Mat* res = Mat_New(m2->w, m1->h);

	int idx = 0;

	for (int j = 0; j < m1->h; j++)
	{
		for (int i = 0; i < m2->w; i++)
		{
			data sum = (data)0;

			for (int k = 0; k < w; k++)
			{
				sum += Mat_Get(m1, k, j) * Mat_Get(m2, i, k);
			}

			res->values[idx] = sum;
			idx++;
		}
	}

	return res;
}

void Mat_Multiply2(Mat* m1, Mat* m2, Mat* res)
{
	int w = m1->w;
	int h = m2->h;

	assert(m1->w == m2->h);
	assert((res->w == m2->w) && (res->h == m1->h));

	int idx = 0;

	for (int j = 0; j < m1->h; j++)
	{
		for (int i = 0; i < m2->w; i++)
		{
			data sum = (data)0;

			for (int k = 0; k < w; k++)
			{
				sum += Mat_Get(m1, k, j) * Mat_Get(m2, i, k);
			}

			res->values[idx] = sum;
			idx++;
		}
	}
}

void Mat_Compose(Mat* m, data (*funcCompose)(data))
{
	int size = m->w * m->h;

	data* v = m->values;

	for (int i = 0; i < size; i++)
	{
		v[i] = funcCompose(v[i]);
	}
}

void Mat_Compose2(Mat* m, data (*funcCompose)(data), Mat* res)
{
	int size = m->w * m->h;

	data* v1 = m->values;
	data* v2 = res->values;

	for (int i = 0; i < size; i++)
	{
		v2[i] = funcCompose(v1[i]);
	}
}

Mat* Mat_Transpose(Mat* m)
{
	int w = m->w;
	int h = m->h;

	Mat* res = Mat_New(h, w);

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			Mat_Set(res, j, i, Mat_Get(m, i, j));
		}
	}

	return res;
}

void Mat_Randomize(Mat* m, data a, data b)
{
	int size = m->w * m->h;

	data* v = m->values;

	for (int i = 0; i < size; i++)
	{
		v[i] = Data_Random(a, b);
	}
}

bool Mat_Equal(Mat* m1, Mat* m2, data epsilon)
{
	assert((m1->w == m2->w) && (m1->h == m2->h));

	int size = m1->w * m2->h;

	data* v1 = m1->values;
	data* v2 = m2->values;

	for (int i = 0; i < size; i++)
	{
		if (fabsf(v1[i] - v2[i]) > epsilon)
		{
			return false;
		}
	}

	return true;
}
