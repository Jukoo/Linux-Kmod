## Generic cmake configuration for building kernel modules 
## Author Umar Ba  <jUmarB@protonmail.com>
## version 0.1
## NOTE : no support for multiple file yet ! 
## ------------------------------------------

set(CMAKE_C_STANDARD 99) 
set(CMAKE_C_STANDARD_REQUIRED ON)  
set(HEADER_LOCATION /usr/lib/modules/)

string(ASCII 27  esc) 
set(success  "${esc}[1;32m")
set(warning  "${esc}[1;33m") 
set(error    "${esc}[1;31m")
set(info     "${esc}[1;36m")
set(normal   "${esc}[0m")  

function(mesginfo  level _m) 
  message(${level}  ${info}${_m}${normal}) 
endfunction() 

function(mesgwarning level _m) 
  message(${level}  ${warning}${_m}${normal}) 
endfunction() 

function(mesgerror level _message) 
  message(${level}  ${error}${_message}${normal}) 
endfunction() 

function(mesgsuccess level _m) 
  message(${level}  ${success}${_m}${normal}) 
endfunction() 

mesginfo(STATUS "load local configuration")

execute_process( 
    COMMAND  uname -r 
    OUTPUT_VARIABLE  KERNEL_RELEASE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

mesginfo(STATUS  "kernel version :::  ${KERNEL_RELEASE}")
mesginfo(CHECK_START "Kernel build Location")
find_path(
  KERNEL_HEADER
  include/linux/init.h
  include/linux/kernel.h
  include/linux/module.h
  PATHS ${HEADER_LOCATION}${KERNEL_RELEASE}/build
) 

if( NOT KERNEL_HEADER) 
  mesgwarning(CHECK_FAIL  "NOT FOUND [aborting...]")
  mesgerror(FATAL_ERROR   "DIE")
endif() 

mesgsuccess(CHECK_PASS  "[OK]") 
include_directories(${KERNEL_HEADER}/include) 

function(kbuild_write _m_source_file) 
  #string(SUBSTRING ${_m_source_file}  0 -1  ${test})   
  file(WRITE  ${CMAKE_CURRENT_BINARY_DIR}/Kbuild "obj-m +=${_m_source_file}.o\n")
endfunction() 

#TODO: append  multiple file object 
function(kbuild_append _m_source_file)
endfunction()


function(module_compile  _m_source_file)

  add_custom_command(OUTPUT  ${_m_source_file}.ko
    COMMAND  $(MAKE) -C   ${KERNEL_HEADER}/ M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR} modules
    WORKING_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR} 
    DEPENDS ${_m_source_file} 
    COMMENT  "[M] modules ${_m_source_file}" 
    VERBATIM
  ) 
  add_custom_target(module_driver ALL DEPENDS ${_m_source_file}.ko)
endfunction()


function(restore)
  add_custom_target(clear  ALL 
    COMMAND  $(MAKE) -C   ${KERNEL_HEADER}/ M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR} clean
    WORKING_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR} 
    COMMENT  "restoring to origine" 
    VERBATIM
  ) 
endfunction() 


restore()
