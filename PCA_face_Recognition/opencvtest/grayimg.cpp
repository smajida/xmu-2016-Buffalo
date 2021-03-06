#include "opencvtest.h"

using namespace std;  
using namespace cv; 

//分块求特征map的直方图
/*
gray：输入由PCA2fea函数得到的叠加后最终的feature map
featureVec：输出特征map分块统计的直方图特征向量
*/
void gray01(Mat &gray,vector<float> &featureVec)
{
	int channels[] = {0};//第一个通道
	int histSize[] = {16};//直方图分为几份
	float granges [] = {0.0,15.0};//灰度图取值范围
	const float* ranges[] = {granges};

	int blocksize = 5;//分块大小

	double minval=0;
	double maxval=0;

	float temp=0.0;

	for(int i=0;i<gray.rows-blocksize+1;)
	{
		for(int j=0;j<gray.cols-blocksize+1;)
		{
			//对每个块内的每一列求直方图并拉成一个列向量
			Rect roi(j, i, blocksize, blocksize);
			Mat roi_img = gray(roi);
			Mat hist;//直方图

			calcHist(&roi_img,1,channels,Mat(),hist,1,histSize,ranges,true,false);

	
			for(int k=0;k<hist.rows;k++)
			{	
				temp = hist.at<float>(k,0);
				featureVec.push_back(temp);
			}
			j+=blocksize;
		}
		i+=blocksize;
	}
}