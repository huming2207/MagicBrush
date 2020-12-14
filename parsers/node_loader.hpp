#pragma once

#include <cstddef>
#include "../external/pugixml/pugixml.hpp"

#include "../helper/defs.hpp"
#include "../helper/logger.hpp"
#include "node_vector.hpp"

#define TAG "node_loader"

namespace mb
{
    class node_loader
    {
    public:
        def::state_t load_in_place(const char *xml_str, size_t len)
        {
            auto result = xml_doc.load_buffer_inplace((void *) xml_str, len);
            if (result.status == pugi::status_out_of_memory || result.status == pugi::status_io_error) {
                MB_LOGE(TAG, "No memory or invalid I/O states for XML loading");
                return def::STATE_NO_MEM;
            } else if (result.status != pugi::status_ok) {
                MB_LOGE(TAG, "Got invalid states from PugiXML: 0x%x", result.status);
                return def::STATE_INVALID_XML;
            }

            MB_LOGI(TAG, "XML document loaded");

            // Find the main node
            auto mb_node = xml_doc.child("magic_brush");
            if (mb_node.empty()) {
                MB_LOGE(TAG, "No child found for the main node");
                return def::STATE_INVALID_XML;
            }

            // Probe length and reserve memory in advance - to avoid heap fragmentation
            size_t xml_len = std::distance(mb_node.begin(), mb_node.end());
            if (xml_len < 1) {
                MB_LOGE(TAG, "No children node found");
                return def::STATE_INVALID_XML;
            }

            MB_LOGI(TAG, "XML loaded, node count: %zu", xml_len);
            nodes.reserve(xml_len);

            // Iterate through XML doc
            auto ret = def::STATE_OK;
            for (auto& node : mb_node.children()) {
                ret = nodes.parse_widget(node);
                if (ret != def::STATE_OK) return ret;
            }

            MB_LOGI(TAG, "Done loading");
            return ret;
        }

    private:
        pugi::xml_document xml_doc = {};
        node_vector nodes = {};
    };
}