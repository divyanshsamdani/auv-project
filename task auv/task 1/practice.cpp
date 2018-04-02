#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main(){
	vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat img2 = imread("dice.jpg",1);
	Mat img = imread("dice.jpg",0);
	Mat img1(img.rows,img.cols,CV_8UC1);
	Mat fin(img.rows,img.cols,CV_8UC1);
	Mat fin1(img.rows,img.cols,CV_8UC1);
	
	namedWindow("win3",WINDOW_NORMAL);
	//GaussianBlur (img,img,Size(3,3),1.5,1.5);

	for(int i=0;i<img.rows;i++){					//convert to binary
		for(int j=0;j<img.cols;j++){
			if(img.at<uchar>(i,j)>200){
				img1.at<uchar>(i,j) = 255;
			}

		}
	}
	
	GaussianBlur (img1,img1,Size(3,3),1.5,1.5);

	int k,l,flag=0;

	for(int i=2;i<img1.rows-2;i++)					//dilation with a 5*5 kernel
	{
		for(int j=2;j<img1.cols-2;j++)
		{
			for( k=i-2;k<=i+2;k++)
			{
				for(l=j-2;l<=j+2;l++)
				{
					if(img1.at<uchar>(k,l)==255)flag=1;

				}
			}
			if(flag==1)fin.at<uchar>(i,j)=255;
			else fin.at<uchar>(i,j)=0;
			flag=0;

		}
	}	




	for(int i=1;i<img1.rows-1;i++)					//erosion with a 3*3 kernel
	{
		for(int j=1;j<img1.cols-1;j++)
		{
			for( k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					if(fin.at<uchar>(k,l)==0)flag=1;

				}
			}
			if(flag==1)fin1.at<uchar>(i,j)=0;
			else fin1.at<uchar>(i,j)=255;
			flag=0;

		}
	}	



	//imshow("win3",fin1);
	//waitKey(0);
	//GaussianBlur (fin,fin,Size(3,3),1.5,1.5);

	findContours(fin1,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE );
	
	

	cout << contours.size()<<endl;
	

	
	int check,dice=0;
	for(int idx=0;idx<contours.size();idx++){
		if(hierarchy[idx][3]==-1){
			drawContours(img2,contours,idx,{255,0,255},5,8,hierarchy,0);
			dice ++;
			

		}
		if(hierarchy[idx][2]==-1){
			drawContours(img2,contours,idx,{255,0,0},5,8,hierarchy,0);

		}


	}

    cout << "Number of dices :- "<<dice<<endl;
    
    }

	namedWindow("win",WINDOW_NORMAL);
	namedWindow("win1",WINDOW_NORMAL);
	namedWindow("win2",WINDOW_NORMAL);
	
	imshow("win",img);
	imshow("win1",img1);
	imshow("win3",fin1);
	
	imshow("win2",img2);
	waitKey (0);
	return 0;

}
