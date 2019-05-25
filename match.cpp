/*
  Detects SIFT features in two images and finds matches between them.

  Copyright (C) 2006-2012  Rob Hess <rob@iqengines.com>

  @version 1.1.2-20100521
*/
//#include "stdafx.h"
#include "sift.h"
//#include "imgfeatures.h"
#include "kdtrees.h"
//#include "utils.h"
//#include "xform.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <stdio.h>
#include"iostream"
#include <fstream>
using namespace std;

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49

IplImage* stack_imgs( IplImage* img1, IplImage* img2 );
int match( )
{
	int si;
	int mm=0;
	char nstr[3];
	char str[20]="D:\\sift\\";
	char str1[20];
	char str2[30];
	char str3[30];
	char strd[20]="H:\\data\\palm\\6\\ROI\\";
	char strd1[20]="H:\\data\\palm\\6\\ROI\\";
	int num=5;
for (si=1;si<num;si++)
{

	
	
  ifstream transform_file(str1,ios::in);

  IplImage* img1, * img2, * stacked,*image,*img_1,*img_2;
  IplImage* dwn1,*dwn_1,*dwn1_2,*dwn1_4;
  IplImage* dwn2,*dwn2_1,*dwn2_2,*dwn2_4;
  struct feature* feat1=NULL, * feat2=NULL, * feat=NULL;
  struct feature** nbrs;
  struct kd_node* kd_root;
  CvPoint pt1, pt2;
  double d0, d1;
  int n1, n2, k, i, m = 0;
   CvSize size=cvSize(1020,1020);
  //if( argc != 3 )
   // fatal_error( "usage: %s <img1> <img2>", argv[0] );
  //IplImage* GrayImage= cvLoadImage( "7.jpg" );
 // img1 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
  //cvCvtColor(GrayImage,img1,CV_RGB2GRAY);
 // IplImage* GrayImage2= cvLoadImage( "8.jpg" );
 // img2 = cvCreateImage(cvGetSize(GrayImage2),IPL_DEPTH_8U,1);
 // cvCvtColor(GrayImage2,img2,CV_RGB2GRAY);
   int p1;
   for (p1=si+1;p1<=num;p1++)
   {
	   itoa(mm,nstr,10);
	   mm++;
	   strcpy(str1,str);
	   strcat(str1,nstr);
	   
	   FILE* file = fopen (str1, "wb");
   
   if(1)
   {
	   
	   itoa(p1,nstr,10);
	   strcpy(str2,strd);
	   strcat(str2,nstr);
	   strcat(str2,"_rotate.jpg");

	   itoa(si,nstr,10);
	   strcpy(str3,strd1);
	   strcat(str3,nstr);
	   strcat(str3,"_rotate.jpg");

	   printf(str2);
	   printf(" ");
	   printf(str3);
	   printf("\n");
  img_1 = cvLoadImage( str2 );
  img_2 = cvLoadImage( str3 );
  CvSize dwnSize1_0=cvSize(img_1->width/2,img_1->height/2);
  CvSize dwnSize1_2=cvSize(img_1->width/4,img_1->height/4);
  CvSize dwnSize1_4=cvSize(img_1->width/8,img_1->height/8);
  CvSize dwnSize2_0=cvSize(img_2->width/2,img_2->height/2);
  CvSize dwnSize2_2=cvSize(img_2->width/4,img_2->height/4);
  CvSize dwnSize2_4=cvSize(img_2->width/8,img_2->height/8);

  dwn1=cvCreateImage(dwnSize1_0,img_1->depth,3);
  dwn1_2=cvCreateImage(dwnSize1_2,img_1->depth,3);
  dwn1_4=cvCreateImage(dwnSize1_4,img_1->depth,3);
  dwn2=cvCreateImage(dwnSize2_0,img_2->depth,3);
  dwn2_2=cvCreateImage(dwnSize2_2,img_2->depth,3);
  dwn2_4=cvCreateImage(dwnSize2_4,img_2->depth,3);

  cvPyrDown(img_1,dwn1,CV_GAUSSIAN_5x5);
  cvPyrDown(dwn1,dwn1_2,CV_GAUSSIAN_5x5);
  cvPyrDown(dwn1_2,dwn1_4,CV_GAUSSIAN_5x5);
  cvPyrDown(img_2,dwn2,CV_GAUSSIAN_5x5);
  cvPyrDown(dwn2,dwn2_2,CV_GAUSSIAN_5x5);
  cvPyrDown(dwn2_2,dwn2_4,CV_GAUSSIAN_5x5);
  img1=dwn1_4;
  img2=dwn2_4;
   }
   else
   {
  image=cvLoadImage( "F://23.jpg" );
  //cvSetImageROI(image,cvRect(510,510,510,510));
  img1=cvCreateImage(cvSize(1020,1020), image->depth, image->nChannels);
  //cvCopy(image,img1,NULL);
  //cvResetImageROI(image);
 for(int i=510;i<img1->height+510;i++)

	{
		unsigned char* ptr=(unsigned char *)(image->imageData + i*image->widthStep);
		unsigned char* ptr1=(unsigned char *)(img1->imageData + (i-510)*img1->widthStep);
		for(int j=0;j<img1->width;j++)
		{
		    ptr1[j*img1->nChannels+0]=ptr[(j+510)*image->nChannels+0];
			ptr1[j*img1->nChannels+1]=ptr[(j+510)*image->nChannels+1];
			ptr1[j*img1->nChannels+2]=ptr[(j+510)*image->nChannels+2];
		}
  }		

   image=cvLoadImage( "F://24.jpg" );
  //cvSetImageROI(image,cvRect(510,510,510,510));
  img2=cvCreateImage(cvSize(1020,1020), image->depth, image->nChannels);
  //cvCopy(image,img1,NULL);
  //cvResetImageROI(image);
 for(int i=510;i<img2->height+510;i++)

	{
		unsigned char* ptr=(unsigned char *)(image->imageData + i*image->widthStep);
		unsigned char* ptr1=(unsigned char *)(img2->imageData + (i-510)*img2->widthStep);
		for(int j=0;j<img1->width;j++)
		{
			ptr1[j*img1->nChannels+0]=ptr[(j+510)*image->nChannels+0];
			ptr1[j*img1->nChannels+1]=ptr[(j+510)*image->nChannels+1];
			ptr1[j*img1->nChannels+2]=ptr[(j+510)*image->nChannels+2];
		}
  }	
  }
 // IplImage* GrayImage = cvCreateImage(cvGetSize(img1),IPL_DEPTH_8U,1);
  //cvCvtColor(img1,GrayImage,CV_RGB2GRAY);
 // cvNamedWindow( "7",0 );
 // cvShowImage( "7", img1 );
 // cvWaitKey( 0 );
//	cvSaveImage("img1.jpg", img1 );
  //cvReleaseImage( &GrayImage );
//  cvDestroyWindow("7");
 // cvNamedWindow( "8",0 );
//  cvShowImage( "8", img2);
//  cvWaitKey( 0 );
//	cvSaveImage("img2.jpg", img2 );
 // cvReleaseImage( &GrayImage2 );
// cvDestroyWindow("8");
//  if( ! img1 )
  ///  fatal_error( "unable to load image from %s", argv[1] );
//  img2 = cvLoadImage( "8.jpg" ,0);
//  if( ! img2 )
  //  fatal_error( "unable to load image from %s", argv[2] );
  stacked = stack_imgs( img1, img2 );

 // /fprintf( stderr, "Finding features in %s...\n", argv[1] );
  feat1 = _sift_features( img1,feat1, SIFT_INTVLS, SIFT_SIGMA, /*SIFT_CONTR_THR*/0.02,
			 SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
		 SIFT_DESCR_HIST_BINS ,&n1);//大于0.46就什么都没了
 // fprintf( stderr, "Finding features in %s...\n", argv[2] );
  feat2 = _sift_features( img2, feat2,SIFT_INTVLS, SIFT_SIGMA, /*SIFT_CONTR_THR*/0.02,
			 SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
		 SIFT_DESCR_HIST_BINS,&n2 );
  fprintf(file,"%d %d\r\n",n1,n2);
 	 fflush(file);
  //fprintf( stderr, "Building kd tree...\n" );
  kd_root = kdtree_build( feat2, n2 );
  for( i = 0; i < n1; i++ )
    {
      feat = feat1 + i;
      k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
      if( k == 2 )
	{
	  d0 = descr_dist_sq( feat, nbrs[0] );
	  d1 = descr_dist_sq( feat, nbrs[1] );
	  if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
	    {
	      pt1 = cvPoint( cvRound( feat->x ), cvRound( feat->y ) );
	      pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
		  fprintf(file,"%d %d %d %d\r\n",pt1.x,pt1.y,pt2.x,pt2.y);
 	      fflush(file);
	      pt2.x += img1->width;//pt2.y += img1->height;
		  cvLine( stacked, pt1, pt2, CV_RGB(255,0,0), 1, 8, 0 );
	      m++;
	      feat1[i].fwd_match = nbrs[0];
	    }
	}
      free( nbrs );
    }
  fprintf(file,"%d \r\n",m);
 	 fflush(file);
	 fclose(file);
 // fprintf( stderr, "Found %d total matches\n", m );
  //display_big_img( stacked, "Matches" );
 
  //cvWaitKey( 0 );

  /* 
     UNCOMMENT BELOW TO SEE HOW RANSAC FUNCTION WORKS
     
     Note that this line above:
     
     feat1[i].fwd_match = nbrs[0];
     
     is important for the RANSAC function to work.
  */
  /*
  {
    CvMat* H;
    IplImage* xformed;
    H = ransac_xform( feat1, n1, FEATURE_FWD_MATCH, lsq_homog, 4, 0.01,
		      homog_xfer_err, 3.0, NULL, NULL );
    if( H )
      {
	xformed = cvCreateImage( cvGetSize( img2 ), IPL_DEPTH_8U, 3 );
	cvWarpPerspective( img1, xformed, H, 
			   CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS,
			   cvScalarAll( 0 ) );
	cvNamedWindow( "Xformed", 1 );
	cvShowImage( "Xformed", xformed );
	cvWaitKey( 0 );
	cvReleaseImage( &xformed );
	cvReleaseMat( &H );
      }
  }
  */
    /*cvNamedWindow( "match",1 );
	cvShowImage( "match", stacked );*/
	/*cvWaitKey( 0 );*/
	//cvSaveImage("match3.jpg", stacked );
  cvReleaseImage( &stacked );
 //cvDestroyWindow("match");
  cvReleaseImage( &img1 );
  cvReleaseImage( &img2 );
  kdtree_release( kd_root );
  free( feat1 );
  free( feat2 );
  }
}
  return 0;
}

 IplImage* stack_imgs( IplImage* img1, IplImage* img2 )
{
  //IplImage* stacked = cvCreateImage( cvSize( MAX(img1->width, img2->width),
					//     img1->height + img2->height ),
				  //   IPL_DEPTH_8U, 3 );
  IplImage* stacked = cvCreateImage( cvSize( img1->width + img2->width,
	  MAX(img1->height, img2->height) ),
				     IPL_DEPTH_8U, 3 );
  cvZero( stacked );
  cvSetImageROI( stacked, cvRect( 0, 0, img1->width, img1->height ) );
  cvAdd( img1, stacked, stacked, NULL );
  //cvSetImageROI( stacked, cvRect(0, img1->height, img2->width, img2->height) );
  cvSetImageROI( stacked, cvRect(img1->width,0,  img2->width, img2->height) );
  cvAdd( img2, stacked, stacked, NULL );
  cvResetImageROI( stacked );

  return stacked;
}