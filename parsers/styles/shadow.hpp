#pragma once

#include "base_style.hpp"

namespace mb::style
{
    class shadow : public base_style
    {
    public:
        const char *name() override
        {
            return "shadow";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style) override
        {

        }
    };
}