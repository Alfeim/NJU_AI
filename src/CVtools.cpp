#include "CVtools.h"

namespace cvtools{
    
    
    void CVMat_to_Tensor(cv::Mat img,tensorflow::Tensor* output_tensor,int input_rows,int input_cols){
        //图像进行resize处理
        resize(img,img,cv::Size(input_cols,input_rows));
 
        //归一化
        img.convertTo(img,CV_32FC1);
        img=1-img/255;
 
        //创建一个指向tensor的内容的指针
        float *p = output_tensor->flat<float>().data();
 
        //创建一个Mat，与tensor的指针绑定,改变这个Mat的值，就相当于改变tensor的值
        cv::Mat tempMat(input_rows, input_cols, CV_32FC1, p);
        img.convertTo(tempMat,CV_32FC1);
    }



}