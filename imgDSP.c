


		/*		Image Segmentation for Car Plates Optical Character Recognition 	*/



#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void LoadImage(IplImage *img, char* argv)
{
	img = cvLoadImage("cpg6.jpg");
}


void ConvertGrayScale(IplImage *img1, IplImage *img2)
{
      cvCvtColor(img1, img2, CV_RGB2GRAY);
}


void ImageFiltering(IplImage *img1, IplImage *img2)
{
	cvSmooth(img1, img2, CV_GAUSSIAN, 7, 7);
}

void ImageBinarize(IplImage *img)
{
	cvThreshold(img, img, 200, 255, CV_THRESH_BINARY);
} 

void ImageDifference(IplImage *pImg_gray, IplImage *pImgBin, IplImage *pImg1, IplImage *pImg2, int *rowFirst, int *rowCount)
{
	int i, j;
	int rowSum = 0;
	int trowFirst = 0, trowCount = 0;

	for(j = 1; j < 294 ; j++) {
		unsigned char* ptrBin = (unsigned char*) pImgBin->imageData + (j * pImgBin->widthStep);
		unsigned char* ptr1 = (unsigned char*) pImg1->imageData + (j * pImg1->widthStep);
		for(i = 1; i < 419 ; i++) {
			ptr1[i] = abs(ptrBin[i] - ptrBin[i + 1]);
			if(ptr1[i])
				rowSum++;
//			*(pImg1->(imageData + i + (j * 296))) = abs(*(pImgBin->(imageData + i + (j * 296))) - *(pImgBin->(imageData + i + 1 +(j * 296))));
		}
		if(rowSum >= 8){
			if(j == (trowFirst + trowCount)) {
				trowCount++;
			}
			else {
				trowFirst = j;
				trowCount++;
			}	

		}

		else {
			if(trowCount > 12){
				*rowCount = trowCount;
				*rowFirst = trowFirst;
			}
			trowCount = 0;
			trowFirst = 0;
		}
		rowSum = 0;
	}
}

int main(int argc,char *argv[])
{
	IplImage *pImg;
	IplImage *pImg_gray;
	IplImage *pImgBin;
	IplImage *pImg1;
	IplImage *pImg2;
	
	if(argc != 3) {
		printf("Incorrect arguments\n");
		return(-1);
	}

//	LoadImage(pImg, argv[1]);

	pImg = cvLoadImage(argv[1]);
	
	pImg_gray = cvCreateImage(cvGetSize(pImg), pImg->depth, 1);
	pImgBin = cvCreateImage(cvGetSize(pImg), pImg->depth, 1);
	pImg1 = cvCreateImage(cvGetSize(pImg), pImg->depth, 1);

	ConvertGrayScale(pImg, pImg_gray);
//	cvCvtColor(pImg, pImg_gray, CV_RGB2GRAY);
//	        cvSaveImage("im1-gray.jpg", pImg_gray);

	ImageFiltering(pImg_gray, pImgBin);
//	cvSmooth(pImg_gray, pImg_gray, CV_GAUSSIAN, 7, 7);
//	        cvSaveImage("im1-filter.jpg", pImg_gray);

	ImageBinarize(pImgBin);
//	cvThreshold(pImgBin, pImgBin, 200, 255, CV_THRESH_BINARY);
//		cvSaveImage("im1-bin.jpg", pImgBin);

        CvRect roi;

	int rowFirst = 0, rowCount = 0;

	ImageDifference(pImg_gray, pImgBin, pImg1, pImg2, &rowFirst, &rowCount);
	
	roi = cvRect(0, rowFirst, pImg_gray->width, rowCount);
	cvSetImageROI(pImg_gray, roi);
	pImg2 = cvCreateImage(cvSize(pImg_gray->roi->width, pImg_gray->roi->height), pImg_gray->depth, 1);
	cvCopy(pImg_gray, pImg2);
	
//	ImageDifference(pImg_gray, pImgBin, pImg1, pImg2);

	cvSaveImage("img-segmnt.jpg", pImg2);
	cvSaveImage(argv[2], pImg_gray);
	cvReleaseImage(&pImg);
	cvReleaseImage(&pImg_gray);
	cvReleaseImage(&pImgBin);
	cvReleaseImage(&pImg1);
	cvReleaseImage(&pImg2);
	return 0;
}

