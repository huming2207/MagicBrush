#pragma once

#include "../../external/pugixml/pugixml.hpp"
#include "../../helper/defs.hpp"
#include "lvgl.h"

namespace mb::style
{
    class base_style
    {
    public:
        virtual const char *name() = 0;
        virtual def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) = 0;
    };
}