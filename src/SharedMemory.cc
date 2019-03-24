/*
 * SharedMemory: Shared Memory Parallelism in GAP
 */

extern "C" {
#include "src/compiled.h"          /* GAP headers */
#include <sys/mman.h>
}

static Obj SHAREDMEMORY_Region_Type;

struct ShmRegion {
    Obj    type;
    size_t size;
    char   *data;
};

typedef struct ShmRegion * ShmRegionPtr;
typedef const struct ShmRegion * ConstShmRegionPtr;

static ShmRegionPtr SHAREDMEMORY_REGION(Obj region) {
    return (ShmRegionPtr)ADDR_OBJ(region);
}

static ConstShmRegionPtr CONST_SHAREDMEMORY_REGION(Obj region) {
    return (ConstShmRegionPtr)CONST_ADDR_OBJ(region);
}

Obj FuncMMAP_SHARED_MEMORY(Obj self, Obj size)
{
    RequireSmallInt("MMAP_SHARED_MEMORY", size, "size");

    size_t sz;
    Obj result;

    sz = INT_INTOBJ(size);

    result = NewBag(T_DATOBJ, sizeof(struct ShmRegion));
    SetTypeDatObj(result, SHAREDMEMORY_Region_Type);

    SHAREDMEMORY_REGION(result)->size = sz;
    SHAREDMEMORY_REGION(result)->data = (char *)mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,
               -1, 0);
    CHANGED_BAG(result);

    return result;
}

template <typename T>
Obj FuncSHARED_MEMORY_PEEK(Obj self, Obj region, Obj pos)
{
    RequireSmallInt("SHARED_MEMORY_PEEK", pos, "pos");

    T *mem = (T *)SHAREDMEMORY_REGION(region)->data;
    UInt8 upos = UInt8_ObjInt(pos);

    return ObjInt_UInt8((UInt8)(mem[upos]));
}

template <typename T> 
Obj FuncSHARED_MEMORY_POKE(Obj self, Obj region, Obj pos, Obj val)
{
    RequireSmallInt("SHARED_MEMORY_POKE", pos, "pos");

    UInt8 upos = UInt8_ObjInt(pos);
    T uval = (T)(UInt_ObjInt(val));

    *(T *)(&SHAREDMEMORY_REGION(region)->data[upos]) = uval;

    return 0;
}

Obj FuncSHARED_MEMORY_PEEK_STRING(Obj self, Obj region, Obj pos, Obj len)
{
    RequireSmallInt("SHARED_MEMORY_PEEK", pos, "pos");
    RequireSmallInt("SHARED_MEMORY_PEEK_STRING", len, "len");

    char *mem = SHAREDMEMORY_REGION(region)->data;
    UInt8 upos = UInt8_ObjInt(pos);
    UInt8 ulen = UInt8_ObjInt(len);

    return MakeStringWithLen(&mem[upos], ulen);
}

Obj FuncSHARED_MEMORY_POKE_STRING(Obj self, Obj region, Obj pos, Obj val)
{
    RequireSmallInt("SHARED_MEMORY_POKE", pos, "pos");
    RequireStringRep("SHARED_MEMORY_POKE", val);

    char *mem = SHAREDMEMORY_REGION(region)->data;
    UInt8 upos = UInt8_ObjInt(pos);
    UInt8 ulen = GET_LEN_STRING(val);

    memcpy(&mem[upos], CHARS_STRING(val), ulen);

    return 0;
}

// Table of functions to export
static StructGVarFunc GVarFuncs[] = {
    GVAR_FUNC(MMAP_SHARED_MEMORY, 1, "size"),
    GVAR_FUNC(SHARED_MEMORY_PEEK<Char>, 2, "shm, pos"),
    GVAR_FUNC(SHARED_MEMORY_PEEK<UInt2>, 2, "shm, pos"),
    GVAR_FUNC(SHARED_MEMORY_PEEK<UInt4>, 2, "shm, pos"),
    GVAR_FUNC(SHARED_MEMORY_PEEK<UInt8>, 2, "shm, pos"),
    GVAR_FUNC(SHARED_MEMORY_POKE<Char>, 3, "shm, pos, val"),
    GVAR_FUNC(SHARED_MEMORY_POKE<UInt2>, 3, "shm, pos, val"),
    GVAR_FUNC(SHARED_MEMORY_POKE<UInt4>, 3, "shm, pos, val"),
    GVAR_FUNC(SHARED_MEMORY_POKE<UInt8>, 3, "shm, pos, val"),
    GVAR_FUNC(SHARED_MEMORY_PEEK_STRING, 3, "shm, pos, length"),
    GVAR_FUNC(SHARED_MEMORY_POKE_STRING, 3, "shm, pos, string"),
    { 0 } /* Finish with an empty entry */
};

/****************************************************************************
**
*F  InitKernel( <module> ) . . . . . . . .  initialise kernel data structures
*/
static Int InitKernel( StructInitInfo *module )
{
    ImportGVarFromLibrary("SHAREDMEMORY_Region_Type", &SHAREDMEMORY_Region_Type);

    /* init filters and functions */
    InitHdlrFuncsFromTable( GVarFuncs );

    /* return success */
    return 0;
}

/****************************************************************************
**
*F  InitLibrary( <module> ) . . . . . . .  initialise library data structures
*/
static Int InitLibrary( StructInitInfo *module )
{
    /* init filters and functions */
    InitGVarFuncsFromTable( GVarFuncs );

    /* return success */
    return 0;
}

/****************************************************************************
**
*F  Init__Dynamic() . . . . . . . . . . . . . . . . . table of init functions
*/
static StructInitInfo module = {
    .type = MODULE_DYNAMIC,
    .name = "SharedMemory",
    .initKernel = InitKernel,
    .initLibrary = InitLibrary,
};

extern "C"
StructInitInfo *Init__Dynamic( void )
{
    return &module;
}
