#pragma once

#include "base_style.hpp"

namespace mb::style
{
    class line : public base_style
    {
    public:
        const char *name() override
        {
            return "line";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) override
        {

        }
    };
}