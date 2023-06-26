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

void Mat_Add(Mat* m1, Mat* m2)
{
	assert((m1->w == m2->w) && (m1->h == m2->h));

	int size = m1->w * m2->h;

	data* v1 = m1->values;
	data* v2 = m2->values;

	for (int i = 0; i < size; i++)
	{
		v1[i] += v2[i];
	}
}

void Mat_Sub(Mat* m1, Mat* m2)
{
	assert((m1->w == m2->w) && (m1->h == m2->h));

	int size = m1->w * m2->h;

	data* v1 = m1->values;
	data* v2 = m2->values;

	for (int i = 0; i < size; i++)
	{
		v1[i] -= v2[i];
	}
}

void Mat_Product(Mat* m1, Mat* m2)
{
	assert((m1->w == m2->w) && (m1->h == m2->h));

	int size = m1->w * m2->h;

	data* v1 = m1->values;
	data* v2 = m2->values;

	for (int i = 0; i < size; i++)
	{
		v1[i] *= v2[i];
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

void Mat_Scale2(Mat* m, data s, Mat* res)
{
	assert((m->w == res->w) && (m->h == res->h));

	int size = m->w * m->h;

	data* v1 = m->values;
	data* v2 = res->values;

	for (int i = 0; i < size; i++)
	{
		v2[i] = v1[i] * s;
	}
}

data Mat_Sum(Mat* m)
{
	int size = m->w * m->h;

	data res = (data)0;
	data* v = m->values;

	for (int i = 0; i < size; i++)
	{
		res += v[i];
	}

	return res;
}

Mat* Mat_Multiply(Mat* m1, Mat* m2)
{
	int w1 = m1->w;
	int h1 = m1->h;
	int w2 = m2->w;
	
	assert(w1 == m2->h);

	Mat* res = Mat_New(w2, h1);

	for (int j = 0; j < h1; j++)
	{
		for (int i = 0; i < w2; i++)
		{
			data sum = (data)0;

			for (int k = 0; k < w1; k++)
			{
				sum += Mat_Get(m1, k, j) * Mat_Get(m2, i, k);
			}

			Mat_Set(res, i, j, sum);
		}
	}

	return res;
}

void Mat_Multiply2(Mat* m1, Mat* m2, Mat* res)
{
	int w1 = m1->w;
	int h1 = m1->h;
	int w2 = m2->w;

	assert(w1 == m2->h);
	assert((res->w == w2) && (res->h == h1));

	for (int j = 0; j < h1; j++)
	{
		for (int i = 0; i < w2; i++)
		{
			data sum = (data)0;

			for (int k = 0; k < w1; k++)
			{
				sum += Mat_Get(m1, k, j) * Mat_Get(m2, i, k);
			}

			Mat_Set(res, i, j, sum);
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
	assert((m->w == res->w) && (m->h == res->h));

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

void Mat_Randomize(Mat* m, data a, data b, data (*funcRandom)(data, data))
{
	int size = m->w * m->h;

	data* v = m->values;

	for (int i = 0; i < size; i++)
	{
		v[i] = funcRandom(a, b);
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
