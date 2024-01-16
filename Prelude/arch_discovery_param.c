
#include <linux/moduleparam.h> 

static int show_archbits_info = 1 ; /** by default it show the message on dmesg */ 
module_param(show_archbits_info , int , 0000) ; 
MODULE_PARM_DESC(show_archbits_info, "optional prameter that  show  message on  log  by default is  > 0  othrewise the log is mutted") ;  



