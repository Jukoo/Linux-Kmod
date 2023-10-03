#ifndef  arch_dicovery_h 
#define  arch_dicovery_h 

#define  ABD_TAG_SYMBOL  "ABD"

MODULE_VERSION("1.0") ; 
MODULE_AUTHOR("Umar Ba , LoopFocus, jUmarB@protonmail.com"); 
MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("architecture byte  discovery") ; 


enum { 
  _exit_success , 
#define _exit_success  (0U << 1) 
  _exit_failure 
#define _exit_failure  ~_exit_success  
} ; 

#define MMSGBUFF   0xfe

#define  _b_unit   ( 1 << 3 )  

enum { 
  _i386 ,  
#define  _i386 (1<< 5) 
  _i64 
#define _i64   (_i386 << 1)
} ; 

#define archbits_print(_mesg , ...) ({\
    char m[MMSGBUFF]={0};\
    sprintf(m , _mesg ,  ##__VA_ARGS__) ;\
    pr_info("%s : %s" ,  ABD_TAG_SYMBOL ,  m) ;\
    }) 


/** @fn static inline  int archbits  
 *  @brief  size of architecture  type
 *  @return  int 
 */ 
static  inline int archbits (void) 
{
  return  sizeof ( void * )  * _b_unit ; 
}




#endif 
