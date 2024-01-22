cmake_minimum_required(VERSION  3.25) 
project(simple_device_driver) 

include("../genericfg.cmake") 

kbuild_write(scdev_pilot) 

module_compile(scdev_pilot)
