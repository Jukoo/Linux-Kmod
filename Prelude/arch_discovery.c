/** @file arch_dicovery.c 
 *  @brief   architecture  discovery 
 */ 

#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/printk.h>
#include <linux/kernel.h> 


#include "arch_discovery.h" 
#include "arch_discovery_param.c"



static int __init arch_dicovery__entry(void) 
{ 
  
  if ( show_arch_discovery_log_mesg >0 ) {
    switch(archbits()){
      case   _i386 :
        archbits_print("architecture type is  %i " ,  _i386) ; 
        break ; 
      case  _i64 : 
        archbits_print("architecture type is  %i " ,  _i64) ; 
        break ; 
      default  : 
        archbits_print("Unknow archbits type") ;  
        break ;  
    } 
  }else{
    /** sudo  insmod  show_arch_discovery_log_mesg=0 */ 
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
