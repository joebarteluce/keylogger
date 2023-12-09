import sys

# handle args
if len(sys.argv) < 2:
    print("Usage: python3 parser.py [input_file] [optional: output_file]")
    exit()
input_file = str(sys.argv[1])
output_file = "log_parsed.txt"
if len(sys.argv) >= 3:
    output_file = str(sys.argv[2])

# thank you chatgpt for creating this key map dictionary
# tedious work
key_mappings = {
    "<1>": "1", "<2>": "2", "<3>": "3", "<4>": "4", "<5>": "5", 
    "<6>": "6", "<7>": "7", "<8>": "8", "<9>": "9", "<0>": "0",
    "<MINUS>": "-", "<EQUAL>": "=", "<BACKSPACE>": "<BACKSPACE>", 
    "<TAB>": "\t", "<Q>": "Q", "<W>": "W", "<E>": "E", "<R>": "R", 
    "<T>": "T", "<Y>": "Y", "<U>": "U", "<I>": "I", "<O>": "O", 
    "<P>": "P", "<LEFTBRACE>": "[", "<RIGHTBRACE>": "]", "<ENTER>": "\n",
    "<LEFTCTRL>": "<LEFTCTRL>", "<A>": "A", "<S>": "S", "<D>": "D", 
    "<F>": "F", "<G>": "G", "<H>": "H", "<J>": "J", "<K>": "K", 
    "<L>": "L", "<SEMICOLON>": ";", "<APOSTROPHE>": "'", "<GRAVE>": "`",
    "<LEFTSHIFT>": "<LEFTSHIFT>", "<BACKSLASH>": "\\", "<Z>": "Z", 
    "<X>": "X", "<C>": "C", "<V>": "V", "<B>": "B", "<N>": "N", 
    "<M>": "M", "<COMMA>": ",", "<DOT>": ".", "<SLASH>": "/", 
    "<RIGHTSHIFT>": "<RIGHTSHIFT>", "<KPASTERISK>": "*", "<LEFTALT>": "<LEFTALT>",
    "<SPACE>": " ", "<CAPSLOCK>": "<CAPSLOCK>", "<F1>": "<F1>", "<F2>": "<F2>", 
    "<F3>": "<F3>", "<F4>": "<F4>", "<F5>": "<F5>", "<F6>": "<F6>", 
    "<F7>": "<F7>", "<F8>": "<F8>", "<F9>": "<F9>", "<F10>": "<F10>", 
    "<NUMLOCK>": "<NUMLOCK>", "<SCROLLLOCK>": "<SCROLLLOCK>", "<KP7>": "7", 
    "<KP8>": "8", "<KP9>": "9", "<KPMINUS>": "-", "<KP4>": "4", 
    "<KP5>": "5", "<KP6>": "6", "<KPPLUS>": "+", "<KP1>": "1", 
    "<KP2>": "2", "<KP3>": "3", "<KP0>": "0", "<KPDOT>": ".", 
}

# load log into an array
log = open(input_file, "r")
log_ar = log.read().split('>')[:-1]
log.close()

# parse keystrokes, save to new array
unshifted = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./"
shifted = "~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?"
shift = False
caps = False
out = []
for keycode in log_ar:
    keycode = keycode + ">"

    if keycode == "<BACKSPACE>":
        out.pop()
    elif keycode == "<LEFTSHIFT>" or keycode == "<RIGHTSHIFT>":
        shift = True
    elif keycode == "<LEFTSHIFT_RELEASED>" or keycode == "<RIGHTSHIFT_RELEASED>":
        shift = False
    elif keycode == "<CAPSLOCK>":
        caps = not caps
    elif keycode in key_mappings.keys():
        val = key_mappings[keycode] 
        if val.lower() in unshifted:
            val = val.lower()
            if shift: val = shifted[unshifted.index(val)]
            if caps: val = val.upper()
        out.append(val)
    else:
        out.append(keycode)

# write the out array to file
with open(output_file, "w") as f:
    for s in out:
        f.write(s)
    f.write("\n")
