#ifndef  _MODEL_H_
#define _MODEL_H_
#include "CNN.h"


namespace cnn{
            class  BasicModel:public model{
                    public:
                        BasicModel(){
                            this->modelpath = "../MODELS/model.pb";  
                            this->tensor_name_input = "input";
                            this->tensor_name_ouput="softmax";
                        };
                    
                        void load(std::vector<tensorflow::Tensor> &output,tensorflow:: Tensor &input_tensor,tensorflow::Session *session);
            };

}

#endif // ! _MODEL_H_
