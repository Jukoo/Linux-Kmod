# makefile  for prlude_ 
obj-m +=prlude.o 
prlude-objs +=  prlude_i.o  prlude_e.o 

pwd :=$(CURDIR) 
kmv=$(shell  uname -r)  # kernel modules version  

.PHONY : all   clean  

all :  
	make -C /usr/lib/modules/$(shell uname -r)/build  M=$(pwd)  modules 

clean : 
	make -C /usr/lib/modules/$(shell uname -r)/build  M=$(shell pwd)  clean  
