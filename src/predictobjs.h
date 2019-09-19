#ifndef _PREDICTOBJ_H_
#define _PREDICTOBJ_H_
#include "CNN.h"

namespace cnn{
            
            class BasicPredictObj : public PredictObj{
                    public:
                        BasicPredictObj( ){
                        
                        };

                        ~BasicPredictObj(){
                            if(NetModel) delete NetModel;
                            if(session) delete  session;

                        };

                        void CreateModel(const std::string  ModelName);
                        void Predict();

            };
}


#endif // !_PREDICTOBJ_H_