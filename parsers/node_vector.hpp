#pragma once

#include <cstddef>
#include <array>
#include <memory>
#include <vector>
#include "widgets/label.hpp"
#include "widgets/base_widget.hpp"
#include "widgets/object.hpp"

#include <lvgl/lvgl.h>

namespace mb
{
    using node_parser = std::unique_ptr<widget::base_widget>;
    class node_vector : public std::vector<def::node_item>
    {
    public:
        def::state_t parse_widget(pugi::xml_node& node)
        {
            for (auto& parser : node_parsers) {
                if (strcmp(parser->name(), node.name()) == 0) {
                    // Detect parent object and hash
                    lv_obj_t *obj_ptr = parent_obj && !!node.parent() && node.parent().hash_value() == parent_hash
                            ? parser->create(parent_obj)
                            : parser->create();
                    auto ret = parser->parse(node, obj_ptr);
                    if (ret != def::STATE_OK) {
                        widget::base_widget::cleanup(obj_ptr);
                        return ret;
                    } else {
                        // Add to item
                        def::node_item item = {};
                        item.obj = obj_ptr;
                        item.parent_obj = parent_obj;
                        item.hash = node.hash_value();
                        push_back(item);

                        // Replace parent for next node
                        parent_hash = node.hash_value();
                        parent_obj = obj_ptr;

                        return def::STATE_OK;
                    }
                }
            }

            return def::STATE_INVALID_NODE;
        }

        def::state_t search_by_hash(size_t hash, def::node_item *out)
        {
            if (!out) return def::STATE_INVALID_ARGS;
            for (auto &curr : *this) {
                if (curr.hash == hash) {
                    out->hash = curr.hash;
                    out->parent_obj = curr.parent_obj;
                    out->obj = curr.obj;
                    return def::STATE_OK;
                }
            }

            return def::STATE_NOT_FOUND;
        }

        def::state_t search_by_lv_obj_ptr(lv_obj_t *obj, def::node_item *out)
        {
            if (!out) return def::STATE_INVALID_ARGS;
            for (auto &curr : *this) {
                if (curr.obj == obj) {
                    out->hash = curr.hash;
                    out->parent_obj = curr.parent_obj;
                    out->obj = curr.obj;
                    return def::STATE_OK;
                }
            }

            return def::STATE_NOT_FOUND;
        }

    private:
        std::array<node_parser, 10> node_parsers = {
                std::make_unique<widget::object>(),
                std::make_unique<widget::label>()
        };

        size_t parent_hash = 0;
        lv_obj_t *parent_obj = nullptr;
    };
}