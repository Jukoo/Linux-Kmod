cmake_minimum_required(VERSION  3.25) 
include("../genericfg.cmake") 
project(simple_device_driver) 

kbuild_write(scdev_pilot) 

module_compile(scdev_pilot)
