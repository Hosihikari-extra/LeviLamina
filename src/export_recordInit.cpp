#include "export_recordInit.h"

#include <unordered_set>

namespace {
using iterator      = std::unordered_set<std::string>::iterator;
using unordered_set = std::unordered_set<std::string>;

template <typename T, typename U>
U iterator_cast(T i) = delete;

template <>
__int64 iterator_cast<iterator, __int64>(iterator i) {
    return *(__int64*)&i;
}

template <>
iterator iterator_cast<__int64, iterator>(__int64 i) {
    return *(iterator*)&i;
}

} // namespace

RecordInit InteropRecordName(std_unordered_set_string_iterator_functions) HosihikariExport(
    void ExportFuncName(std_unordered_set_string_iterator_init)(std_unordered_set_string_iterator_functions& ref)
) {
    ref.get<0>() = [](__int64 ptr) {
        return const_cast<std::string*>(&iterator_cast<__int64, iterator>(ptr).operator*());
    };
    ref.get<1>() = [](__int64 ptr) {
        return iterator_cast<iterator, __int64>(iterator_cast<__int64, iterator>(ptr).operator++());
    };
    ref.get<2>() = [](__int64 ptr) {
        return iterator_cast<iterator, __int64>(iterator_cast<__int64, iterator>(ptr).operator--());
    };
    ref.get<3>() = [](__int64 ptr, __int64 ptr2) {
        return iterator_cast<__int64, iterator>(ptr).operator==(iterator_cast<__int64, iterator>(ptr2));
    };
}

RecordInit InteropRecordName(std_unordered_set_string_functions)
    HosihikariExport(void ExportFuncName(std_unordered_set_string_init)(std_unordered_set_string_functions& ref)) {
    // begin
    ref.get<0>() = [](std::unordered_set<std::string>* ptr) { return iterator_cast<iterator, __int64>(ptr->begin()); };
    // end
    ref.get<1>() = [](std::unordered_set<std::string>* ptr) {
        return iterator_cast<iterator, __int64>(reinterpret_cast<unordered_set*>(ptr)->end());
    };
    // size
    ref.get<2>() = [](std::unordered_set<std::string>* ptr) { return reinterpret_cast<unordered_set*>(ptr)->size(); };
    // max_size
    ref.get<3>() = [](std::unordered_set<std::string>* ptr) {
        return reinterpret_cast<unordered_set*>(ptr)->max_size();
    };
    // clear
    ref.get<4>() = [](std::unordered_set<std::string>* ptr) { reinterpret_cast<unordered_set*>(ptr)->clear(); };
    // insert
    ref.get<5>() = [](bool& succeed, std::unordered_set<std::string>* ptr, std::string* str) {
        auto temp = reinterpret_cast<unordered_set*>(ptr)->insert(*reinterpret_cast<std::string*>(str));
        succeed   = temp.second;
        return iterator_cast<iterator, __int64>(temp.first);
    };
    // count
    ref.get<6>() = [](std::unordered_set<std::string>* ptr, std::string* str) {
        return reinterpret_cast<unordered_set*>(ptr)->count(*reinterpret_cast<std::string*>(str));
    };
    // cotains
    ref.get<7>() = [](std::unordered_set<std::string>* ptr, std::string* str) {
        return reinterpret_cast<unordered_set*>(ptr)->contains(*reinterpret_cast<std::string*>(str));
    };
    // erase
    ref.get<8>() = [](std::unordered_set<std::string>* ptr, std::string* str) {
        return reinterpret_cast<unordered_set*>(ptr)->erase(*reinterpret_cast<std::string*>(str));
    };
}