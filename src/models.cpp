#include "models.h"

void cnn::BasicModel::load(std::vector<tensorflow::Tensor> &outputs,tensorflow:: Tensor &input_tensor,tensorflow::Session* session){
     /*-----------------------------------用网络进行测试-----------------------------------------*/
       //前向运行，输出结果一定是一个tensor的vector
    	std::string output_node = this->tensor_name_ouput;
    	tensorflow::Status status_run = session->Run({{this->tensor_name_input, input_tensor}}, {output_node}, {}, &outputs);

    	if (!status_run.ok()) {
        	std::cout << "ERROR : RUN failed..."  << std::endl;
        	std::cout << status_run.ToString() << "\n";
        	return;
    	}
        

}