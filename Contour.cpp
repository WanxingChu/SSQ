///**************************************************
// * �������
// * ��Ҫ������
// *      cvFindContours
// *      cvDrawContours
// **************************************************/
//
///***********************************************************************
// * OpenCV example
// * By Shiqi Yu 2006
// ***********************************************************************/
//
//#include "cv.h"
//#include "cxcore.h"
//#include "highgui.h"
//
//int main( int argc, char** argv )
//{
//	  //����IplImageָ��
//	IplImage* pImg = NULL; 
//	IplImage* pContourImg = NULL;
//
//
//	CvMemStorage * storage = cvCreateMemStorage(0);
//	CvSeq * contour = 0;
//	int mode = CV_RETR_EXTERNAL;
//	
//	if( argc == 3)
//		if(strcmp(argv[2], "all") == 0)
//			mode = CV_RETR_CCOMP; //�������������
//      
//
//	  //��������
//	cvNamedWindow("src", 1);
//	cvNamedWindow("contour",1);
//
//
//	  //����ͼ��ǿ��ת��ΪGray
//	if( argc >= 2 && (pImg = cvLoadImage( argv[1], 0)) != 0 )
//	{
//		cvShowImage( "src", pImg );
//
//		  //Ϊ������ʾͼ������ռ�
//		  //3ͨ��ͼ���Ա��ò�ɫ��ʾ
//		pContourImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//		  //copy source image and convert it to BGR image
//		cvCvtColor(pImg, pContourImg, CV_GRAY2BGR);
//
//
//		  //����contour
//		cvFindContours( pImg, storage, &contour, sizeof(CvContour),	mode, CV_CHAIN_APPROX_SIMPLE);
//
//	}
//	else
//	{
//		  //���ٴ���
//		cvDestroyWindow( "src" );
//		cvDestroyWindow( "contour" );
//		cvReleaseMemStorage(&storage);
//		
//		return -1;
//	}
//
//
//
//
//	  //����������  
//	cvDrawContours(pContourImg, contour, CV_RGB(0,0,255), CV_RGB(255, 0, 0), 2, 2, 8);
//	  //��ʾͼ��
//	cvShowImage( "contour", pContourImg );
//	
//	cvWaitKey(0);
//
//
//	  //���ٴ���
//	cvDestroyWindow( "src" );
//	cvDestroyWindow( "contour" );
//	  //�ͷ�ͼ��
//	cvReleaseImage( &pImg );
//	
//	cvReleaseImage( &pContourImg ); 
//	
//	cvReleaseMemStorage(&storage);
//	
//	return 0;
//}
 /**************************************************
 * cvCanny��Canny��Ե���
 **************************************************/

/***********************************************************************
 * OpenCV example
 * By Shiqi Yu 2006
 ***********************************************************************/

//#include "cv.h"
//#include "cxcore.h"
//#include "highgui.h"
//
//int main( int argc, char** argv )
//{
//  //����IplImageָ��
//  IplImage* pImg = NULL; 
//  IplImage* pCannyImg = NULL;
//
//  //����ͼ��ǿ��ת��ΪGray
//  if( argc == 2 && 
//      (pImg = cvLoadImage( argv[1], 0)) != 0 )
//    {
//
//      //Ϊcanny��Եͼ������ռ�
//      pCannyImg = cvCreateImage(cvGetSize(pImg),
//					  IPL_DEPTH_8U,
//					  1);
//      //canny��Ե���
//      cvCanny(pImg, pCannyImg, 50, 150, 3);
//
//      //��������
//      cvNamedWindow("src", 1);
//      cvNamedWindow("canny",1);
//
//      
//      //��ʾͼ��
//      cvShowImage( "src", pImg );
//      cvShowImage( "canny", pCannyImg );
//	
//      cvWaitKey(0); //�ȴ�����
//
//      //���ٴ���
//      cvDestroyWindow( "src" );
//      cvDestroyWindow( "canny" );
//      //�ͷ�ͼ��
//      cvReleaseImage( &pImg ); 
//      cvReleaseImage( &pCannyImg ); 
//
//      return 0;
//    }
//
//  return -1;
//}

#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#endif

char wndname[] = "Edge";
char tbarname[] = "Threshold";
int edge_thresh = 1;

IplImage *image = 0, *cedge = 0, *gray = 0, *edge = 0;

// define a trackbar callback
void on_trackbar(int h)
{
	cvSmooth( gray, edge, CV_BLUR, 3, 3, 0, 0 );
	cvNot( gray, edge );

	// Run the edge detector on grayscale
	cvCanny(gray, edge, (float)edge_thresh, (float)edge_thresh*3, 3);

	cvZero( cedge );
	// copy edge points
	cvCopy( image, cedge, edge );

	cvShowImage(wndname, cedge);
}

int main( int argc, char** argv )
{
	char* filename = argc == 2 ? argv[1] : (char*)"fruits.jpg";

	if( (image = cvLoadImage( filename, 1)) == 0 )
		return -1;

	// Create the output image
	cedge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 3);

	// Convert to grayscale
	gray = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
	edge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
	cvCvtColor(image, gray, CV_BGR2GRAY);

	// Create a window
	cvNamedWindow(wndname, 1);

	// create a toolbar 
	cvCreateTrackbar(tbarname, wndname, &edge_thresh, 100, on_trackbar);

	// Show the image
	on_trackbar(0);

	// Wait for a key stroke; the same function arranges events processing
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&gray);
	cvReleaseImage(&edge);
	cvDestroyWindow(wndname);

	return 0;
}

#ifdef _EiC
main(1,"edge.c");
#endif

