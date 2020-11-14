#pragma once

#include "base_style.hpp"

namespace mb::style
{
    class outline : public base_style
    {
    public:
        const char *name() override
        {
            return "outline";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style) override
        {

        }
    };
}