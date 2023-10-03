obj-m += ad.o 
ad-objs= arch_discovery.o  arch_discovery_param.o  

.PHONY : all  clean 
	
all : 
	make -C /usr/lib/modules/$(shell  uname -r)/build/ M=$(shell pwd) modules 

clean  : 
	make -C /usr/lib/modules/$(shell uname -r)/build  M=$(shell  pwd) clean 



