#
# SharedMemory: Shared Memory Parallelism in GAP
#
#! @Chapter Introduction
#!
#! SharedMemory is a package which does some
#! interesting and cool things
#!
#! @Chapter Functionality
#!
#!
#! @Section Example Methods
#!
#! This section will describe the example
#! methods of SharedMemory

#!
DeclareCategory("IsSharedMemoryRegion", IsObject);
BindGlobal("SHAREDMEMORY_Region_Family", NewFamily("SHAREDMEMORY_Region_Family"));
BindGlobal("SHAREDMEMORY_Region_Type",
           NewType(SHAREDMEMORY_Region_Family, IsSharedMemoryRegion));
