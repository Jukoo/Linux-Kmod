
#include <linux/moduleparam.h> 

static int show_arch_discovery_log_mesg  = 1 ; /** by default it show the message on dmesg */ 
module_param(show_arch_discovery_log_mesg  , int , 0000) ; 
MODULE_PARM_DESC(show_arch_discovery_log_mesg, "optional prameter that  show  message on  log  by default is  > 0  othrewise the log is mutted") ;  



