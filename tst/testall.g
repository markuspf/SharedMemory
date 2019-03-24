#
# SharedMemory: Shared Memory Parallelism in GAP
#
# This file runs package tests. It is also referenced in the package
# metadata in PackageInfo.g.
#
LoadPackage( "SharedMemory" );

TestDirectory(DirectoriesPackageLibrary( "SharedMemory", "tst" ),
  rec(exitGAP := true));

FORCE_QUIT_GAP(1); # if we ever get here, there was an error
