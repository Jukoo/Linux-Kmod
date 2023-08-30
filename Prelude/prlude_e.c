/** @file   prlude_e.c 
 *  @brief  prelude  of linux kernel development ( module spinning  ) 
 *  @author  Umar Ba , LoopFocus jUmarB@protonmail.com 
 *  @copyright (c) 2023
 */
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/printk.h> 


static void __exit prelud_exit (void){ 
  pr_info("prelude : removed !\n");
}

module_exit(prelud_exit) ; 
