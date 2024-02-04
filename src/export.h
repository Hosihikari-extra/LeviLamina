#pragma once

#define AutoGenerate
#define Manually
#define HosihikariExport(func)           extern "C" __declspec(dllexport) func
#define ExportFuncName(func)             levilamina_exported_##func
#define ExportFuncNameOverload(func, id) levilamina_exported_##func##_##id

#include <ll/api/base/FixedString.h>
#include <type_traits>
#include <utility>

namespace {

// https://zhuanlan.zhihu.com/p/672626789

template <typename T, ll::FixedString Name>
struct RecordField {
    using type = T;
};

template <std::size_t Index, typename T, typename... Types>
struct Type_element {
    using Type = typename Type_element<Index - 1, Types...>::Type;
};
template <typename T, typename... Types>
struct Type_element<0, T, Types...> {
    using Type = T;
};

template <int Index, typename... Types>
using Type_element_t = typename Type_element<Index, Types...>::Type;

template <typename T, std::size_t Index>
class Item {
protected:
    T value;
};
template <typename Index, typename... Types>
struct RecordImpl;
template <std::size_t... Indexs, typename... Types>
struct RecordImpl<std::index_sequence<Indexs...>, Types...> : Item<Types, Indexs>... {
    constexpr static auto args_size = sizeof...(Types);
    RecordImpl<std::index_sequence<Indexs...>, Types...>(const Types&... args) : Item<Types, Indexs>{args}... {}
    template <std::size_t Index>
    auto& get() {
        static_assert(0 <= Index && Index < args_size);
        return Item<Type_element_t<Index, Types...>, Index>::value;
    }
};

template <typename... Types>
struct Record : RecordImpl<std::make_index_sequence<sizeof...(Types)>, Types...> {
    Record(const Types&... args) : RecordImpl<std::make_index_sequence<sizeof...(Types)>, Types...>(args...){};
};

} // namespace

#define RecordField(field_type, field_name) RecordField<field_type, field_name>::type
#define InteropRecord(record_name, ...)     using record_name = Record<__VA_ARGS__>
