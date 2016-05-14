#Nginx
这是我自己阅读Nginx源码，对其中的一些部分加上注释，一是为了记录自己的理解，而是为了学习Nginx。
只要自己觉得有些难理解的都会加上自己思考时的注释，github上有另外一份注释版本，但是那部分对我来说有些简洁，而且似乎跟我现在学习使用的书籍的注释一模一样。
## code style
1. _s 表示struct, _t表示type: 习惯写法：
```
typedef struct ngx_list_part_s ngx_list_part_t;
struct ngx_list_part_s {
    void            *elts;
    ngx_uint_t       nelts;
    ngx_list_part_t *next;
```
2. elts 数组的起始地址，可能表示element start的意思。
##进度
1. 完成ngx_queue.c 
许多函数其实宏，其中ngx_queue_insert_after 就是ngx_queue_insert_head
2. 完成ngx_list.c

####参考资料
《深入理解Nginx》 陶晖 第二版
