# artificlock
A handmade clock

I have created this mini, RTC-like library because some of microcontroller have not a RTC unit. This handmade artifical clock doesn't include any internal timer for tick operation. You must supply a tick functionalty manually. For example, a timer/counter 1 second perioded may call tick_time() lib function. The lib has two function for user : init_time() and tick_time(). The first function is used for checking date_time struct instance that is passed as argument if it is valid or not and initilizing some of things. To increase time for struct just call tick_time() function. Of course, before than, you must call init_time() function firstly. 

Good luck.
