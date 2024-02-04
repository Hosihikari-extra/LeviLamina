#include "export.h"

#include <ll/api/memory/Hook.h>
#include <ll/api/utils/StringUtils.h>

Manually HosihikariExport(std::vector<std::string>* ExportFuncName(lookupSymbol)(void* func)) {
    return new std::vector<std::string>(std::move(ll::memory::lookupSymbol(func)));
}

Manually HosihikariExport(void ExportFuncName(modify)(void* ptr, size_t len, void(__stdcall* callback)())) {
    ll::memory::modify(ptr, len, callback);
}