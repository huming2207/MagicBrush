#pragma once

#include "../../helper/markup_strategy.hpp"
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

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) override
        {
            const def::style::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    MB_ADD_STYLE_ATTR_FUNC(parse_color, style, "color", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_opacity, style, "opa", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_width, style, "width", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad, style, "pad", state),
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
            lv_style_set_outline_color(style, state, lv_color);
            return def::STATE_OK;
        }

        static def::state_t parse_opacity(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto opa_val = attr.as_uint(255);
            if (opa_val > 255) return def::STATE_INVALID_ARGS;

            lv_style_set_outline_opa(style, state, opa_val);
            return def::STATE_OK;
        }

        static def::state_t parse_width(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_style_set_outline_width(style, state, attr.as_uint(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_style_set_outline_pad(style, state, attr.as_int(0));
            return def::STATE_OK;
        }


        static def::state_t parse_blend_mode(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto val = attr.as_string("normal");

            if (strcmp(val, "normal") == 0) {
                lv_style_set_outline_blend_mode(style, state, LV_BLEND_MODE_NORMAL);
            } else if (strcmp(val, "additive") == 0) {
                lv_style_set_outline_blend_mode(style, state, LV_BLEND_MODE_ADDITIVE);
            } else if (strcmp(val, "subtract") == 0) {
                lv_style_set_outline_blend_mode(style, state, LV_BLEND_MODE_SUBTRACTIVE);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }
    };
}