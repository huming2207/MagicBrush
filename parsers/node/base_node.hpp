#pragma once

#include "pugixml.hpp"
#include "helper/defs.hpp"
#include "helper/markup_strategy.hpp"

namespace lv::node
{
    class base_node
    {
    public:
        virtual const char *name() = 0;
        virtual def::state_t parse(const pugi::xml_node &node, lv_obj_t *obj) = 0;
    };
}