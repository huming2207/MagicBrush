#pragma once

#include <cstddef>
#include <lvgl/lvgl.h>

namespace mb::def
{
    enum state_t
    {
        STATE_OK = 0,
        STATE_UNKNOWN,
        STATE_NOT_FOUND,
        STATE_INVALID_ATTR,
        STATE_INVALID_ARGS,
        STATE_NO_MEM,
        STATE_INVALID_XML,
        STATE_LVGL_ERR,
        STATE_INVALID_NODE,
    };

    struct node_item
    {
        size_t hash = 0;
        lv_obj_t *parent_obj = nullptr;
        lv_obj_t *obj = nullptr;
    };
}