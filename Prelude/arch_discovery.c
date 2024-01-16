/** @file arch_dicovery.c 
 *  @brief architecture  discovery 
 *  @author  Umar Ba <jUmarB@protonmail.com> 
 *  
 *  !!-MISCELLANEOUS-!! 
 */ 

#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/printk.h>
#include <linux/kernel.h> 


#include "arch_discovery.h" 
#include "arch_discovery_param.c"



static int __init arch_dicovery__entry(void) 
{ 
  
  if ( show_archbits_info > 0 ) {
    
    archbits_print("Architecture Type is %i", archbits()) ;   
  }else{
    archbits_print("*************") ;  
  }

  
  return _exit_success ; 
}


static void __exit arch_dicovery__end(void) 
{
  archbits_print("module unloaded"); 
}


module_init(arch_dicovery__entry) ; 
module_exit(arch_dicovery__end)
