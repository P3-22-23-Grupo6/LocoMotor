#pragma once
#ifndef _LM_INPUTS
#define _LM_INPUTS
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

enum LMKeyboard {
    LMK_UNKNOWN = 0,

    LMK_RETURN = '\r',
    LMK_ESCAPE = '\x1B',
    LMK_BACKSPACE = '\b',
    LMK_TAB = '\t',
    LMK_SPACE = ' ',
    LMK_EXCLAIM = '!',
    LMK_QUOTEDBL = '"',
    LMK_HASH = '#',
    LMK_PERCENT = '%',
    LMK_DOLLAR = '$',
    LMK_AMPERSAND = '&',
    LMK_QUOTE = '\'',
    LMK_LEFTPAREN = '(',
    LMK_RIGHTPAREN = ')',
    LMK_ASTERISK = '*',
    LMK_PLUS = '+',
    LMK_COMMA = ',',
    LMK_MINUS = '-',
    LMK_PERIOD = '.',
    LMK_SLASH = '/',
    LMK_0 = '0',
    LMK_1 = '1',
    LMK_2 = '2',
    LMK_3 = '3',
    LMK_4 = '4',
    LMK_5 = '5',
    LMK_6 = '6',
    LMK_7 = '7',
    LMK_8 = '8',
    LMK_9 = '9',
    LMK_COLON = ':',
    LMK_SEMICOLON = ';',
    LMK_LESS = '<',
    LMK_EQUALS = '=',
    LMK_GREATER = '>',
    LMK_QUESTION = '?',
    LMK_AT = '@',

    /*
       Skip uppercase letters
     */

    LMK_LEFTBRACKET = '[',
    LMK_BACKSLASH = '\\',
    LMK_RIGHTBRACKET = ']',
    LMK_CARET = '^',
    LMK_UNDERSCORE = '_',
    LMK_BACKQUOTE = '`',
    LMK_a = 'a',
    LMK_b = 'b',
    LMK_c = 'c',
    LMK_d = 'd',
    LMK_e = 'e',
    LMK_f = 'f',
    LMK_g = 'g',
    LMK_h = 'h',
    LMK_i = 'i',
    LMK_j = 'j',
    LMK_k = 'k',
    LMK_l = 'l',
    LMK_m = 'm',
    LMK_n = 'n',
    LMK_o = 'o',
    LMK_p = 'p',
    LMK_q = 'q',
    LMK_r = 'r',
    LMK_s = 's',
    LMK_t = 't',
    LMK_u = 'u',
    LMK_v = 'v',
    LMK_w = 'w',
    LMK_x = 'x',
    LMK_y = 'y',
    LMK_z = 'z',

    LMK_CAPSLOCK = 1073741881,

    LMK_F1 = 1073741882,
    LMK_F2 = 1073741883,
    LMK_F3 = 1073741884,
    LMK_F4 = 1073741885,
    LMK_F5 = 1073741886,
    LMK_F6 = 1073741887,
    LMK_F7 = 1073741888,
    LMK_F8 = 1073741889,
    LMK_F9 = 1073741890,
    LMK_F10 = 1073741891,
    LMK_F11 = 1073741892,
    LMK_F12 = 1073741893,

    LMK_PRINTSCREEN = 1073741894,
    LMK_SCROLLLOCK = 1073741895,
    LMK_PAUSE = 1073741896,
    LMK_INSERT = 1073741897,
    LMK_HOME = 1073741898,
    LMK_PAGEUP = 1073741899,
    LMK_DELETE = '\x7F',
    LMK_END = 1073741901,
    LMK_PAGEDOWN = 1073741902,
    LMK_RIGHT = 1073741903,
    LMK_LEFT = 1073741904,
    LMK_DOWN = 1073741905,
    LMK_UP = 1073741906,

    LMK_NUMLOCKCLEAR = 1073741907,
    LMK_KP_DIVIDE = 1073741908,
    LMK_KP_MULTIPLY = 1073741909,
    LMK_KP_MINUS = 1073741910,
    LMK_KP_PLUS = 1073741911,
    LMK_KP_ENTER = 1073741912,
    LMK_KP_1 = 1073741913,
    LMK_KP_2 = 1073741914,
    LMK_KP_3 = 1073741915,
    LMK_KP_4 = 1073741916,
    LMK_KP_5 = 1073741917,
    LMK_KP_6 = 1073741918,
    LMK_KP_7 = 1073741919,
    LMK_KP_8 = 1073741920,
    LMK_KP_9 = 1073741921,
    LMK_KP_0 = 1073741922,
    LMK_KP_PERIOD = 1073741923,

   
    LMK_KP_TAB = 1073742010,
    LMK_KP_BACKSPACE = 1073742011,

    LMK_KP_COLON = 1073742027,
    LMK_KP_HASH = 1073742028,
    LMK_KP_SPACE = 1073742029,


    LMK_LCTRL = 1073742048,
    LMK_LSHIFT = 1073742049,
    LMK_LALT = 1073742050,
    LMK_LGUI = 1073742051,
    LMK_RCTRL = 1073742052,
    LMK_RSHIFT = 1073742053,
    LMK_RALT = 1073742054,
    LMK_RGUI = 1073742055,

    LMK_MODE = 1073742081,
};
enum Controller {
    

};
enum Gyro {

};



#endif