#pragma once

#define AutoGenerate
#define Manually
#define InteropRecordName(...)
#define HosihikariExport(func)           extern "C" __declspec(dllexport) func
#define ExportFuncName(func)             levilamina_exported_##func
#define ExportFuncNameOverload(func, id) levilamina_exported_##func##_##id
#define RecordInit

/*
 * def: AutoGenerate
 * // point out the interop C# code will be generated automatically.
 */

/*
 * def: Manually
 * // point out the interop C# code will be writting manually.
 */

/*
 * def: InteropRecordName(<record_type_name>)
 * // point out the <record_type_name> is defined by InteropRecordDefinition, and will be used by C# code generator for
 * // searching record type definition.
 */

/*
 * def: HosihikariExport(<function>)
 * // export a function by __declspec(dllexport).
 */

/*
 * def: ExportFuncName(<function>)
 * // conbine the prefix "levilamina_exported_" and the <function> name.
 */

/*
 * def: ExportFuncNameOverload(<function>, <id>)
 * // conbine the prefix "levilamina_exported_" and the <function> name and the <id> name.
 */

/*
 * def: RecordInit
 * // a sign for record type initialization function.
 */

#include <ll/api/base/FixedString.h>
#include <type_traits>
#include <utility>

namespace {

// https://zhuanlan.zhihu.com/p/672626789

template <typename T, ll::FixedString Name>
struct NamedType {
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

public:
    Item() = default;
};

template <typename Index, typename... Types>
struct RecordImpl;

template <std::size_t... Indexs, typename... Types>
struct RecordImpl<std::index_sequence<Indexs...>, Types...> : Item<Types, Indexs>... {
    constexpr static auto args_size = sizeof...(Types);
    RecordImpl<std::index_sequence<Indexs...>, Types...>(const Types&... args) : Item<Types, Indexs>{args}... {}
    RecordImpl<std::index_sequence<Indexs...>, Types...>() = default;

    template <std::size_t Index>
    auto& get() {
        static_assert(0 <= Index && Index < args_size);
        return Item<Type_element_t<Index, Types...>, Index>::value;
    }
};

template <typename... Types>
struct Record : RecordImpl<std::make_index_sequence<sizeof...(Types)>, Types...> {
    Record(const Types&... args) : RecordImpl<std::make_index_sequence<sizeof...(Types)>, Types...>(args...){};
    Record() = default;
};

} // namespace

#define RecordField(field_type, field_name)       NamedType<field_type, field_name>::type
#define InteropRecordDefinition(record_name, ...) using record_name = Record<__VA_ARGS__>

/*
 * def: RecordField(<field_type>, <field_name>)
 * // define a record field with <field_type> and <field_name>.
 */

/*
 * def: InteropRecordDefinition(<record_name>, ...)
 * // define a record type with <record_name> and <parameters>, the <parameters> should defined by RecordField.
 */

namespace {
template <typename T>
    requires std::is_function_v<T>
struct FunctionPointerType {
    using type = std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<T>>>>;
};

template <size_t Size>
struct Filler {
    char data[Size];
};

template <typename T>
    requires std::is_pointer_v<T>
struct PointerType {
    using type = T;
};

template <typename T>
    requires std::is_reference_v<T>
struct ReferenceType {
    using type = T;
};

} // namespace
#define FunctionPointerDef(name, conv, ret, ...) NamedType<ret(conv*)(__VA_ARGS__), name>::type
#define FillerDef(size)                          Filler<size>
#define Pointer(_type)                           PointerType<_type*>::type
#define Reference(_type)                         ReferenceType<_type&>::type

/*
 * def: FunctionPointerDef(<name>, <conv>, <ret>, ...)
 * // define a function pointer type with <name>, <conv> is the function's calling convention, <ret> is the return type
 * // and <parameters> is the function's parameters.
 */

/*
 * def: FillerDef(<size>)
 * // define a filler type with <size>.
 */

/*
 * def: Pointer(<type_name>)
 * // point out that the <type_name>'s pointer type and will be interop with C# code using by nint(native int).
 */

/*
 * def: Reference(<type_name>)
 * // same as Pointer.
 */


/*
 * def: AutoGenerate HosihikariExport(<return_type> ExportFuncName(<function_name>))(<parameters>)
 * // export a function with <return_type> and <function_name> and <parameters>, and C# code generator will generate
 * // interop code automatically.
 */

/*
 * def: Manually HosihikariExport(<return_type> ExportFuncName(<function_name>))(<parameters>)
 * // export a function with <return_type> and <function_name> and <parameters>, and interop code will be writting
 * // manually because of its complexity.
 */

/*
 * def: RecordInit InteropRecordName(<type_name>) HosihikariExport(<return_type>
 * ExportFuncName(<function_name>))(<parameters>)
 * // export a function for initialize the record type with <type_name: record type name>, <return_type: function return
 * // type>, <function_name: exported function name> and <parameters: function parameters>.
 */

/*
 * def: InteropRecordDefinition(<type_name>, ...)
 * // define a record type with <type_name: record type name> and <parameters: record parameters>.
 * //
 * // supported parameters: RecordField(<field_type>, <field_name>), FunctionPointerDef(<name>, <conv>, <ret>, ...),
 * // FillerDef(<size>)
 * //
 * // example1: InteropRecordDefinition(MyRecord, RecordField(int, a), RecordField(std::string, b))
 * //
 * // example2: InteropRecordDefinition(MyRecord, RecordField(int, a), RecordField(std::string, b),
 * // FunctionPointerDef("my_fptr_def", __cdecl, void, int, Pointer(std::string)))
 * //
 * // example3: InteropRecordDefinition(MyRecord, FillerDef(100))
 * //
 * // using <type_name>.get<0>() to get the first field, <type_name>.get<1>() to get the second field, and so on.
 * // the <type_name>.get<index>() will return the <index>-th field.
 */
