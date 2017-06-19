#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "sb6.h"

/* glfw input keys converted to enumeration */

enum INPUT_KEY
{

	INPUT_SPACE           = 32,
	INPUT_APOSTROPHE      = 39,  /* ' */
	INPUT_COMMA           = 44,  /* , */
	INPUT_MINUS           = 45,  /* - */
	INPUT_PERIOD          = 46,  /* . */
	INPUT_SLASH           = 47,  /* / */
	INPUT_0               = 48,
	INPUT_1               = 49,
	INPUT_2               = 50,
	INPUT_3               = 51,
	INPUT_4               = 52,
	INPUT_5               = 53,
	INPUT_6               = 54,
	INPUT_7               = 55,
	INPUT_8               = 56,
	INPUT_9               = 57,
	INPUT_SEMICOLON       = 59,  /* ; */
	INPUT_EQUAL           = 61,  /* = */
	INPUT_A               = 65,
	INPUT_B               = 66,
	INPUT_C               = 67,
	INPUT_D               = 68,
	INPUT_E               = 69,
	INPUT_F               = 70,
	INPUT_G               = 71,
	INPUT_H               = 72,
	INPUT_I               = 73,
	INPUT_J               = 74,
	INPUT_K               = 75,
	INPUT_L               = 76,
	INPUT_M               = 77,
	INPUT_N               = 78,
	INPUT_O               = 79,
	INPUT_P               = 80,
	INPUT_Q               = 81,
	INPUT_R               = 82,
	INPUT_S               = 83,
	INPUT_T               = 84,
	INPUT_U               = 85,
	INPUT_V               = 86,
	INPUT_W               = 87,
	INPUT_X               = 88,
	INPUT_Y               = 89,
	INPUT_Z               = 90,
	INPUT_LEFT_BRACKET    = 91,  /* [ */
	INPUT_BACKSLASH       = 92,  /* \ */
	INPUT_RIGHT_BRACKET   = 93,  /* ] */
	INPUT_GRAVE_ACCENT    = 96,  /* ` */
	INPUT_WORLD_1         = 161, /* non-US #1 */
	INPUT_WORLD_2         = 162, /* non-US #2 */
	INPUT_ESCAPE          = 256,
	INPUT_ENTER           = 257,
	INPUT_TAB             = 258,
	INPUT_BACKSPACE       = 259,
	INPUT_INSERT          = 260,
	INPUT_DELETE          = 261,
	INPUT_RIGHT           = 262,
	INPUT_LEFT            = 263,
	INPUT_DOWN            = 264,
	INPUT_UP              = 265,
	INPUT_PAGE_UP         = 266,
	INPUT_PAGE_DOWN       = 267,
	INPUT_HOME            = 268,
	INPUT_END             = 269,
	INPUT_CAPS_LOCK       = 280,
	INPUT_SCROLL_LOCK     = 281,
	INPUT_NUM_LOCK        = 282,
	INPUT_PRINT_SCREEN    = 283,
	INPUT_PAUSE           = 284,
	INPUT_F1              = 290,
	INPUT_F2              = 291,
	INPUT_F3              = 292,
	INPUT_F4              = 293,
	INPUT_F5              = 294,
	INPUT_F6              = 295,
	INPUT_F7              = 296,
	INPUT_F8              = 297,
	INPUT_F9              = 298,
	INPUT_F10             = 299,
	INPUT_F11             = 300,
	INPUT_F12             = 301,
	INPUT_F13             = 302,
	INPUT_F14             = 303,
	INPUT_F15             = 304,
	INPUT_F16             = 305,
	INPUT_F17             = 306,
	INPUT_F18             = 307,
	INPUT_F19             = 308,
	INPUT_F20             = 309,
	INPUT_F21             = 310,
	INPUT_F22             = 311,
	INPUT_F23             = 312,
	INPUT_F24             = 313,
	INPUT_F25             = 314,
	INPUT_KP_0            = 320,
	INPUT_KP_1            = 321,
	INPUT_KP_2            = 322,
	INPUT_KP_3            = 323,
	INPUT_KP_4            = 324,
	INPUT_KP_5            = 325,
	INPUT_KP_6            = 326,
	INPUT_KP_7            = 327,
	INPUT_KP_8            = 328,
	INPUT_KP_9            = 329,
	INPUT_KP_DECIMAL      = 330,
	INPUT_KP_DIVIDE       = 331,
	INPUT_KP_MULTIPLY     = 332,
	INPUT_KP_SUBTRACT     = 333,
	INPUT_KP_ADD          = 334,
	INPUT_KP_ENTER        = 335,
	INPUT_KP_EQUAL        = 336,
	INPUT_LEFT_SHIFT      = 340,
	INPUT_LEFT_CONTROL    = 341,
	INPUT_LEFT_ALT        = 342,
	INPUT_LEFT_SUPER      = 343,
	INPUT_RIGHT_SHIFT     = 344,
	INPUT_RIGHT_CONTROL   = 345,
	INPUT_RIGHT_ALT       = 346,
	INPUT_RIGHT_SUPER     = 347,
	INPUT_MENU            = 348,

	INPUT_ARROW_UP		  = GLFW_KEY_UP, 
	INPUT_ARROW_DOWN	  = GLFW_KEY_DOWN,
	INPUT_ARROW_LEFT	  = GLFW_KEY_LEFT,
	INPUT_ARROW_RIGHT	  = GLFW_KEY_RIGHT

};

class Keyboard
{

public:
	Keyboard();

	/* used to read keyboard input */
	bool getKeyState(INPUT_KEY thisKey);

};
#endif // !KEYBOARD_H
