#include "export.h"

#include <ll/api/memory/Hook.h>
#include <ll/api/service/Service.h>
#include <ll/api/utils/StringUtils.h>

AutoGenerate HosihikariExport(
    int ExportFuncName(hook)(void* target, void* detour, void** originalFunc, int priority, bool stopTheWorld)
) {
    return ll::memory::hook(
        target,
        detour,
        originalFunc,
        static_cast<ll::memory::HookPriority>(priority),
        stopTheWorld
    );
}

AutoGenerate HosihikariExport(bool ExportFuncName(unhook)(void* target, void* detour, bool stopTheWorld)) {
    return ll::memory::unhook(target, detour, stopTheWorld);
}

AutoGenerate HosihikariExport(void* ExportFuncName(resolveIdentifier)(wchar_t* identifier, bool disableErrorOutput)) {
    return ll::memory::resolveIdentifier(ll::string_utils::wstr2str(identifier), disableErrorOutput);
}

AutoGenerate HosihikariExport(void* ExportFuncName(resolveSymbol)(wchar_t* symbol)) {
    return ll::memory::resolveSymbol(ll::string_utils::wstr2str(symbol).c_str());
}

AutoGenerate
HosihikariExport(void* ExportFuncNameOverload(resolveSymbol, 2params)(wchar_t* symbol, bool disableErrorOutput)) {
    return ll::memory::resolveSymbol(
        static_cast<std::string_view>(ll::string_utils::wstr2str(symbol)),
        disableErrorOutput
    );
}

AutoGenerate HosihikariExport(void* ExportFuncName(resolveSignature)(wchar_t* signature)) {
    return ll::memory::resolveSymbol(ll::string_utils::wstr2str(signature).c_str());
}

AutoGenerate HosihikariExport(void* ExportFuncName(unwrapFuncPtrJmp)(void* ptr)) {
    return ll::memory::unwrapFuncPtrJmp(ptr);
}

AutoGenerate HosihikariExport(size_t ExportFuncName(getMemSizeFromPtr)(void* ptr)) {
    return ll::memory::getMemSizeFromPtr(ptr);
}