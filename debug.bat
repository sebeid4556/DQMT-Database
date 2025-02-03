cls
CALL build
cd debug
gdb main.exe -x "../gdb_commands.txt"
cd ..