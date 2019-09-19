#include "headers.h"
#include "predictobjs.h"
#include "models.h"
#include "CVtools.h"

 /* --------the process to predict is shown in main()  ;  
     -------to know about the interface of functions, you can read  README.txt  or see them in CNN.h and CVtools.h*/

int main(){

		 cnn::PredictObj *p = new cnn::BasicPredictObj();

		 p->set_img_size(208,208);
		 p->set_img_path("/usr/local/DNN/NJU-AI/flowers-Classifer/train/tulips/10791227_7168491604.jpg");
		 p->set_Labels("daisy,roses,sunflowers,dandelion,tulips");
		 p->CreateModel("basic");
		 p->Predict();
		 delete p;

		 return 0;
}    


