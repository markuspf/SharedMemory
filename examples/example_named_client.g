LoadPackage("SharedMemory");

name := "/gap-is-awzum";
size := 1024 * 1024;
msg := "Hello, world";

Print("Getting and mapping region\n");
fd := SHARED_MEMORY_SHMOPEN(name, 2);
region := SHARED_MEMORY_MMAP(fd, size);

Print("Peeking some stuff from the region");
len := SHARED_MEMORY_PEEK\<UInt4\>(region, 0);
Print(" length of message: ", len, "\n");
rmsg := SHARED_MEMORY_PEEK_STRING(region, 4, len);
Print(" retrieved message: ", rmsg, "\n");

Print("polling counter: \n");
while true do
  MicroSleep(1000000);
  rcounter := SHARED_MEMORY_PEEK\<UInt4\>(region, 1024);
  Print(rcounter, " \c");
od; 
