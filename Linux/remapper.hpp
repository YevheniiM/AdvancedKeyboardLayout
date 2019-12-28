#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

#include <map>
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
#include <fstream>
#include <vector>


using namespace rapidjson;


class Remapper
{
    std::map<std::string, int> std_keymap =
            {
// {"KEY_RESERVED",		KEY_RESERVED},
// {"KEY_ESC",			KEY_ESC},
// {"KEY_1",			KEY_1},
// {"KEY_2",			KEY_2},
// {"KEY_3",			KEY_3},
// {"KEY_4",			KEY_4},
// {"KEY_5",			KEY_5},
// {"KEY_6",			KEY_6},
// {"KEY_7",			KEY_7},
// {"KEY_8",			KEY_8},
// {"KEY_9",			KEY_9},
// {"KEY_0",			KEY_0},
// {"KEY_MINUS",		KEY_MINUS},
// {"KEY_EQUAL",		KEY_EQUAL},
                    {"KEY_BACKSPACE", KEY_BACKSPACE},
// {"KEY_TAB",			KEY_TAB},
                    {"KEY_Q",         KEY_Q},
                    {"KEY_W",         KEY_W},
                    {"KEY_E",         KEY_E},
                    {"KEY_R",         KEY_R},
                    {"KEY_T",         KEY_T},
                    {"KEY_Y",         KEY_Y},
                    {"KEY_U",         KEY_U},
                    {"KEY_I",         KEY_I},
                    {"KEY_O",         KEY_O},
                    {"KEY_P",         KEY_P},
// {"KEY_LEFTBRACE",		KEY_LEFTBRACE},
// {"KEY_RIGHTBRACE",		KEY_RIGHTBRACE},
// {"KEY_ENTER",		KEY_ENTER},
// {"KEY_LEFTCTRL",		KEY_LEFTCTRL},
                    {"KEY_A",         KEY_A},
                    {"KEY_S",         KEY_S},
                    {"KEY_D",         KEY_D},
                    {"KEY_F",         KEY_F},
                    {"KEY_G",         KEY_G},
                    {"KEY_H",         KEY_H},
                    {"KEY_J",         KEY_J},
                    {"KEY_K",         KEY_K},
                    {"KEY_L",         KEY_L},
// {"KEY_SEMICOLON",		KEY_SEMICOLON},
// {"KEY_APOSTROPHE",		KEY_APOSTROPHE},
// {"KEY_GRAVE",		KEY_GRAVE},
// {"KEY_LEFTSHIFT",		KEY_LEFTSHIFT},
                    {"KEY_BACKSLASH", KEY_BACKSLASH},
                    {"KEY_Z",         KEY_Z},
                    {"KEY_X",         KEY_X},
                    {"KEY_C",         KEY_C},
                    {"KEY_V",         KEY_V},
                    {"KEY_B",         KEY_B},
                    {"KEY_N",         KEY_N},
                    {"KEY_M",         KEY_M},
                    {"KEY_COMMA",     KEY_COMMA},
                    {"KEY_DOT",       KEY_DOT},
                    {"KEY_SLASH",     KEY_SLASH},
// {"KEY_RIGHTSHIFT",		KEY_RIGHTSHIFT},
// {"KEY_KPASTERISK",		KEY_KPASTERISK},
// {"KEY_LEFTALT",		KEY_LEFTALT},
                    {"KEY_SPACE",     KEY_SPACE},
// {"KEY_CAPSLOCK",		KEY_CAPSLOCK},
// {"KEY_F1",			KEY_F1},
// {"KEY_F2",			KEY_F2},
// {"KEY_F3",			KEY_F3},
// {"KEY_F4",			KEY_F4},
// {"KEY_F5",			KEY_F5},
// {"KEY_F6",			KEY_F6},
// {"KEY_F7",			KEY_F7},
// {"KEY_F8",			KEY_F8},
// {"KEY_F9",			KEY_F9},
// {"KEY_F10",			KEY_F10},
// {"KEY_NUMLOCK",		KEY_NUMLOCK},
// {"KEY_SCROLLLOCK",		KEY_SCROLLLOCK},
// {"KEY_KP7",			KEY_KP7},
// {"KEY_KP8",			KEY_KP8},
// {"KEY_KP9",			KEY_KP9},
// {"KEY_KPMINUS",		KEY_KPMINUS},
// {"KEY_KP4",			KEY_KP4},
// {"KEY_KP5",			KEY_KP5},
// {"KEY_KP6",			KEY_KP6},
// {"KEY_KPPLUS",		KEY_KPPLUS},
// {"KEY_KP1",			KEY_KP1},
// {"KEY_KP2",			KEY_KP2},
// {"KEY_KP3",			KEY_KP3},
// {"KEY_KP0",			KEY_KP0},
// {"KEY_KPDOT",		KEY_KPDOT},
// {"KEY_ZENKAKUHANKAKU",	KEY_ZENKAKUHANKAKU},
// {"KEY_102ND",		KEY_102ND},
// {"KEY_F11",			KEY_F11},
// {"KEY_F12",			KEY_F12},
// {"KEY_RO",			KEY_RO},
// {"KEY_KATAKANA",		KEY_KATAKANA},
// {"KEY_HIRAGANA",		KEY_HIRAGANA},
// {"KEY_HENKAN",		KEY_HENKAN},
// {"KEY_KATAKANAHIRAGANA",	KEY_KATAKANAHIRAGANA},
// {"KEY_MUHENKAN",		KEY_MUHENKAN},
// {"KEY_KPJPCOMMA",		KEY_KPJPCOMMA},
// {"KEY_KPENTER",		KEY_KPENTER},
// {"KEY_RIGHTCTRL",		KEY_RIGHTCTRL},
// {"KEY_KPSLASH",		KEY_KPSLASH},
// {"KEY_SYSRQ",		KEY_SYSRQ},
// {"KEY_RIGHTALT",		KEY_RIGHTALT},
// {"KEY_LINEFEED",		KEY_LINEFEED},
// {"KEY_HOME",		KEY_HOME},
// {"KEY_UP",			KEY_UP},
// {"KEY_PAGEUP",		KEY_PAGEUP},
// {"KEY_LEFT",		KEY_LEFT},
// {"KEY_RIGHT",		KEY_RIGHT},
// {"KEY_END",			KEY_END},
// {"KEY_DOWN",		KEY_DOWN},
// {"KEY_PAGEDOWN",		KEY_PAGEDOWN},
// {"KEY_INSERT",		KEY_INSERT},
// {"KEY_DELETE",		KEY_DELETE},
// {"KEY_MACRO",		KEY_MACRO},
// {"KEY_MUTE",		KEY_MUTE},
// {"KEY_VOLUMEDOWN",		KEY_VOLUMEDOWN},
// {"KEY_VOLUMEUP",		KEY_VOLUMEUP},
// {"KEY_POWER",		KEY_POWER},
// {"KEY_KPEQUAL",		KEY_KPEQUAL},
// {"KEY_KPPLUSMINUS",		KEY_KPPLUSMINUS},
// {"KEY_PAUSE",		KEY_PAUSE},
// {"KEY_SCALE",		KEY_SCALE},
// {"KEY_KPCOMMA",		KEY_KPCOMMA},
// {"KEY_HANGEUL",		KEY_HANGEUL},
// {"KEY_HANGUEL",		KEY_HANGUEL},
// {"KEY_HANJA",		KEY_HANJA},
// {"KEY_YEN",			KEY_YEN},
// {"KEY_LEFTMETA",		KEY_LEFTMETA},
// {"KEY_RIGHTMETA",		KEY_RIGHTMETA},
// {"KEY_COMPOSE",		KEY_COMPOSE},
// {"KEY_STOP",		KEY_STOP},
// {"KEY_AGAIN",		KEY_AGAIN},
// {"KEY_PROPS",		KEY_PROPS},
// {"KEY_UNDO",		KEY_UNDO},
// {"KEY_FRONT",		KEY_FRONT},
// {"KEY_COPY",		KEY_COPY},
// {"KEY_OPEN",		KEY_OPEN},
// {"KEY_PASTE",		KEY_PASTE},
// {"KEY_FIND",		KEY_FIND},
// {"KEY_CUT",			KEY_CUT},
// {"KEY_HELP",		KEY_HELP},
// {"KEY_MENU",		KEY_MENU},
// {"KEY_CALC",		KEY_CALC},
// {"KEY_SETUP",		KEY_SETUP},
// {"KEY_SLEEP",		KEY_SLEEP},
// {"KEY_WAKEUP",		KEY_WAKEUP},
// {"KEY_FILE",		KEY_FILE},
// {"KEY_SENDFILE",		KEY_SENDFILE},
// {"KEY_DELETEFILE",		KEY_DELETEFILE},
// {"KEY_XFER",		KEY_XFER},
// {"KEY_PROG1",		KEY_PROG1},
// {"KEY_PROG2",		KEY_PROG2},
// {"KEY_WWW",			KEY_WWW},
// {"KEY_MSDOS",		KEY_MSDOS},
// {"KEY_COFFEE",		KEY_COFFEE},
// {"KEY_SCREENLOCK",		KEY_SCREENLOCK},
// {"KEY_ROTATE_DISPLAY",	KEY_ROTATE_DISPLAY},
// {"KEY_DIRECTION",		KEY_DIRECTION},
// {"KEY_CYCLEWINDOWS",	KEY_CYCLEWINDOWS},
// {"KEY_MAIL",		KEY_MAIL},
// {"KEY_BOOKMARKS",		KEY_BOOKMARKS},
// {"KEY_COMPUTER",		KEY_COMPUTER},
// {"KEY_BACK",		KEY_BACK},
// {"KEY_FORWARD",		KEY_FORWARD},
// {"KEY_CLOSECD",		KEY_CLOSECD},
// {"KEY_EJECTCD",		KEY_EJECTCD},
// {"KEY_EJECTCLOSECD",	KEY_EJECTCLOSECD},
// {"KEY_NEXTSONG",		KEY_NEXTSONG},
// {"KEY_PLAYPAUSE",		KEY_PLAYPAUSE},
// {"KEY_PREVIOUSSONG",	KEY_PREVIOUSSONG},
// {"KEY_STOPCD",		KEY_STOPCD},
// {"KEY_RECORD",		KEY_RECORD},
// {"KEY_REWIND",		KEY_REWIND},
// {"KEY_PHONE",		KEY_PHONE},
// {"KEY_ISO",			KEY_ISO},
// {"KEY_CONFIG",		KEY_CONFIG},
// {"KEY_HOMEPAGE",		KEY_HOMEPAGE},
// {"KEY_REFRESH",		KEY_REFRESH},
// {"KEY_EXIT",		KEY_EXIT},
// {"KEY_MOVE",		KEY_MOVE},
// {"KEY_EDIT",		KEY_EDIT},
// {"KEY_SCROLLUP",		KEY_SCROLLUP},
// {"KEY_SCROLLDOWN",		KEY_SCROLLDOWN},
// {"KEY_KPLEFTPAREN",		KEY_KPLEFTPAREN},
// {"KEY_KPRIGHTPAREN",	KEY_KPRIGHTPAREN},
// {"KEY_NEW",			KEY_NEW},
// {"KEY_REDO",		KEY_REDO},
// {"KEY_F13",			KEY_F13},
// {"KEY_F14",			KEY_F14},
// {"KEY_F15",			KEY_F15},
// {"KEY_F16",			KEY_F16},
// {"KEY_F17",			KEY_F17},
// {"KEY_F18",			KEY_F18},
// {"KEY_F19",			KEY_F19},
// {"KEY_F20",			KEY_F20},
// {"KEY_F21",			KEY_F21},
// {"KEY_F22",			KEY_F22},
// {"KEY_F23",			KEY_F23},
// {"KEY_F24",			KEY_F24},
// {"KEY_PLAYCD",		KEY_PLAYCD},
// {"KEY_PAUSECD",		KEY_PAUSECD},
// {"KEY_PROG3",		KEY_PROG3},
// {"KEY_PROG4",		KEY_PROG4},
// {"KEY_DASHBOARD",		KEY_DASHBOARD},
// {"KEY_SUSPEND",		KEY_SUSPEND},
// {"KEY_CLOSE",		KEY_CLOSE},
// {"KEY_PLAY",		KEY_PLAY},
// {"KEY_FASTFORWARD",		KEY_FASTFORWARD},
// {"KEY_BASSBOOST",		KEY_BASSBOOST},
// {"KEY_PRINT",		KEY_PRINT},
// {"KEY_HP",			KEY_HP},
// {"KEY_CAMERA",		KEY_CAMERA},
// {"KEY_SOUND",		KEY_SOUND},
// {"KEY_QUESTION",		KEY_QUESTION},
// {"KEY_EMAIL",		KEY_EMAIL},
// {"KEY_CHAT",		KEY_CHAT},
// {"KEY_SEARCH",		KEY_SEARCH},
// {"KEY_CONNECT",		KEY_CONNECT},
// {"KEY_FINANCE",		KEY_FINANCE},
// {"KEY_SPORT",		KEY_SPORT},
// {"KEY_SHOP",		KEY_SHOP},
// {"KEY_ALTERASE",		KEY_ALTERASE},
// {"KEY_CANCEL",		KEY_CANCEL},
// {"KEY_BRIGHTNESSDOWN",	KEY_BRIGHTNESSDOWN},
// {"KEY_BRIGHTNESSUP",	KEY_BRIGHTNESSUP},
// {"KEY_MEDIA",		KEY_MEDIA},
// {"KEY_SWITCHVIDEOMODE",	KEY_SWITCHVIDEOMODE},
// {"KEY_KBDILLUMTOGGLE",	KEY_KBDILLUMTOGGLE},
// {"KEY_KBDILLUMDOWN",	KEY_KBDILLUMDOWN},
// {"KEY_KBDILLUMUP",		KEY_KBDILLUMUP},
// {"KEY_SEND",		KEY_SEND},
// {"KEY_REPLY",		KEY_REPLY},
// {"KEY_FORWARDMAIL",		KEY_FORWARDMAIL},
// {"KEY_SAVE",		KEY_SAVE},
// {"KEY_DOCUMENTS",		KEY_DOCUMENTS},
// {"KEY_BATTERY",		KEY_BATTERY},
// {"KEY_BLUETOOTH",		KEY_BLUETOOTH},
// {"KEY_WLAN",		KEY_WLAN},
// {"KEY_UWB",			KEY_UWB},
// {"KEY_UNKNOWN",		KEY_UNKNOWN},
// {"KEY_VIDEO_NEXT",		KEY_VIDEO_NEXT},
// {"KEY_VIDEO_PREV",		KEY_VIDEO_PREV},
// {"KEY_BRIGHTNESS_CYCLE",	KEY_BRIGHTNESS_CYCLE},
// {"KEY_BRIGHTNESS_AUTO",	KEY_BRIGHTNESS_AUTO},
// {"KEY_BRIGHTNESS_ZERO",	KEY_BRIGHTNESS_ZERO},
// {"KEY_DISPLAY_OFF",		KEY_DISPLAY_OFF},
// {"KEY_WWAN",		KEY_WWAN},
// {"KEY_WIMAX",		KEY_WIMAX},
// {"KEY_RFKILL",		KEY_RFKILL},
// {"KEY_MICMUTE",		KEY_MICMUTE}
            };

    std::map<int, int> custom_keymap;
    int fdi;
    int fdo = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
//    int fdi = fdo;
    struct input_event ev{};
    ssize_t n{};
    struct uinput_setup usetup{};

    const char *const evval[3] = {
            "RELEASED",
            "PRESSED ",
            "REPEATED"
    };

    using RemapperConf = struct RemapperConf
    {
        enum RemapMode
        {
            LONG_PRESS, MULTIPLE_PRESS
        };
        std::map<std::string, RemapMode> remap_mode_str2enum{
                {"long_press",     LONG_PRESS},
                {"LongPress",      LONG_PRESS},
                {"multiple_press", MULTIPLE_PRESS},
                {"MultiplePress",  MULTIPLE_PRESS},
        };

        int remapper_pid{};
        std::map<std::string, std::vector<std::string>> keymap{};
        RemapMode mode{LONG_PRESS};
        int remap_conf_value{};

        RemapperConf() = default;


        RemapperConf(const Document &d) :
                remapper_pid{d["id"].GetInt()},
                mode{remap_mode_str2enum[d["mode"].GetObject()["type"].GetString()]},
                remap_conf_value{d["mode"].GetObject()["value"].GetInt()}
        {
            for (auto doc_it = d["keymap"].MemberBegin(); doc_it != d["keymap"].MemberEnd(); ++doc_it)
                keymap[doc_it->name.GetString()] = array2vector(doc_it);
        }


        std::vector<std::string> array2vector(const rapidjson::Document::ConstMemberIterator &doc_it)
        {
//          rapidjson::Array to std::vector
            std::vector<std::string> remaps{};
            auto remaps_array = doc_it->value.GetArray();
            remaps.reserve(remaps_array.Size());
            for (auto i = 0; i < remaps_array.Size(); ++i)
                remaps.emplace_back(remaps_array[i].GetString());
            return remaps;
        }
    };


    RemapperConf confs_from_json(const std::string &json_file_name)
    {
        std::ifstream ifs(json_file_name);
        IStreamWrapper isw(ifs);

        Document d;
        d.ParseStream(isw);

        return {d};
    }


    inline void init_custom_keymap()
    {
        for (auto &p : std_keymap)
            custom_keymap[p.second] = p.second;
    }


    inline void setup_user_input()
    {
        memset(&usetup, 0, sizeof(usetup));
        usetup.id.bustype = BUS_USB;
        usetup.id.vendor = 0x1234; /* sample vendor */
        usetup.id.product = 0x5678; /* sample product */
        strcpy(usetup.name, "Example device");
    }


    inline void enable_input_changing()
    {
        ioctl(fdo, UI_SET_EVBIT, EV_KEY);
        for (auto &p: std_keymap)
            ioctl(fdo, UI_SET_KEYBIT, p.second);
        ioctl(fdo, UI_DEV_SETUP, &usetup);
        ioctl(fdo, UI_DEV_CREATE);
    }


public:

    Remapper()
    {
//        strict order
        init_custom_keymap();
        setup_user_input();
        enable_input_changing();

        auto confs = confs_from_json("../test.json");

        /*
         * On UI_DEV_CREATE the kernel will create the device node for this
         * device. We are inserting a pause here so that userspace has time
         * to detect, initialize the new device, and can start listening to
         * the event, otherwise it will not notice the event we are about
         * to send. This pause is only needed in our example code!
         */
        const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
//        const char *dev = "/dev/input/event4";
        fdi = open(dev, O_RDWR);
        if (fdi == -1)
        {
            fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
//             return EXIT_FAILURE;
        }
    }


    ~Remapper()
    {
        fflush(stdout);
        fprintf(stderr, "%s.\n", strerror(errno));
        ioctl(fdo, UI_DEV_DESTROY);
        close(fdo);
        ioctl(fdi, UI_DEV_DESTROY);
        close(fdi);
    }


    void listen()
    {
        while (true)
        {
            n = read(fdi, &ev, sizeof ev);
            if (n == (ssize_t) -1)
            {
                if (errno == EINTR)
                    continue;
                else
                    break;
            }
            else if (n != sizeof ev)
            {
                errno = EIO;
                break;
            }
            if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2)
            {
                printf("%s 0x%04x (%d)\n", evval[ev.value], (int) ev.code, (int) ev.code);
                // ev.code = custom_keymap[ev.code];
                std::cout << "sec" << ev.time.tv_sec
                          << "usec" << ev.time.tv_usec << std::endl;

                if (evval[ev.value] == "PRESSED ")
                    send_new_event(fdo, ev.code);
            }
        }
    }


    inline void remap(const std::string &original, const std::string &remapped)
    {
        custom_keymap[std_keymap[original]] = std_keymap[remapped];
    }


private:
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

};