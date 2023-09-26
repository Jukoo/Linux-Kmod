/** @file  prelude.h
 *  @brief prelude header  defintion and metainformation
 *  @author  Umar Ba ,LoopFocus jUmarB@lf.protonmail.com 
 *  @copyright (c) 2023 
 */

#ifndef  _PRLD
#define  _PRLD 

#include <linux/kernel.h>  

MODULE_DESCRIPTION("Simple module  that discover running architecture type " ); 
MODULE_AUTHOR("Umar Ba ,LoopFocus jUmarB@protonmail.com") ; 
MODULE_VERSION("1.0") ; 
MODULE_LICENSE("GPL") ;  

#define PRLD "prelude:"
#define PRLD_PRINT_BUFF  40 

enum { 
   exit_success ,
#define  exit_success  ( 0U << 1 ) 
   exit_failure 
#define  exit_failure  ~exit_success   
};

#define  _b_unit   (1 << 3)
enum { 
   _i386, 
#define _i386  (1 << 5) 
   x82_64
#define _x64 (_i386 << 1 ) 
}; 


#define  prld_print(__fmt_mesg , ... ) ({\
  char  tag[PRLD_PRINT_BUFF]={0}; \
  sprintf(tag,__fmt_mesg , ##__VA_ARGS__) ; \
  pr_info("%s:%s" ,  PRLD , tag); \
  })





static inline int  _archtype_descovery (void) { 
  return  sizeof(void *)*   _b_unit ; 
}




#endif 
