#pragma once

#include "../../helper/markup_strategy.hpp"
#include "base_style.hpp"

namespace mb::style
{
    class spacing : public base_style
    {
    public:
        const char *name() override
        {
            return "layout";
        }

        def::state_t parse(const pugi::xml_node &node, lv_style_t *style, lv_state_t state) override
        {
            const def::style::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_top, style, "pd_top", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_bottom, style, "pd_bottom", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_right, style, "pd_right", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_left, style, "pd_left", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_hor, style, "pd_hor", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_pad_ver, style, "pd_ver", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_top, style, "mg_top", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_bottom, style, "mg_bottom", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_right, style, "mg_right", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_left, style, "mg_left", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_hor, style, "mg_hor", state),
                    MB_ADD_STYLE_ATTR_FUNC(parse_margin_ver, style, "mg_ver", state),
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
        static def::state_t parse_pad_top(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_top(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad_bottom(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_bottom(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad_right(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_right(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad_left(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_left(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad_hor(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_hor(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_pad_ver(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_pad_ver(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_top(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_top(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_bottom(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_bottom(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_left(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_left(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_right(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_right(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_hor(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_hor(style, state, attr.as_int(0));
            return def::STATE_OK;
        }

        static def::state_t parse_margin_ver(const pugi::xml_attribute &attr, lv_style_t *style, lv_state_t state)
        {
            if (!style || !attr) return def::STATE_INVALID_ARGS;
            lv_style_set_margin_ver(style, state, attr.as_int(0));
            return def::STATE_OK;
        }
    };
}