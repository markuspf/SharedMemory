# The GAP package SharedMemory

This package provides shared memory primitives for GAP. Used in combination with
`IO_fork`, it can be used to build more sophisticated and powerful parallelisation
and concurrency frameworks.

The current basic way of using this package is as follows

```
LoadPackage("IO");
LoadPackage("SharedMemory");

message := "Hello, world!";

# Create 1 Megabyte of shared memory
o := MMAP_SHARED_MEMORY(1024 * 1024);

pid := IO_fork();
if pid <> 0 then
  # Store the length of the string in the shared memory array
  SHARED_MEMORY_POKE1(o, 0, Length(message));
  # Store a message in the shared memory array
  SHARED_MEMORY_POKE_STRING(o, 1, message);
  # dump some other junk in it
  for i in [50..60] do
    SHARED_MEMORY_POKE\<Char\>(o, i, i);
  od;
  IO_WaitPid(pid, true);
  QUIT_GAP(0);
else
  # Make sure messages have arrived
  Sleep(5);
  len := SHARED_MEMORY_PEEK\<Char\>(o, 0);
  Print("Message has length ", len, "\n");
  mem := SHARED_MEMORY_PEEK_STRING(o, 0, len);
  Print("message ", mem, "\c\n");
  for i in [50..60] do
    mem := SHARED_MEMORY_PEEK1(o, i);
    Print(" ", mem, "\c");
  od;
  QUIT_GAP(0);
fi;
```

## Bug reports and feature requests

Please submit bug reports and feature requests via our GitHub issue tracker:

  <https://github.com/markuspf/SharedMemory/issues>

## License

SharedMemory is free software; you can redistribute it and/or modify it under
the terms of the BSD 3-clause license.

For details see the files COPYRIGHT.md and LICENSE.


