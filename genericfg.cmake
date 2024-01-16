## Generic cmake configuration for building kernel modules 
## Author Umar Ba  <jUmarB@protonmail.com>  github/Jukoo 
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

function(mesginfo  level _message) 
  message(${level}  ${info}${_message}${normal}) 
endfunction() 

function(mesgwarning level _message) 
  message(${level}  ${warning}${_message}${normal}) 
endfunction() 

function(mesgerror level _message) 
  message(${level}  ${error}${_message}${normal}) 
endfunction() 

function(mesgsuccess level _message) 
  message(${level}  ${success}${_message}${normal}) 
endfunction() 

mesginfo(STATUS "Load  Static Config")

execute_process( 
    COMMAND  uname -r 
    OUTPUT_VARIABLE  KERNEL_RELEASE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

mesginfo(STATUS  "kernel version  ${KERNEL_RELEASE}")
mesginfo(CHECK_START "Detecting  Kernel Build Path Location")
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

mesgsuccess(CHECK_PASS  "<${KERNEL_HEADER}> [OK]")

include_directories(${KERNEL_HEADER}/include)  


function(kbuild_write _m_source_file) 
  file(WRITE  ${CMAKE_CURRENT_BINARY_DIR}/Kbuild "obj-m +=${_m_source_file}.o\n")
endfunction() 

function(kbuild_append _m_source_file)
  file(APPEND   ${CMAKE_CURRENT_BINARY_DIR}/Kbuild "obj-m +=${_m_source_file}.o\n")  
endfunction() 


## Add more objects file in kbuild file
## FIXME : foreach loop doesn't work well 
#function(kbuild_append_multi  _m_source_files_list) #
#foreach(_mfile  IN  LISTS _m_source_files_list)     
    #kbuild_append(${_mfile_0})
    #message(STATUS "build for  ->  ${_mfile}") 
    #endforeach() 
#endfunction()


function(kmod_spaning _m_spaname file_1 file_2)  
   
endfunction()  

function(module_compile  _m_source_file)

  add_custom_command(OUTPUT  ${_m_source_file}.ko
    COMMAND  $(MAKE) -C   ${KERNEL_HEADER}/ M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR} modules
    WORKING_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR} 
    DEPENDS ${_m_source_file} 
    COMMENT  "[M] modules ${_m_source_file}" 
    VERBATIM
  ) 
  ## make module_driver  
  add_custom_target(module_driver ALL DEPENDS ${_m_source_file}.ko)
endfunction()


function(restore) 
  ##  make clear 
  add_custom_target(clear  ALL 
    COMMAND  $(MAKE) -C   ${KERNEL_HEADER}/ M=${CMAKE_CURRENT_BINARY_DIR} src=${CMAKE_CURRENT_SOURCE_DIR} clean
    WORKING_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR} 
    COMMENT  "restoring to origine" 
    VERBATIM
  ) 
endfunction() 

#!NOTE: must be called so that the makefile takes it into account from the start. 
restore()
