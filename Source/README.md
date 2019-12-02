# this filefolder include all the project codes

下面是文件夹的结构，train里面有两个文件夹，分别是缺陷件和非缺陷件，尺寸为64 * 64
```
├── eval(存放测试图片)
├── eval_logs(存放测试用的静态模型)
│   └──convert_aware_training.py (利用tensorflow python API将伪量化训练生成的模型转换为tflite格式，分别存储一份非量化和量化版本)	
│   └──convert_quant_training.py (利用tensorflow python API将非伪量化训练生成的模型转换为tflite格式，分别存储一份非量化和量化版本)	
|   └──post_pb2tflite.sh (利用toco将非量化训练生成的模型转换为tflite格式，推荐使用；如果不想量化就去掉max、min、stddev、mean、post_training_quantize等参数，并把输入类型改为float)
|   └──aware_pb2tflite.sh (利用toco将量化训练生成的模型转换为tflite格式，不推荐使用)	
├── train
│   └── defect
│   └── no_defect
├── run.sh (运行脚本,省事直接修改里面的参数配置即可)
├── train_logs(存放训练临时生成的cpkt文件)
├── input_data.py(输入模块，用于读取数据) 
├── MyNet.py(训练脚本，使用-h查看相关参数，推荐使用run.sh运行)
└── test_on_pb.py(测试脚本,请在包含tensorflow的虚拟环境下测试,输入模型格式为pb)
└── test_on_tflite_in_tensorflow.py(测试脚本,请在包含tensorflow的虚拟环境下测试,使用tensorflow.compat.v1.lite包，效率更高；输入模型格式为tflite) 
└── test_on_tflite_in_tflite_runtime.py(测试脚本,请在包含tensorflow lite runtime的虚拟环境下测试，使用tflite_runtime包，效率稍低一些；输入模型格式为tflite)
```

add on 2019/11/23 建议在tensorflow2.0环境下进行测试,在tensorflow1.X环境下进行训练、验证并生成量化模型

add on 2019/11/26 本项目可直接在tensorflow1.15下训练并测试

add on 2019/11/27 新增参数 MODELTYPE
		  修改run.sh中的MODELTYPE选项，为NOQUANT时表示不量化/训练后量化
		  修改run.sh中的MODELTYPE选项，为NOQUANT时表示训练时量化(伪量化)
		  注意在修改MODELTYPE选项后请清理train_logs中的文件

add on 2019/12/02 新增参数 EVALTYPE
		  修改run.sh中的EVALTPYE选项，为TEST时表示不进行最大最小值统计，而是进行测试并保存pb文件
		  修改run.sh中的EVALTPYE选项，为COUNT时表示进行最大最小值统计，其将对计算图各层进行逐层统计，得到最大最小值结果后可以算出量化时的std_dev和mean

		  附：在eval_logs文件夹下，修改post_pb2tflite.sh文件，
		  其参数的default_ranges_min即为传入参数COUNT时由MyNet脚本统计出的最大值；
		  其参数的default_ranges_min即为传入参数COUNT时由MyNet脚本统计出的最小值；
		  其参数的mean_values代表浮点0.0映射到uint8类型的位置，由公式mean=255*（float_zero - float_min)/(float_max - float_min)求出，是一个整数；
		  其参数的std_dev_values代表步长比，由公式std_dev = 255/(float_max - float_min)求出，是一个浮点数；
