import tensorflow as tf
from skimage import io, transform
import numpy as np
import glob
import cv2

WIDTH = 64
HEIGHT = 64
CHANNELS = 3
tf.enable_eager_execution()

imgpath = '../eval/'
in_path = "./frozen_model_NQ.pb"
out_path = "./post_model_byconvert.tflite"
out_path_quant = "./post_model_quant_byconvert.tflite"

#用convert方法生成的量化模型目前速率要比toco直接转换的方式小很多
#这种方式不支持层内有LRN操作 建议不使用

def get_image(file_dir,batch_size):
    #先载入图片
    imgs   = []
    
    for im in glob.glob(file_dir + '/*.jpg'):
        #print('reading the image: %s' % (im))
        img = io.imread(im)
        img = transform.resize(img, (WIDTH, HEIGHT, CHANNELS))
        imgs.append(img)

    imgs = np.asarray(imgs,np.float32)
    #然后生成batch
    image_batch = []
    border = imgs.shape[0]
    if border % batch_size != 0:
        border = border - border%batch_size
    maxstep = border//batch_size
    for i in range(maxstep):
        image_batch.append(imgs[i*batch_size:i*batch_size + batch_size])
    return np.asarray(image_batch)


# 确定模型节点
input_tensor_name = ["input"]
input_tensor_shape = {"input":[12,64,64,3]}
classes_tensor_name = ["output"]
ds=get_image(imgpath,12)
def representative_data_gen():
  for input_value in ds:
    yield [input_value]

converter = tf.compat.v1.lite.TFLiteConverter.from_frozen_graph(in_path,
                                            input_tensor_name, classes_tensor_name,
                                            input_shapes = input_tensor_shape)


#先生成原生的tflite模型
converter.allow_custom_ops=True
tflite_model = converter.convert()
with open(out_path,"wb") as f:
    f.write(tflite_model)


#再生成量化后的tflite模型
converter.post_training_quantize = True
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.float32
converter.inference_output_type = tf.uint8
converter.representative_dataset = representative_data_gen
tflite_quant_model = converter.convert()

with open(out_path_quant, "wb") as f:
    f.write(tflite_quant_model)
