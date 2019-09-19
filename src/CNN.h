#ifndef _CNN_H_
#define _CNN_H_
#include "headers.h"


namespace cnn{


        /*-----------------------------------------Ineterface  illustration---------------------------------------
         * 
         * member fuction name :
         *              model : initialize the object and set default  model(.pb) path
         *              set_modelpath : set your own model path
         *              set_tensor_name_input : set the name of the input layer of model  (you can check it by using check.py)
         *              set_tensor_name_output : set the name of the output layer of model  (you can check it by using check.py)
         *              GetModelPath : return the model's path of the object 
         *              GetTensorNameInput : get the name of the input layer of model(if you have set it)
         *              GetTensorNameOutput : get the name of the output layer of model(if you have set it)           
         *              load : to load the pb file , you should implement this function yourself.      
         *  
         *member var name:
         *              modelpath : the string the path of model(.pb)
         *              tensor_name_input : the string the name of the input layer of model;
         *              tensor_name_output :   the string the name of the output layer of model;
         *            
         *--------------------------------------------------------------------------------------------------------------*/

        class model{
            public:
                    model(){
                            
                    }; 

                    model(const std::string path):modelpath(path){
                        
                    }

                    void set_modelpath(const std::string path){
                                this->modelpath = path;
                    }

                    void set_tensor_name_input(const std::string name){
                                this->tensor_name_input = name;
                    }

                    void set_tensor_name_output(const std::string name){
                                this->tensor_name_ouput = name;
                    }
                    
                    std::string GetModelPath(){
                        return modelpath;
                    }

                    std::string GetTensorNameInput(){
                            return tensor_name_input;
                    }

                    std::string GetTensorNameOutput(){
                            return tensor_name_ouput;
                    }


                    virtual void load(std::vector<tensorflow::Tensor> &outputs,tensorflow:: Tensor &input_tensor,tensorflow::Session *session)= 0;

            
            protected:
                    std::string modelpath;
                    std::string tensor_name_input;
                    std::string tensor_name_ouput;


        };



        /*-----------------------------------------Ineterface  illustration---------------------------------------
        * 
        * member fuction name :
        *               set_img_size : set the width and the height of  image input (after transformed by cvtools)
        *               set_img_path : set the path of single image
        *               set_img_folder : set the path containing your test images(should be a folder)
        *               Initialize : to initial the session
        *               setModel : to change the name of layer inputs and outputs of your model
        *               CreateModel: the interface to create a model object , you should implement this function yourself.
        *               Predict : the interface to predict your image , you should implement this function yourself.
        *               set_Labels : to set the labels of your prediction   the format of input should be like this "daisy,rose,sunflowers"  each element should be seperated by  ','
        * 
        * member var name:
        *               ImgWidth : the width you set of the image
        *               ImgHeight : the height you set of  the image
        *               NetModel : a pointer of the model object
        *               Imgpath : the string the path of your image
        *               ImgFolder : the string the path of your image folder;
        *               session : a session (from tensorflow libs) 
        *               graphdef : the graph of tensorflow(from tensorflow libs) 
        * 
        *--------------------------------------------------------------------------------------------------------------*/
        
        class PredictObj{
                public:

                        PredictObj():session(nullptr),NetModel(nullptr){
                                Initialize();
                        };

                        void set_img_size(int width,int height){
                                this->ImgWidth = width;
                                this->ImgHeight = height;
                        };

                
                        void set_img_path(std::string  path){
                                this->ImgPath = path;
                        };

                        void set_img_forder(std::string  path){
                                this->ImgFolder = path;
                        };

                        void Initialize(){
    	                        if( session == nullptr ) tensorflow::Status status = tensorflow::NewSession(tensorflow::SessionOptions(), &session);
                        };

                        void setModel(std::string  tensor_input_name,std::string tensor_output_name){
                                 if(!NetModel){
                                        std::cout<<"ERROR:    Please Create a new Model first!"<<std::endl;
                                        return;
                                 }
                                this->NetModel->set_tensor_name_input(tensor_input_name);
                                this->NetModel->set_tensor_name_output(tensor_output_name);
                        };


                        void set_Labels(std::string str){
                                 Labels.clear();
                                 int n = str.size(),i = 0;
                                 while(i < n){
                                         if(str[i] == ','){
                                                 i++;
                                                 continue;
                                         }
                                         std::string cur;
                                         while(i < n && str[i] != ',') cur += str[i++];
                                         Labels.push_back(cur);
                                 }
                        }


                        virtual void CreateModel(const std::string  ModelName)=0;
                        virtual void Predict() = 0;
                       

                protected:
                        int ImgWidth;
                        int ImgHeight;
                        model *NetModel;
                        std::string ImgPath;
                        std::string ImgFolder;
                        std::vector<std::string> Labels;
                        tensorflow::Session *session;
                        tensorflow::GraphDef graphdef;
      
        };

}

#endif