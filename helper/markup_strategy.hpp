#pragma once

#include <functional>
#include <lvgl/lvgl.h>
#include "../external/pugixml/pugixml.hpp"
#include "defs.hpp"

#define MB_ADD_WIDGET_ATTR_FUNC(func, obj, name)                                             \
    def::widget::markup_strategy<pugi::xml_attribute>([&](const pugi::xml_attribute &attr, lv_obj_t *(obj)) {    \
        return func(attr, obj);                                                              \
    }, name)

#define MB_ADD_STYLE_ATTR_FUNC(func, obj, name, state)                                             \
    def::style::markup_strategy<pugi::xml_attribute>([&](const pugi::xml_attribute &attr, lv_style_t *(obj), lv_state_t (state)) {    \
        return func(attr, obj, state);                                                              \
    }, name)

namespace mb::def::widget
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

namespace mb::def::style
{
    template <typename T>
    class markup_strategy
    {
    public:
        explicit markup_strategy(std::function<def::state_t(const T &, lv_style_t *, lv_state_t)> strategy, const char *_name)
                : func_name(_name), strategy(std::move(strategy)) { }

        def::state_t run(const T &attr, lv_style_t *style, lv_state_t state) const { return strategy(attr, style, state); }
        [[nodiscard]] const char *name() const { return func_name; }

    private:
        const char *func_name;
        const std::function<def::state_t(const T &, lv_style_t *, lv_state_t)> strategy;
    };
}