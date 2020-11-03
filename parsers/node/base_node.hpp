#pragma once

#include "pugixml.hpp"
#include "helper/defs.hpp"
#include "helper/markup_strategy.hpp"

namespace mb::node
{
    class base_node
    {
    public:
        static def::state_t cleanup(lv_obj_t *obj)
        {
            if (obj == nullptr) {
                return def::STATE_INVALID_ARGS;
            }

            if (lv_obj_del(obj) != LV_RES_OK) {
                return def::STATE_LVGL_ERR;
            } else {
                return def::STATE_OK;
            }
        }

        virtual const char *name() = 0;
        virtual lv_obj_t *create() = 0;
        virtual lv_obj_t *create(lv_obj_t *parent) = 0;
        virtual def::state_t parse(const pugi::xml_node &node, lv_obj_t *obj) = 0;
    };
}