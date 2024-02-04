/**  @file scdev-pilot.h 
 *   @brief header prototype and meta information for character device driver  
 *   @author Umar Ba, LoopFocus 'Software Craftmanship' <jUmarB@protonmail.com>
 *   @copyright (c)  2023  
 **/ 

#ifndef  SCDEV_PILOT 
#define  SCDEV_PILOT

/** Meta information */

MODULE_VERSION("0.1")  ; 
MODULE_AUTHOR("Umar Ba, LoopFocus 'Software Craftmanship' <jUmarB@protonmail.com>") ; 
MODULE_LICENSE("GPL") ; 
MODULE_DESCRIPTION("Simple Character Device Driver") ; 

#define  _exit_success 0 
#define  _exit_failure  ~_exit_success  
#define  _nullable  (void *) _exit_success 

 

#define SCDEV_TAG      "sc2df"    /** device filename */
#define SCDEV_BASENAME "scdev-pilot"  

#define SCDEV_BUFFSIZE 0xff  


#ifndef SCDEV_KLOG 

#define scdev_log(fmt , ...) \
  pr_info(pr_fmt(fmt) ,##__VA_ARGS__)  

#define scdev_log_err(fmt, ...) \
  pr_err(pr_fmt(fmt) , ##__VA_ARGS__)  

#define scdev_log_warn(fmt,...) \
  pr_warn(pr_fmt(fmt) , ##__VA_ARGS__)   

#else 

typedef  enum LOG_LVL { 
  K_STDOUT , 
  K_STDERR 
}LOG_LVL;  

static inline  void  scdev_log (const char * mesg  , LOG_LVL __log_level)  { 
  char scdev_buff[0xff] = {0}; 
  sprintf(scdev_buff , "%s:%s" ,SCDEV_BASENAME, mesg) ;  
  
  switch(__log_level) 
  {
    case  K_STDOUT:  
      pr_info("%s" , scdev_buff) ;
      break ; 
    case K_STDERR : 
      pr_err("%s",scdev_buff) ; 
      break  ; 
      
    default : 
      pr_notice("%s" ,"Undefine  log level" ) ; 
      break ;  

  }
}
#endif

static int  scdev_open(struct  inode*  , struct file *) ;
static int  scdev_close(struct  inode*  , struct file *) ;
static ssize_t scdev_read(struct file * , char __user *  , size_t ,  loff_t *);
static ssize_t scdev_write(struct file * ,const char __user *  , size_t ,  loff_t *);


#endif 
