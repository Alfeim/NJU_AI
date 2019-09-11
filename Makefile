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
