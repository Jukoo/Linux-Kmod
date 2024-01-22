cmake_minimum_required(VERSION 3.25) 
include(../genericfg.cmake) 

project(prld) 


kmod_spaning(ad arch_discovery arch_discovery_param)

module_compile(ad)
