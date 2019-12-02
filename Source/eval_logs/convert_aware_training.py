import tensorflow as tf
import os
os.environ["CUDA_VISIBLE_DEVICES"] = "0"

in_path = "./frozen_model_Q.pb"
out_path = "./model_aware_training.tflite"
out_path_quant = "./model_aware_training_quant.tflite"

# 模型输入节点
input_tensor_name = ["input"]
input_tensor_shape = {"input":[12,64,64,3]}
# 模型输出节点
classes_tensor_name = ["output"]

converter = tf.lite.TFLiteConverter.from_frozen_graph(in_path,
                                            input_tensor_name, classes_tensor_name,
                                            input_shapes = input_tensor_shape)

converter.inference_type = tf.lite.constants.QUANTIZED_UINT8

#以下参数(0.,1.)分别表示mean = 0 ， std_dev = 1
#mean的含义是与float值0.0对应的uint8值，即零点，可用公式 mean = 255 * （float_zero - float_min)/(float_max - float_min)求出
#stddev的含义时步长比率，即uint8下的一步相当于float下的多少步，公式为std_dev = 255/(float_max - float_min)
#float_max与float_min可在训练后对各层参数进行统计
converter.quantized_input_stats = {input_tensor_name[0]: (0.,1.)}

tflite_model_quant = converter.convert()

#然后存储量化后的tflite
with open(out_path_quant, "wb") as f:
    f.write(tflite_model_quant)
