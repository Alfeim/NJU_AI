#include "CVtools.h"
#include "models.h"
#include "predictobjs.h"
#include "headers.h"

void cnn::BasicPredictObj::CreateModel(std::string ModelName){
        
        	if(!NetModel){
                if(ModelName == "basic") this->NetModel = new BasicModel;
       	  }


			tensorflow::Status status_load = tensorflow::ReadBinaryProto(tensorflow::Env::Default(), NetModel->GetModelPath(), &graphdef); //从pb文件中读取图模型;

            if (!status_load.ok()) {
        	std::cout << "ERROR: Loading model failed..." <<  NetModel->GetModelPath() << std::endl;
        	std::cout << status_load.ToString() << "\n";
        	return;
    	}

    	tensorflow::Status status_create = session->Create(graphdef); //将模型导入会话Session中;
    	if (!status_create.ok()) {
        	std::cout << "ERROR: Creating graph in session failed..." << status_create.ToString() << std::endl;
        	return;
    	}
    	std::cout << "**Notice:    Successfully created session and load graph   "<<std::endl;

}




void  cnn::BasicPredictObj::Predict(){

        if(!session) Initialize();
    

         /*---------------------------------载入测试图片-------------------------------------*/
    	cv::Mat img=cv::imread(this->ImgPath,0);
    	if(img.empty())
    	{
        	std::cout<<"ERROR :can't open the image!"<<std::endl;
        	return ;
    	}

    	//创建一个tensor作为输入网络的接口
    	tensorflow::Tensor resized_tensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({1,this->ImgHeight,this->ImgWidth,3}));

    	//将Opencv的Mat格式的图片存入tensor
    	cvtools::CVMat_to_Tensor(img,&resized_tensor,this->ImgHeight,this->ImgWidth);

    	std::cout << resized_tensor.DebugString()<<std::endl;
        



       /*---------------------------------运行模型-------------------------------------*/
        std::vector<tensorflow::Tensor>  outputs;
        NetModel->load(outputs,resized_tensor,session);


        /*---------------------------------输出处理-------------------------------------*/
        //把输出值给提取出来,输出值存放在outputs中
    	std::cout << "Output tensor size:" << outputs.size() << std::endl;
    	for (std::size_t i = 0; i < outputs.size(); i++) {
        	std::cout << outputs[i].DebugString()<<std::endl;
	}


	tensorflow::Tensor t = outputs[0];                      // Fetch the first tensor
    	auto tmap = t.tensor<float, 2>();                         // Tensor Shape: [batch_size, target_class_num]
    	int output_dim = t.shape().dim_size(1);         // Get the target_class_num from 1st dimension



    	// Argmax: Get Final Prediction Label and Probability
    	int output_class_id = -1;
    	double output_prob = 0.0;
    	for (int j = 0; j < output_dim; j++)
    	{
        	std::cout << "Class " << j << " prob:" << tmap(0, j) << "," << std::endl;
        	if (tmap(0, j) >= output_prob) {
            		output_class_id = j;
            		output_prob = tmap(0, j);
        	}
   	 }	

    	 // 输出结果
    	std::cout << "Final class is: " << Labels[output_class_id] << std::endl;

		//清除会话
        delete session;
		session = nullptr;
}


