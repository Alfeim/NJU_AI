#ifndef _CV_TOOLS_H_
#define _CV_TOOLS_H_
#include "headers.h"

namespace cvtools{

/*-----------------------------------------Functions  illustration---------------------------------------
*
* CVMat_to_Tensor : to reshape the img and transform it to the  tensor format(from the cv libs)
* 
*------------------------------------------------------------------------------------------------------------*/

void CVMat_to_Tensor(cv::Mat img,tensorflow::Tensor* output_tensor,int input_rows,int input_cols);

}



#endif // !_CV_TOOLS_H_