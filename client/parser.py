import sys

# handle args
if len(sys.argv) < 2:
    print("Usage: python3 parser.py [input_file] [optional: output_file]")
    exit()
input_file = str(sys.argv[1])
output_file = "log_parsed.txt"
if len(sys.argv) >= 3:
    output_file = str(sys.argv[2])

# some mappings defined
d = {}
d["ENTER"] = "\n"
d["SPACE"] = " "
d["DOT"] = "."
d["COMMA"] = ","
d["MINUS"] = "-"
d["PLUS"] = "+"

# load log into an array
log = open(input_file, "r")
log_ar = log.read().split('>')[:-1]
log.close()

# parse keystrokes, save to new array
out = []
for keycode in log_ar:
    keycode = keycode[1:]

    if keycode in d.keys():
        out.append(d[keycode])
    elif keycode == "BACKSPACE":
        out.pop()
    elif keycode.lower() in "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./":
        out.append(keycode.lower())
    else:
        out.append("<" + keycode + ">")

# write the out array to file
with open(output_file, "w") as f:
    for s in out:
        f.write(s)
    f.write("\n")
