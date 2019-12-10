#include "customhooklinux.h"

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;
    // std::cout << "sending: " << code << std::endl
   write(fd, &ie, sizeof(ie));
}
