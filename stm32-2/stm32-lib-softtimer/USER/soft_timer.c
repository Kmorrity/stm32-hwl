#include "soft_timer.h"

//timer handle list head.
static struct Timer* head_handle = 0;

//Timer ticks
static unsigned int _timer_ticks = 0;

/**
  * @brief  Initializes the timer struct handle.
  * @param  handle: the timer handle strcut.
  * @param  timeout_cb: timeout callback.
  * @param  repeat: repeat interval time.
  * @retval None
  */
void timer_init(struct Timer* handle, void(*timeout_cb)(), unsigned int timeout, unsigned int repeat)
{
    // memset(handle, sizeof(struct Timer), 0);
    handle->timeout_cb = timeout_cb;
    handle->timeout = _timer_ticks + timeout;
	handle->next = 0;
	
	if(repeat !=0) 
		handle->repeat = timeout;
	else
    	handle->repeat = 0;
}

/**
  * @brief  Start the timer work, add the handle into work list.
  * @param  btn: target handle strcut.
  * @retval 0: succeed. -1: already exist.
  */
int timer_start(struct Timer* handle)
{
    struct Timer* target = head_handle;
    while(target) {
        if(target == handle) return -1; //already exist.
        target = target->next;
    }
    handle->next = head_handle;
    head_handle = handle;
    return 0;
}

/**
  * @brief  Stop the timer work, remove the handle off work list.
  * @param  handle: target handle strcut.
  * @retval None
  */
void timer_stop(struct Timer* handle)
{
    struct Timer** curr;
    for(curr = &head_handle; *curr; ) {
        struct Timer* entry = *curr;
        if (entry == handle) {
            *curr = entry->next;
//          free(entry);
        } else
            curr = &entry->next;
    }
}

/**
  * @brief  main loop.
  * @param  None.
  * @retval None
  */
void timer_loop()
{
    struct Timer* target;
    for(target=head_handle; target; target=target->next) {
        if(  (int)target->timeout - (int)_timer_ticks <=0) {  //To prevent overflow
            if(target->repeat == 0) {
                timer_stop(target);
            } else {
                target->timeout = _timer_ticks + target->repeat;
            }
            target->timeout_cb();
        }
    }
}

/**
  * @brief  background ticks, timer repeat invoking interval 1ms.
  * @param  None.
  * @retval None.
  */
void timer_ticks()
{
    _timer_ticks++;
}

