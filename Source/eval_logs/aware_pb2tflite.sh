toco    --graph_def_file=/usr/local/DNN/NJU-AI/defect_detection_v_1_0_2/eval_logs/frozen_model_Q.pb \
        --input_format=TENSORFLOW_GRAPHDEF   \
        --output_format=TFLITE   \
        --output_file=/usr/local/DNN/NJU-AI/defect_detection_v_1_0_2/eval_logs/aware_model_quant.tflite  \
        --inference_type=QUANTIZED_UINT8 \
        --input_data_types=QUANTIZED_UINT8  \
        --input_arrays=input  \
        --output_arrays=output  \
        --input_shapes=12,64,64,3 \
	--reorder_across_fake_quant
