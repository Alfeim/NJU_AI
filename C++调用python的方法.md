1.头文件引用Python.h
2.编译时添加 -I/对应版本python头文件的位置 -L/对应版本python库的位置 -lpythonX.X 

之所以在头文件引用时不用如<pythonX.X/Python>的方式是因为当Python版本号改变时需要更改源文件，而在编译时指定版本号更为方便

记得先要在～/.bashrc中增加如下的环境变量设置

export PYTHONHOME=/Python的路径
export LD_LIBRARY_PATH=其他环境设置:$PYTHONHOME/lib
PATH=$PATH:其他环境设置:PYTHONHOME/bin

以本机编译命令为例
sudo g++ -o test test.cpp -I /home/alfeim/anaconda3/envs/tensorflow/include/python3.6m -L /home/alfeim/anaconda3/envs/tensorflow/lib -lpython3.6m

