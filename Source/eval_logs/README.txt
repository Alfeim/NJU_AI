#convert_post_training.py

采用post training 量化方式
1.注释掉MyNet.py中的 
tf.contrib.quantize.create_training_graph(input_graph=tf.get_default_graph(), quant_delay=2000) 
tf.contrib.quantize.create_eval_graph(input_graph=tf.get_default_graph())
2.train模式下运行MyNet.py
3.eval模式下运行MyNet.py，在eval_logs文件下生成frozen_model.pb
4.运行convert_post_traning.py脚本



#convert_aware_training.py

采用aware training 量化方式
1.把MyNet.py中
tf.contrib.quantize.create_training_graph(input_graph=tf.get_default_graph(), quant_delay=2000) 
tf.contrib.quantize.create_eval_graph(input_graph=tf.get_default_graph())
的注释去掉
2.train模式下运行MyNet.py
3.eval模式下运行MyNet.py，在eval_logs文件下生成frozen_model.pb
4.运行convert_aware_traning.py脚本

