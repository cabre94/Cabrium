#pragma once

#define DECL_ITERATORS(type, cont_type, cont_name)                                 \
    std::cont_type<type>::iterator begin() { return cont_name.begin(); }           \
    std::cont_type<type>::iterator end() { return cont_name.end(); }               \
    std::cont_type<type>::reverse_iterator rbegin() { return cont_name.rbegin(); } \
    std::cont_type<type>::reverse_iterator rend() { return cont_name.rend(); }

#define DECL_CONST_ITERATORS(type, cont_type, cont_name)                             \
    std::cont_type<type>::const_iterator begin() const { return cont_name.begin(); } \
    std::cont_type<type>::const_iterator end() const { return cont_name.end(); }     \
    std::reverse_iterator<std::cont_type<type>::const_iterator> rbegin() const {     \
        return cont_name.rbegin();                                                   \
    }                                                                                \
    std::reverse_iterator<std::cont_type<type>::const_iterator> rend() const {       \
        return cont_name.rend();                                                     \
    }\
