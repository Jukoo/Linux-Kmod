obj-m += scdev-pilot.o

.PHONY : all clean 

all : 
	@echo  -e " Compling module  $(obj-m)"  
	make -C /lib/modules/$(shell uname -r)/build  M=$(shell pwd)  modules  

clean :  
	make -C /lib/modules/$(shell uname -r)/build  M=$(shell pwd)  clean  
