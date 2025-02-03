cls
CALL build
cd build
gdb main.exe -x "../gdb_commands.txt"
cd ..