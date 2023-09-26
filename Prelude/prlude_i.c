/** @file   prlude_i.c 
 *  @brief  prelude  of linux kernel development 
 *  @author  Umar Ba , LoopFocus jUmarB@protonmail.com 
 *  @copyright (c) 2023
 */

#include <linux/module.h>
#include <linux/printk.h> 
#include <linux/init.h>
#include <linux/moduleparam.h> 


#include "prlude.h" 

static int show_log = 1 ; 
module_param(show_log , int,   S_IRUSR | S_IWUSR) ;
MODULE_PARM_DESC(show_log , "Show log"); 




static int __init   prlude (void) { 

  int  current_architecture_type = _archtype_descovery(); 
  char logbuff[PRLD_PRINT_BUFF] ={ 0 } ; 
  
  switch (current_architecture_type) 
  {
    case (_i386)  : 
      sprintf ( logbuff , "Current Architecture Type is : %i Bits" , _i386 ) ; 
      break ; 
    
    case (_x64) : 
      sprintf ( logbuff , "Current Architecture Type is : %i Bits" , _x64 ) ;
      break ; 

    default  : 
      goto UKARCH; 
  }
  
  if(show_log  < 1 ) sprintf(logbuff  , "Hidden") ;  
  prld_print(logbuff);

  return   exit_success ;
  
UKARCH : 
  pr_warn("%s, Unknow Architecture\n",  PRLD) ; 
  return  exit_failure ; 
  
}

module_init(prlude) ; 
