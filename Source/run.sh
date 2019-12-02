#shell
python MyNet.py \
	--MODELTYPE NOQUANT \
	--EVALTYPE COUNT \
        --EVAL 1 \
        --BATCH 12 \
        --STEP 3000 \
        --IMGPATH ./train/ \
        --VALPATH ./eval/ \
        --TRAINLOGS ./train_logs/ \
        --VALLOGS ./eval_logs/ \
        --WIDTH 64 \
        --HEIGHT 64 \
        --CHANNELS 3 \
        --LRATE 0.0001 \
        --RATIO 0.8 \

