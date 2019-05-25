#include "sift.h"
//#include "imgfeatures.h"
#include "match.h"
#include <math.h>
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
#include"iostream"
using namespace std;
int main()
{   //int intvls=6;
 //    feature* feat=NULL;
//	IplImage*src=cvLoadImage("1.jpg");
//	_sift_features( src, feat, SIFT_INTVLS, SIFT_SIGMA, /*SIFT_CONTR_THR*/0.355,
//			 SIFT_CURV_THR, SIFT_IMG_DBL, SIFT_DESCR_WIDTH,
//		 SIFT_DESCR_HIST_BINS );//0.04,80000;0.1,20000;0.2,3500;0.3,2600;0.35,279;0.355,229;0.4,29*/
	match();
	cout<<"%%%%%%%%%%%%%%   SUCCESS    %%%%%%%%%%%%%%%%% "<<endl;
	return 0;
}
