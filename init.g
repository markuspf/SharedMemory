#
# ShmIng: Shared Memory Parallelism in GAP
#
# Reading the declaration part of the package.
#
_PATH_SO:=Filename(DirectoriesPackagePrograms("ShmIng"), "ShmIng.so");
if _PATH_SO <> fail then
    LoadDynamicModule(_PATH_SO);
fi;
Unbind(_PATH_SO);

ReadPackage( "ShmIng", "gap/ShmIng.gd");
