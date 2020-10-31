#pragma once

#include <functional>
#include <lvgl/lvgl.h>
#include "pugixml.hpp"
#include "defs.hpp"

#define LVML_ADD_ATTR_FUNC(func, obj, name)                                             \
    def::markup_strategy<pugi::xml_attribute>([&](const pugi::xml_attribute &attr, lv_obj_t *(obj)) {    \
        return func(attr, obj);                                                              \
    }, name)

#define LVML_ADD_NODE_FUNC(func, obj, name)                                             \
    def::markup_strategy<pugi::xml_node>([&](const pugi::xml_node &attr, lv_obj_t *(obj)) {              \
        return func(attr, obj);                                                              \
    }, name)

namespace lv::def
{
    template <typename T>
    class markup_strategy
    {
    public:
        explicit markup_strategy(std::function<def::state_t(const T &, lv_obj_t *)> strategy, const char *_name)
                : func_name(_name), strategy(std::move(strategy)) { }

        def::state_t run(const T &attr, lv_obj_t *obj) const { return strategy(attr, obj); }
        [[nodiscard]] const char *name() const { return func_name; }

    private:
        const char *func_name;
        const std::function<def::state_t(const T &, lv_obj_t *)> strategy;
    };
}