// Rotate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"
#include "math.h"
int main (int argc, char **argv)
{
	IplImage *src = 0;
	IplImage *dst = 0;

	/* the first command line parameter must be image file name */
	if ((argc == 2) && (src = cvLoadImage (argv[1], -1)) != 0)
	{
		int delta = 1;
		int angle = 30;
		int opt = 0;		// 1�� ��ת������
		// 0:  ������ת
		double factor;

		dst = cvCloneImage (src);
		cvNamedWindow ("src", 1);
		cvShowImage ("src", src);

		for (;;)
		{
			float m[6];
			// Matrix m looks like:
			//
			// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
			// [ m3  m4  m5 ]       [ A21  A22   b2 ]
			//
			CvMat M = cvMat (2, 3, CV_32F, m);
			int w = src->width;
			int h = src->height;
			if (opt)		// ��ת������
				factor = (cos (angle * CV_PI / 180.) + 1.0) * 2;
			else			//  ������ת
				factor = 1;
			m[0] = (float) (factor * cos (-angle * 2 * CV_PI / 180.));
			m[1] = (float) (factor * sin (-angle * 2 * CV_PI / 180.));
			m[3] = -m[1];
			m[4] = m[0];
			// ����ת��������ͼ���м�
			m[2] = w * 0.5f;
			m[5] = h * 0.5f;
			//  dst(x,y) = A * src(x,y) + b
			cvZero (dst);
			cvGetQuadrangleSubPix (src, dst, &M);
			cvNamedWindow ("dst", 1);
			cvShowImage ("dst", dst);
			if (cvWaitKey (1) == 27)	//ESC
				break;
			angle = (int) (angle + delta) % 360;
		}			// for-loop
	}
	return 0;
}


