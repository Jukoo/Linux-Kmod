cmake_minimum_required(VERSION 3.25) 
include(../genericfg.cmake) 
project(prld) 

kmod_spaning(misc_archdiscovery  arch_discovery arch_discovery_param)

module_compile(misc_archdiscovery)
