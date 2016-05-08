
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>


/*
 * find the middle queue element if the queue has odd number of elements
 * or the first element of the queue's second part otherwise
 */

ngx_queue_t *
ngx_queue_middle(ngx_queue_t *queue)
{
    ngx_queue_t  *middle, *next;

    middle = ngx_queue_head(queue);

    if (middle == ngx_queue_last(queue)) {
        return middle;
    }

    next = ngx_queue_head(queue);

    /* 快慢指针法寻找中间节点 */
    for ( ;; ) {
        middle = ngx_queue_next(middle);

        next = ngx_queue_next(next);

        /* 假设k个循环时，这里next等于last,那么一共是2k个节点
         * 而middle走了k个，出发时是从head,所以一共走了k+1个。*/
        if (next == ngx_queue_last(queue)) {
            return middle;
        }

        next = ngx_queue_next(next);

        /* 假设k个循环时，这里next等于last，那么一共是2k+1个节点
         * 而Middle走了k+1个，*/
        if (next == ngx_queue_last(queue)) {
            return middle;
        }
    }
}


/* the stable insertion sort
* 比如 3->1->2->4 链表
* 排序后的链表以1->2->3->4->5的形式
* */
void
ngx_queue_sort(ngx_queue_t *queue,
    ngx_int_t (*cmp)(const ngx_queue_t *, const ngx_queue_t *))
{
    ngx_queue_t  *q, *prev, *next;

    q = ngx_queue_head(queue);

    if (q == ngx_queue_last(queue)) {
        return;
    }
    /* 循环不变量为，q之前的链表是有序的，
     * 初始时链表只有一个元素，所以循环不变量保持
     * 假设某次循环不变量保持，进入循环语句判断是否循环不变量
     * 仍然不变。
     * 终止时。。。*/
    for (q = ngx_queue_next(q); q != ngx_queue_sentinel(queue); q = next) {

        prev = ngx_queue_prev(q);
        next = ngx_queue_next(q);

        ngx_queue_remove(q);

        do {
            /* 如果prev 小于等于q则退出do循环
             * 否则prev 后退一位。*/
            if (cmp(prev, q) <= 0) {
                break;
            }

            prev = ngx_queue_prev(prev);

        } while (prev != ngx_queue_sentinel(queue));

        /* 将q插入prev的后面
         * insert_after(q, x)等于insert_head(q, x), head中的q表示链表容器，
         * after中的q表示链表里面的某一个元素。
         *  */
        ngx_queue_insert_after(prev, q);
    }
}
