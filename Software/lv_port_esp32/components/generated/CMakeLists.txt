if(ESP_PLATFORM)

file(GLOB_RECURSE SOURCES *.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS . ../ ./custom ./guider_customer_fonts ./guider_fonts ../lvgl/src/lv_font
                       REQUIRES lvgl)

else()
    message(FATAL_ERROR "LVGL LV examples: ESP_PLATFORM is not defined. Try reinstalling ESP-IDF.")
endif()
