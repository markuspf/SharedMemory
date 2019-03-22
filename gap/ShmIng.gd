#
# ShmIng: Shared Memory Parallelism in GAP
#
#! @Chapter Introduction
#!
#! ShmIng is a package which does some
#! interesting and cool things
#!
#! @Chapter Functionality
#!
#!
#! @Section Example Methods
#!
#! This section will describe the example
#! methods of ShmIng

#!
DeclareCategory("IsSharedMemoryRegion", IsObject);
BindGlobal("SHMING_Region_Family", NewFamily("SHMING_Region_Family"));
BindGlobal("SHMING_Region_Type",
           NewType(SHMING_Region_Family, IsSharedMemoryRegion));
