cmake_minimum_required(VERSION 3.25) 
project(fas) 
list(APPEND English one two three four ) 

foreach( v IN  ZIP_LISTS English  ) 
  message(STATUS "----> ${v_0}" ) 
endforeach() 



