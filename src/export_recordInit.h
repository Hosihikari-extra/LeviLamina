#include "export.h"

InteropRecordDefinition(
    std_unordered_set_string_iterator_functions,
    FunctionPointerDef("dereference", __stdcall, Pointer(std::string), __int64),
    FunctionPointerDef("inc", __stdcall, __int64, __int64),
    FunctionPointerDef("dec", __stdcall, __int64, __int64),
    FunctionPointerDef("equals", __stdcall, bool, __int64, __int64)
);

#include <unordered_set>

InteropRecordDefinition(
    std_unordered_set_string_functions,
    FunctionPointerDef("begin", __stdcall, __int64, Pointer(std::unordered_set<std::string>)),
    FunctionPointerDef("end", __stdcall, __int64, Pointer(std::unordered_set<std::string>)),
    FunctionPointerDef("size", __stdcall, unsigned __int64, Pointer(std::unordered_set<std::string>)),
    FunctionPointerDef("max_size", __stdcall, unsigned __int64, Pointer(std::unordered_set<std::string>)),
    FunctionPointerDef("clear", __stdcall, void, Pointer(std::unordered_set<std::string>)),
    FunctionPointerDef(
        "insert",
        __stdcall,
        __int64,
        bool&,
        Pointer(std::unordered_set<std::string>),
        Pointer(std::string)
    ),
    FunctionPointerDef(
        "count",
        __stdcall,
        unsigned __int64,
        Pointer(std::unordered_set<std::string>),
        Pointer(std::string)
    ),
    FunctionPointerDef("contains", __stdcall, bool, Pointer(std::unordered_set<std::string>), Pointer(std::string)),
    FunctionPointerDef(
        "erase",
        __stdcall,
        unsigned __int64,
        Pointer(std::unordered_set<std::string>),
        Pointer(std::string)
    )
);