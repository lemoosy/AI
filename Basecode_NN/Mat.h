#pragma once

#include "Settings.h"

typedef float data;

typedef struct sMat
{
	int w, h;
	data** value;
}Mat;

Mat* Mat_New(int w, int h);
Mat* Mat_Copy(Mat* m);
void Mat_Destroy(Mat* m);

void Mat_Add(Mat* m1, Mat* m2);
void Mat_Sub(Mat* m1, Mat* m2);
Mat* Mat_Prd(Mat* m1, Mat* m2);
void Mat_Scale(Mat* m, data s);
