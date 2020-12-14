#pragma once

#include "../../helper/markup_strategy.hpp"
#include "base_style.hpp"

namespace mb::style
{
    class background : public base_style
    {
    public:
        const char *name() override
        {
            return "background";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) override
        {
            const def::style::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    MB_ADD_STYLE_ATTR_FUNC(parse_color, style, "color", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_opacity, style, "opa", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_grad_color, style, "grad_color", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_main_stop, style, "main_stop", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_grad_stop, style, "grad_stop", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_grad_dir, style, "grad_dir", state),
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
            lv_style_set_bg_color(style, state, lv_color);
            return def::STATE_OK;
        }

        static def::state_t parse_opacity(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto opa_val = attr.as_uint(0);
            if (opa_val > 255) return def::STATE_INVALID_ARGS;

            lv_style_set_bg_opa(style, state, opa_val);
            return def::STATE_OK;
        }

        static def::state_t parse_grad_color(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            lv_color_t lv_color = lv_color_hex(attr.as_uint(0));
            lv_style_set_bg_grad_color(style, state, lv_color);
            return def::STATE_OK;
        }

        static def::state_t parse_main_stop(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto opa_val = attr.as_uint(0);
            if (opa_val > 255) return def::STATE_INVALID_ARGS;

            lv_style_set_bg_main_stop(style, state, opa_val);
            return def::STATE_OK;
        }

        static def::state_t parse_grad_stop(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto opa_val = attr.as_uint(0);
            if (opa_val > 255) return def::STATE_INVALID_ARGS;

            lv_style_set_bg_grad_stop(style, state, opa_val);
            return def::STATE_OK;
        }

        static def::state_t parse_grad_dir(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!attr || !style) return def::STATE_INVALID_ARGS;
            auto val = attr.as_string("none");

            if (strcmp(val, "none") == 0) {
                lv_style_set_bg_grad_dir(style, state, LV_GRAD_DIR_NONE);
            } else if (strcmp(val, "ver") == 0) {
                lv_style_set_bg_grad_dir(style, state, LV_GRAD_DIR_VER);
            } else if (strcmp(val, "hor") == 0) {
                lv_style_set_bg_grad_dir(style, state, LV_GRAD_DIR_HOR);
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
                lv_style_set_bg_blend_mode(style, state, LV_BLEND_MODE_NORMAL);
            } else if (strcmp(val, "additive") == 0) {
                lv_style_set_bg_grad_dir(style, state, LV_BLEND_MODE_ADDITIVE);
            } else if (strcmp(val, "subtract") == 0) {
                lv_style_set_bg_grad_dir(style, state, LV_BLEND_MODE_SUBTRACTIVE);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }
    };
}