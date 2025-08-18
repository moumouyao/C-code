src = $(wildcard ./*.c) #匹配src下的所有源文件
obj = $(patsubst ./%.c, ./%, $(src)) #根据src中的文件，生成.o

inc_path=../include #定义变量 路径

myArgs= -Wall  #wall显示所有错误，g生成调试文件


a.out: $(obj)
	gcc $^ -o $@ $(myArgs) 

$(obj): ./%:./%.c
	gcc $< -o $@ $(myArgs) -I $(inc_path)

clean:
	rm -rf $(obj)

.PHONY: clean ALL


