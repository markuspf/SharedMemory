LoadPackage("SharedMemory");

size := 1024 * 1024;
msg := "Hello, world";

Print("Creating region\n");
fd := SHARED_MEMORY_SHMOPEN("/gap-is-awzum", 66);
SHARED_MEMORY_FTRUNCATE(fd, size);
region := SHARED_MEMORY_MMAP(fd, size);

Print("Dumping some stuff into the region");
SHARED_MEMORY_POKE\<UInt4\>(region, 0, Length(msg));
SHARED_MEMORY_POKE_STRING(region, 4, msg);

counter := 0;
while true do
  Sleep(1);
  Print("counter is: ", counter, "\n");
  SHARED_MEMORY_POKE\<Char\>(region, 1024, counter);
  pp := SHARED_MEMORY_PEEK\<Char\>(region, 1024);
  Print("pp: ", pp, "\n");
  counter := counter + 1;
od; 
