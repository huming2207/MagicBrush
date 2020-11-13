#pragma once

#include "object.hpp"

namespace mb::widget
{
    class label : public object
    {
    public:
        const char *name() override
        {
            return "label";
        }

        lv_obj_t *create() override
        {
            return lv_label_create(lv_scr_act(), nullptr);
        }

        lv_obj_t *create(lv_obj_t *parent) override
        {
            return lv_label_create(parent, nullptr);
        }

        def::state_t parse(const pugi::xml_node &node, lv_obj_t *obj) override
        {
            auto ret = object::parse(node, obj);
            if (ret != def::STATE_OK) return ret;

            static const def::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    MB_ADD_ATTR_FUNC(parse_text, obj, "text"),
                    MB_ADD_ATTR_FUNC(parse_anim_speed, obj, "anim_speed"),
                    MB_ADD_ATTR_FUNC(parse_long_mode, obj, "long_mode"),
                    MB_ADD_ATTR_FUNC(parse_recolor, obj, "recolor"),
                    MB_ADD_ATTR_FUNC(parse_align, obj, "align"),
            };

            for(const auto& attr : attr_lut) {
                const auto& xml_attr = node.attribute(attr.name());
                if (xml_attr) {
                    attr.run(xml_attr, obj);
                }
            }

            return def::STATE_OK;
        }

    private:
        static def::state_t parse_text(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            const char *val = attr.value();
            if (!val) {
                ESP_LOGE("mb_label", "Invalid text");
                return def::STATE_INVALID_ATTR;
            } else {
                size_t len = strlen(val);
                ESP_LOGI("mb_label", "Text: %s, len: %u", val, len);
            }

            lv_label_set_text(ui_obj, val);

            return def::STATE_OK;
        }

        static def::state_t parse_anim_speed(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_label_set_anim_speed(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_align(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            const char *val = attr.as_string();
            if (!val || strlen(val) < 1) return def::STATE_INVALID_ATTR;
            if (strcmp("right", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_ALIGN_RIGHT);
            } else if (strcmp("left", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_ALIGN_LEFT);
            } else if (strcmp("center", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_ALIGN_CENTER);
            } else if (strcmp("auto", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_ALIGN_AUTO);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }

        static def::state_t parse_long_mode(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            const char *val = attr.as_string();
            if (!val || strlen(val) < 1) return def::STATE_INVALID_ATTR;
            if (strcmp("expand", val) == 0) {
                lv_label_set_long_mode(ui_obj, LV_LABEL_LONG_EXPAND);
            } else if (strcmp("break", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_LONG_BREAK);
            } else if (strcmp("dot", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_LONG_DOT);
            } else if (strcmp("sroll", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_LONG_SROLL);
            } else if (strcmp("sroll_circ", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_LONG_SROLL_CIRC);
            } else if (strcmp("crop", val) == 0) {
                lv_label_set_align(ui_obj, LV_LABEL_LONG_CROP);
            } else {
                return def::STATE_INVALID_ATTR;
            }

            return def::STATE_OK;
        }

        static def::state_t parse_recolor(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            bool val = attr.as_bool();
            lv_label_set_recolor(ui_obj, val);
            return def::STATE_OK;
        }
    };
}