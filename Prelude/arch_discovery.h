#ifndef  arch_dicovery_h 
#define  arch_dicovery_h 

#define  TAG "Archdiscovery"

MODULE_VERSION("1.0") ; 
MODULE_AUTHOR("Umar Ba , jUmarB@protonmail.com"); 
MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("architecture byte  discovery") ; 


typedef  void *   __ptr_t   ; 

enum { 
  _exit_success , 
#define _exit_success  (0U << 1) 
  _exit_failure 
#define _exit_failure  ~_exit_success  
} ; 

#define MMSGBUFF   0xfe

#define  _b_unit   ( 1 << 3 )  

enum { 
  _32,  
#define  _32 (1<< 5) 
  _64 
#define _64   (_32<< 1)
} ; 

#define archbits_print(_mesg , ...) ({\
    char m[MMSGBUFF]={0};\
    sprintf(m , _mesg ,  ##__VA_ARGS__) ;\
    pr_info("%s : %s" , TAG,  m) ;\
    }) 


/** @fn static inline  int archbits  
 *  @brief  size of architecture  type
 *  @return  int 
 */ 
static  inline int archbits (void) 
{
  return  sizeof(__ptr_t)  * _b_unit ; 
}




#endif 
