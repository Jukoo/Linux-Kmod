/**  @file scdev-pilot.c
 *   @brief  simple character  device driver 
 *   @author Umar Ba, LoopFocus 'Software Craftmanship' <jUmarB@protonmail.com>
 *   @copyright (c)  2023  
 *  
 **/ 


#include <linux/init.h> 
#include <linux/module.h>  
#include <linux/printk.h>
#include <linux/fs.h> 
#include <linux/kernel.h>  
#include <linux/cdev.h>  
#include <linux/device.h>  

#include "scdev.h" 

static struct file_operations fops = { 
  .owner = THIS_MODULE , 
  .open  = scdev_open , 
  .release = scdev_close,  
  .read  =  scdev_read , 
  .write =  scdev_write   
} ; 

static int scdev_mjn =0  ;  
static struct class  * scdev_class ; 

static char  scdev_buff[SCDEV_BUFFSIZE]  ; 



static int __init  scdev_main (void) {
  /**TODO :  use register_chrdev_region  and cdev  interface for next */ 

  scdev_mjn = register_chrdev(0 , SCDEV_TAG ,  &fops ) ;
  if (scdev_mjn <=~0) 
  {
    scdev_log_warn("kernel register satus event  fail  [KO] KnockOut!") ; 
    return _exit_failure;  
  }
  scdev_log("%s  : device registred  %i \n" ,  SCDEV_BASENAME ,  scdev_mjn ) ; 
  scdev_class =  class_create(THIS_MODULE, SCDEV_TAG) ; 
  if ( device_create (scdev_class , _nullable , MKDEV(scdev_mjn , 0) , _nullable , SCDEV_TAG ) == _nullable ) 
  {
    scdev_log("device_create : failure") ; 
    goto  SCDEV_DCERR ; 
  }

  return _exit_success ; 

SCDEV_DCERR: 
  class_destroy(scdev_class) ;
  unregister_chrdev(scdev_mjn , SCDEV_TAG) ; 
  return _exit_failure ; 
}

static void __exit scdev_exit(void) { 
  device_destroy(scdev_class , MKDEV(scdev_mjn , 0)) ; 
  class_destroy(scdev_class) ;
  unregister_chrdev(scdev_mjn , SCDEV_TAG) ; 
  
  scdev_log_warn("scdev unloaded") ; 
} 

static int scdev_open (struct  inode * _inode,  struct  file  * _file) { 
  
  scdev_log("device_open");   
  return _exit_success ; 
}

static int scdev_close(struct inode * _inode , struct  file * _file) { 
   
  
  scdev_log("device closed") ; 
  
  return _exit_success ; 
}

static ssize_t scdev_read (struct  file  * _file  , char __user  * _ubuff , size_t _ubuff_length , loff_t  * _offetcursor ) {

  ssize_t bytes_readed = 0 ;
  ssize_t _ubuff_length_ref  = 0 ; 
  //! we  admit that scdev_buff is already feeded 
  const  char  *mesg = (scdev_buff + *_offetcursor) ;   
  
  scdev_log_warn("%s:reading" ,  SCDEV_BASENAME) ; 
  if( !*mesg ) 
  {
   *_offetcursor= 0; 
    return  0;  
  }

  if (_ubuff_length > SCDEV_BUFFSIZE)  
  {
    scdev_log_warn("Adjust to max bytes allowed %i" , SCDEV_BUFFSIZE) ; 
    _ubuff_length  = SCDEV_BUFFSIZE ;  
  }
  
  _ubuff_length_ref = _ubuff_length ; 

  while (  *mesg && _ubuff_length >  0 ) 
  {
    bytes_readed++ ;  
    //mesg++ ; //! feed userspace buffer ... 
    _ubuff_length-- ; 
  } 

  *_offetcursor =  bytes_readed ; 
  //! check  if bytes_readed ==  _ubuff_length 
  
  if (bytes_readed == _ubuff_length_ref )  
  {
     scdev_log("Byte Read  OK") ;  
  }  

  if (bytes_readed < _ubuff_length_ref )  
  {
    scdev_log_warn("bytes readed") ; 
  }
  
  return bytes_readed ;  
}

static ssize_t scdev_write (struct  file  * _file  , const char __user  * _ubuff ,  size_t _ubuff_length , loff_t  * _offetcursor ) {

  scdev_log_warn("%s :  operation not yet suppported \n" ,  SCDEV_BASENAME) ; 
  return _exit_failure; 
}



module_init(scdev_main) ; 
module_exit(scdev_exit) ;  
