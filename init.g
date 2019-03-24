#
# SharedMemory: Shared Memory Parallelism in GAP
#
# Reading the declaration part of the package.
#
_PATH_SO:=Filename(DirectoriesPackagePrograms("SharedMemory"), "SharedMemory.so");
if _PATH_SO <> fail then
    LoadDynamicModule(_PATH_SO);
fi;
Unbind(_PATH_SO);

ReadPackage( "SharedMemory", "gap/SharedMemory.gd");
