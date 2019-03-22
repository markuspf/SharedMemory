/*
 * ShmIng: Shared Memory Parallelism in GAP
 */

#include "src/compiled.h"          /* GAP headers */
#include <sys/mman.h>


static Obj SHMING_Region_Type;

static const void * GET_SHMING_OBJ_REGION_PTR(Obj region) {
    return (const void *)(&ADDR_OBJ(region)[1]);
}

static void SET_SHMING_OBJ_REGION_PTR(Obj region, void* ptr) {
    ADDR_OBJ(region)[1] = ptr;
}


Obj FuncCREATE_SHARED_MEMORY(Obj self, Obj size)
{
    return INTOBJ_INT(42);
}

Obj FuncSHARED_MEMORY_PEEK(Obj self, Obj region, Obj pos)
{
    RequireSmallInt("SHARED_MEMORY_PEEK", pos, "pos");

    UInt8 *mem = (UInt8*)(GET_SHMING_OBJ_REGION_PTR(region));
    UInt8 upos = UInt8_ObjInt(pos);

    return ObjInt_UInt8(mem[upos]);
}

Obj FuncSHARED_MEMORY_POKE(Obj self, Obj region, Obj pos, Obj val)
{
    RequireSmallInt("SHARED_MEMORY_POKE", pos, "pos");

    UInt8* mem = (UInt8 *)(GET_SHMING_OBJ_REGION_PTR(region));
    UInt8 upos = UInt8_ObjInt(pos);
    UInt8 uval = UInt8_ObjInt(val);

    mem[upos] = uval;

    return 0;
}

Obj FuncMMAP_SHARED_MEMORY(Obj self, Obj size)
{
    size_t sz;
    void * mem;
    Obj result;

    RequireSmallInt("MMAP_SHARED_MEMORY", size, "size");
    sz = INT_INTOBJ(size);

    result = NewBag(T_DATOBJ, sizeof(UInt4) + sizeof(void*));
    SetTypeDatObj(result, SHMING_Region_Type);

    mem = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,
               0, 0);

    SET_SHMING_OBJ_REGION_PTR(result, mem);

    return result;
}

// Table of functions to export
static StructGVarFunc GVarFuncs[] = {
    GVAR_FUNC(MMAP_SHARED_MEMORY, 1, "size"),
    GVAR_FUNC(CREATE_SHARED_MEMORY, 0, ""),
    GVAR_FUNC(SHARED_MEMORY_PEEK, 2, "shm, pos"),
    GVAR_FUNC(SHARED_MEMORY_POKE, 3, "shm, pos, val"),
    { 0 } /* Finish with an empty entry */
};

/****************************************************************************
**
*F  InitKernel( <module> ) . . . . . . . .  initialise kernel data structures
*/
static Int InitKernel( StructInitInfo *module )
{
    ImportGVarFromLibrary("SHMING_Region_Type", &SHMING_Region_Type);

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
    .name = "ShmIng",
    .initKernel = InitKernel,
    .initLibrary = InitLibrary,
};

StructInitInfo *Init__Dynamic( void )
{
    return &module;
}
