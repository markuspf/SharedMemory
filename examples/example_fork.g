LoadPackage("IO");
LoadPackage("SharedMemory");

message := "Hello, world!";

# map 1 megabyte of shareable memory into the process' address
# space.
#
# "map" is to be understood literally: this command does *not*
# allocate (physical) memory, but creates a mapping in the process'
# address space. "actual" memory is allocated by the operating
# system as soon as it is used.
# 
# If the current process is forked (using IO_fork for example), this
# memory mapping is inherited by child processes who can subsequently
# read from and write to it: All descended processes share this bit
# of memory. 
o := SHARED_MEMORY_MMAP(-1, 1024 * 1024);

pid := IO_fork();
if pid <> 0 then
  SHARED_MEMORY_POKE\<UInt4\>(o, 0, Length(message));
  SHARED_MEMORY_POKE_STRING(o, 4, message);
  for i in [50..60] do
    SHARED_MEMORY_POKE\<Char\>(o, i, i);
  od;
  IO_WaitPid(pid, true);
  QUIT_GAP(0);
else
  Sleep(5);
  len := SHARED_MEMORY_PEEK\<UInt4\>(o, 0);
  Print("Message has length ", len, "\n");
  mem := SHARED_MEMORY_PEEK_STRING(o, 4, len);
  Print("message ", mem, "\c\n");
  for i in [50..60] do
    mem := SHARED_MEMORY_PEEK\<Char\>(o, i);
    Print(" ", mem, "\c");
  od;
  QUIT_GAP(0);
fi;


