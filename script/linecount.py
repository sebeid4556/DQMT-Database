import os

DIRECTORY = "../source"
CONSOLE_GREEN = "\x1b[32m"
CONSOLE_YELLOW = "\x1b[33m"
CONSOLE_WHITE = "\x1b[39m"

def main():
    global DIRECTORY
    global CONSOLE_GREEN
    global CONSOLE_YELLOW
    global CONSOLE_WHITE
    line_count = 0
    folder_count = 0
    file_count = 0
    print()
    for path, folders, files in os.walk(DIRECTORY):
        for folder in folders:
            folder_count += 1
        for filename in files:
            file_count += 1
            full = os.path.join(path, filename)
            with open(full, "rb") as f:
                buffer = f.read()                
                nls = 0
                for char in buffer:
                    if char == 0x0A: nls += 1
                total = (nls + 1)
                print("%s(%d bytes): %s%d%s lines" % (full, len(buffer), CONSOLE_GREEN, total, CONSOLE_WHITE))
                line_count += total
    print("\nTotal: %s%d%s\t\b\b\b\blines\n       %s%d%s\t\b\b\b\bfolders\n       %s%d%s\t\b\b\b\bfiles" %
          (CONSOLE_GREEN, line_count, CONSOLE_WHITE, CONSOLE_GREEN, folder_count, CONSOLE_WHITE, CONSOLE_GREEN, file_count, CONSOLE_WHITE))
            

if __name__ == "__main__":
    main()
