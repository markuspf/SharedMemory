#
# ShmIng: Shared Memory Parallelism in GAP
#
# This file contains package meta data. For additional information on
# the meaning and correct usage of these fields, please consult the
# manual of the "Example" package as well as the comments in its
# PackageInfo.g file.
#
SetPackageInfo( rec(

PackageName := "ShmIng",
Subtitle := "Shared Memory Parallelism in GAP",
Version := "0.1",
Date := "22/03/2019", # dd/mm/yyyy format
License := "GPL-2.0-or-later",

Persons := [
  rec(
    FirstNames := "Markus",
    LastName := "Pfeiffer",
    WWWHome := "https://markusp.morphism.de/",
    Email := "markus.pfeiffer@st-andrews.ac.uk",
    IsAuthor := true,
    IsMaintainer := true,
    PostalAddress := Concatenation(
               "School of Computer Science\n",
               "University of St Andrews\n",
               "Jack Cole Building, North Haugh\n",
               "St Andrews, Fife, KY16 9SX\n",
               "United Kingdom" ),
    Place := "St Andrews",
    Institution := "University of St Andrews",
  ),
],

SourceRepository := rec(
    Type := "git",
    URL := "https://github.com/markuspf/ShmIng",
),
IssueTrackerURL := Concatenation( ~.SourceRepository.URL, "/issues" ),
PackageWWWHome  := "https://markuspf.github.io/ShmIng/",
PackageInfoURL  := Concatenation( ~.PackageWWWHome, "PackageInfo.g" ),
README_URL      := Concatenation( ~.PackageWWWHome, "README.md" ),
ArchiveURL      := Concatenation( ~.SourceRepository.URL,
                                 "/releases/download/v", ~.Version,
                                 "/", ~.PackageName, "-", ~.Version ),

ArchiveFormats := ".tar.gz",

##  Status information. Currently the following cases are recognized:
##    "accepted"      for successfully refereed packages
##    "submitted"     for packages submitted for the refereeing
##    "deposited"     for packages for which the GAP developers agreed
##                    to distribute them with the core GAP system
##    "dev"           for development versions of packages
##    "other"         for all other packages
##
Status := "dev",

AbstractHTML   :=  "",

PackageDoc := rec(
  BookName  := "ShmIng",
  ArchiveURLSubset := ["doc"],
  HTMLStart := "doc/chap0.html",
  PDFFile   := "doc/manual.pdf",
  SixFile   := "doc/manual.six",
  LongTitle := "Shared Memory Parallelism in GAP",
),

Dependencies := rec(
  GAP := ">= 4.9",
  NeededOtherPackages := [ ],
  SuggestedOtherPackages := [ ],
  ExternalConditions := [ ],
),

AvailabilityTest := function()
  local dir, lib;
  dir := DirectoriesPackagePrograms("ShmIng");
  lib := Filename(dir, "ShmIng.so");
  if lib = fail then
    LogPackageLoadingMessage(PACKAGE_WARNING,
                             "failed to load kernel module of package ShmIng");
    return fail;
  fi;
  return true;
end,

TestFile := "tst/testall.g",

#Keywords := [ "TODO" ],

));


