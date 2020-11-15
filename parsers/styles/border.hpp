#pragma once

#include "helper/markup_strategy.hpp"
#include "base_style.hpp"

namespace mb::style
{
    class border : public base_style
    {
    public:
        const char *name() override
        {
            return "border";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) override
        {
            const def::style::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    MB_ADD_STYLE_ATTR_FUNC(parse_color, style, "color", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_opacity, style, "opa", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_border_width, style, "width", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_side, style, "side", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_post, style, "post", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_blend_mode, style, "blend", state),
            };

            for(const auto& attr : attr_lut) {
                const auto& xml_attr = node.attribute(attr.name());
                if (xml_attr) {
                    attr.run(xml_attr, style, state);
                }
            }

            return def::STATE_OK;
        }

    private:
        static def::state_t parse_color(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_color_t lv_color = lv_color_hex(attr.as_uint(0));
            lv_style_set_border_color(style, state, lv_color);
            return def::STATE_OK;
        }

        static def::state_t parse_opacity(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto opa_val = attr.as_uint(0);
            if (opa_val > 255) return def::STATE_INVALID_ARGS;

            lv_style_set_border_opa(style, state, opa_val);
            return def::STATE_OK;
        }

        static def::state_t parse_border_width(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_style_set_border_width(style, state, attr.as_uint(0));
            return def::STATE_OK;
        }

        static def::state_t parse_post(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_style_set_border_post(style, state, attr.as_bool(false));
            return def::STATE_OK;
        }

        static def::state_t parse_side(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto val = attr.as_string("full");

            if (strcmp(val, "full") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_FULL);
            } else if (strcmp(val, "left") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_LEFT);
            } else if (strcmp(val, "right") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_RIGHT);
            } else if (strcmp(val, "top") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_TOP);
            } else if (strcmp(val, "bottom") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_BOTTOM);
            } else if (strcmp(val, "none") == 0) {
                lv_style_set_border_side(style, state, LV_BORDER_SIDE_NONE);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }

        static def::state_t parse_blend_mode(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto val = attr.as_string("normal");

            if (strcmp(val, "normal") == 0) {
                lv_style_set_border_blend_mode(style, state, LV_BLEND_MODE_NORMAL);
            } else if (strcmp(val, "additive") == 0) {
                lv_style_set_border_blend_mode(style, state, LV_BLEND_MODE_ADDITIVE);
            } else if (strcmp(val, "subtract") == 0) {
                lv_style_set_border_blend_mode(style, state, LV_BLEND_MODE_SUBTRACTIVE);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }
    };
}