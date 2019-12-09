// #define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <stdio.h>
#include <X11/XKBlib.h>
#include <iostream>

#include "keymap.h"



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

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

inline void remap (const std::string & original, const std::string & remapped)
{
    custom_keymap[std_keymap[original]] = std_keymap[remapped];
}

void send_new_event(int fdo, int code)
{
    if (code != custom_keymap[code])
    {
        std::cout << "from: " << code << " to: " << custom_keymap[code] << std::endl;
        // sleep(1);
        emit(fdo, EV_KEY, KEY_BACKSPACE, 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, KEY_BACKSPACE, 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        // sleep(1);
        emit(fdo, EV_KEY, custom_keymap[code], 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, custom_keymap[code], 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        // sleep(1);
    }
    else
    {
        std::cout << "from: " << code << " to: " << code << std::endl;
        emit(fdo, EV_KEY, code, 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, code, 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
    }
}

void init_custom_keymap()
{
    for (auto & p : std_keymap)
        custom_keymap[p.second] = p.second;
}

int main(void)
{
   struct uinput_setup usetup;
    init_custom_keymap();
   int fdo = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

//    /*
//     * The ioctls below will enable the device that is about to be
//     * created, to pass key events, in this case the space key.
//     */
   ioctl(fdo, UI_SET_EVBIT, EV_KEY);
   for (auto & p: std_keymap)
    //    std::cout << p.second << std::endl;
      ioctl(fdo, UI_SET_KEYBIT, p.second);

   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x1234; /* sample vendor */
   usetup.id.product = 0x5678; /* sample product */
   strcpy(usetup.name, "Example device");

   ioctl(fdo, UI_DEV_SETUP, &usetup);
   ioctl(fdo, UI_DEV_CREATE);
   /*
    * On UI_DEV_CREATE the kernel will create the device node for this
    * device. We are inserting a pause here so that userspace has time
    * to detect, initialize the new device, and can start listening to
    * the event, otherwise it will not notice the event we are about
    * to send. This pause is only needed in our example code!
    */

    // auto custom_keymap = std_keymap;
    remap("KEY_A", "KEY_S");
    remap("KEY_S", "KEY_O");
    remap("KEY_D", "KEY_S");
    remap("KEY_F", "KEY_I");
    // for (auto & k: custom_keymap)
    // {
        // std::cout << k.first << " : " << k.second << std::endl;
    // }
    int fdi;
    const char * dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    fdi = open(dev, O_RDWR);
    if (fdi == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }
    struct input_event ev;
    ssize_t n;
    while (1) {
        n = read(fdi, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
            printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
            // ev.code = custom_keymap[ev.code];
            if (evval[ev.value] == "PRESSED ")
                send_new_event(fdo, ev.code);
            }

        }
    
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
   ioctl(fdo, UI_DEV_DESTROY);
   close(fdo);
   ioctl(fdi, UI_DEV_DESTROY);
   close(fdi);

    return EXIT_FAILURE;
}