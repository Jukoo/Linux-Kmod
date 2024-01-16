cmake_minimum_required(VERSION 3.25) 
include(../genericfg.cmake) 

project(prld) 

LIST( APPEND sources arch_discovery.c  arch_discovery_param.c) 

foreach(file IN  LISTS  sources ) 
  kbuild_append(${file})  
endforeach()




