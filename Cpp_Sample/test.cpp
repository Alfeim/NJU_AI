#include <iostream>

#include "mat2tensor.h"

#include <fstream>
#include <utility>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
 

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"

#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
 
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
 
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
 
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
 
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
 
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace tensorflow::ops;
using namespace tensorflow;
using namespace std;
using namespace cv;
using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;

void CVMat_to_Tensor(Mat img,Tensor* output_tensor,int input_rows,int input_cols)
{
    //imshow("input image",img);
    //图像进行resize处理
    resize(img,img,cv::Size(input_cols,input_rows));
    //imshow("resized image",img);
 
    //归一化
    img.convertTo(img,CV_32FC1);
    img=1-img/255;
 
    //创建一个指向tensor的内容的指针
    float *p = output_tensor->flat<float>().data();
 
    //创建一个Mat，与tensor的指针绑定,改变这个Mat的值，就相当于改变tensor的值
    cv::Mat tempMat(input_rows, input_cols, CV_32FC1, p);
    img.convertTo(tempMat,CV_32FC1);
 
//  waitKey(0);
}


int main(){
       	/*--------------------------------配置关键信息------------------------------*/
    	string model_path="../model.pb";
    	string image_path="/usr/local/DNN/NJU-AI/flowers-Classifer/train/roses/1.jpg";
    	int input_height =208;
    	int input_width=208;
    	string input_tensor_name="input";
    	string output_tensor_name="softmax";
 
	/*--------------------------------创建session------------------------------*/
    	Session* session;
    	Status status = NewSession(SessionOptions(), &session);//创建新会话Session
 
    	/*--------------------------------从pb文件中读取模型--------------------------------*/
    	GraphDef graphdef; //Graph Definition for current model
 
    	Status status_load = ReadBinaryProto(Env::Default(), model_path, &graphdef); //从pb文件中读取图模型;
    	if (!status_load.ok()) {
        	cout << "ERROR: Loading model failed..." << model_path << std::endl;
        	cout << status_load.ToString() << "\n";
        	return -1;
    	}
    	Status status_create = session->Create(graphdef); //将模型导入会话Session中;
    	if (!status_create.ok()) {
        	cout << "ERROR: Creating graph in session failed..." << status_create.ToString() << std::endl;
        	return -1;
    	}
    	cout << "<----Successfully created session and load graph.------->"<< endl;
        
	 /*---------------------------------载入测试图片-------------------------------------*/
    	cout<<endl<<"<------------loading test_image-------------->"<<endl;
    	Mat img=imread(image_path,0);
    	if(img.empty())
    	{
        	cout<<"can't open the image!!!!!!!"<<endl;
        	return -1;
    	}

    	//创建一个tensor作为输入网络的接口
    	Tensor resized_tensor(DT_FLOAT, TensorShape({1,input_height,input_width,3}));

    	//将Opencv的Mat格式的图片存入tensor
    	CVMat_to_Tensor(img,&resized_tensor,input_height,input_width);

    	cout << resized_tensor.DebugString()<<endl;


       /*-----------------------------------用网络进行测试-----------------------------------------*/
        cout<<endl<<"<-------------Running the model with test_image--------------->"<<endl;
       //前向运行，输出结果一定是一个tensor的vector
    	vector<tensorflow::Tensor> outputs;
    	string output_node = output_tensor_name;
    	Status status_run = session->Run({{input_tensor_name, resized_tensor}}, {output_node}, {}, &outputs);

    	if (!status_run.ok()) {
        	cout << "ERROR: RUN failed..."  << std::endl;
        	cout << status_run.ToString() << "\n";
        	return -1;
    	}
    	//把输出值给提取出来
    	cout << "Output tensor size:" << outputs.size() << std::endl;
    	for (std::size_t i = 0; i < outputs.size(); i++) {
        	cout << outputs[i].DebugString()<<endl;
	}


	Tensor t = outputs[0];                   // Fetch the first tensor
    	auto tmap = t.tensor<float, 2>();        // Tensor Shape: [batch_size, target_class_num]
    	int output_dim = t.shape().dim_size(1);  // Get the target_class_num from 1st dimension

    	// Argmax: Get Final Prediction Label and Probability
    	int output_class_id = -1;
    	double output_prob = 0.0;
    	for (int j = 0; j < output_dim; j++)
    	{
        	cout << "Class " << j << " prob:" << tmap(0, j) << "," << std::endl;
        	if (tmap(0, j) >= output_prob) {
            		output_class_id = j;
            		output_prob = tmap(0, j);
        	}
   	 }	

    	// 输出结果
    	cout << "Final class id: " << output_class_id << std::endl;
    	cout << "Final class prob: " << output_prob << std::endl;

	return 0;

}    
