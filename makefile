src = $(wildcard ./src/*.c) #匹配src下的所有源文件
obj = $(patsubst ./src/%.c, ./lib/%.o, $(src)) #根据src中的文件，生成.o

inc_path=./include #定义变量 路径

myArgs= -Wall -g #wall显示所有错误，g生成调试文件

ALL:a.out	#指定最终目标

a.out: $(obj)
	gcc $^ -o $@ $(myArgs) 

$(obj): ./lib/%.o:./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path)

clean:
	rm -rf $(obj) a.out

.PHONY: clean ALL


