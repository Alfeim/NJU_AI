# Makefile内容格式


cc = g++

prom = TEST

deps = $(shell find ./ -name "*.h")

src = $(shell find ./ -name "*.cpp")

obj = $(src:%.c=%.o)

CFLAGS = -I/home/alfeim/anaconda3/envs/tensorflow/include/python3.6m

LIBS = -L/home/alfeim/anaconda3/envs/tensorflow/lib -lpython3.6m

$(prom): $(obj)

        $(cc) $(CFLAGS) -o $(prom) $(obj) $(LIBS)

%.o: %.c $(deps)

        $(cc) -c $< -o $@

clean:

        rm -rf $(obj) $(prom)



# 各个参数意义
cc     指定的编译器
prom   生成文件名
deps   头文件
src    源文件
obj    指定目标文件，将所有的.c变成.o
CFLAGS 搜索头文件的目录
LIBS   库文件目录
