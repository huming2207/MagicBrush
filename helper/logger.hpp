#pragma once

#ifdef ESP_PLATFORM
#include <esp_log.h>
#define MB_LOGE( tag, format, ... ) ESP_LOGE(tag, format, ##__VA_ARGS__)
#define MB_LOGW( tag, format, ... ) ESP_LOGW(tag, format, ##__VA_ARGS__)
#define MB_LOGI( tag, format, ... ) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define MB_LOGD( tag, format, ... ) ESP_LOGD(tag, format, ##__VA_ARGS__)
#define MB_LOGV( tag, format, ... ) ESP_LOGV(tag, format, ##__VA_ARGS__)
#else
#include <cstdio>
#define MB_LOG_FORMAT(level, tag, format, ...) "[" level "]" "[" tag "] " format "\n"
#define MB_LOGE(tag, format, ...) fprintf(stderr, MB_LOG_FORMAT("E", tag, format), ##__VA_ARGS__)
#define MB_LOGW(tag, format, ...) fprintf(stdout, MB_LOG_FORMAT("W", tag, format), ##__VA_ARGS__)
#define MB_LOGI(tag, format, ...) fprintf(stdout, MB_LOG_FORMAT("I", tag, format), ##__VA_ARGS__)
#define MB_LOGD(tag, format, ...) fprintf(stdout, MB_LOG_FORMAT("D", tag, format), ##__VA_ARGS__)
#define MB_LOGV(tag, format, ...) fprintf(stdout, MB_LOG_FORMAT("V", tag, format), ##__VA_ARGS__)
#endif