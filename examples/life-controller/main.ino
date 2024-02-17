#include <LilyGoLib.h>
#include <LV_Helper.h>

#include "src/app.h"

uint32_t lastMillis;

lv_obj_t *label1;
char buf[64];

#include <action.hpp>
#include <log_eval.hpp>

void setup()
{
    Serial.begin(115200);
    watch.begin();

    beginLvglHelper();

    lv_obj_t *cont = lv_obj_create(lv_scr_act());
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    lv_obj_center(cont);

    label1 = lv_label_create(cont);
    lv_obj_set_width(label1, LV_PCT(90));  /*Set smaller width to make the lines wrap*/

    lv_example_get_started_1(cont);

    delay(1000);
    Serial.println("hello!");

    std::time_t start = std::time(0);
    std::time_t end = start + 10 * 60 * 60;
    create_event_log("test", "test event");
    create_goal_log("test", true, 10, start, end);
    create_goal_log("test", true, 99999, start, end);
    create_goal_log("test", false, 9999999, start, end);
    do_event_log(start, end, "test", "test");
    eval_log();
}

void loop()
{
    if (millis() - lastMillis > 1000) {

        lastMillis = millis();

        struct tm timeinfo;
        // Get the time C library structure
        watch.getDateTime(&timeinfo);

        size_t written = strftime(buf, 64, "%A, %B %d %Y %H:%M:%S", &timeinfo);

        if (written != 0) {
            lv_label_set_text(label1, buf);
            Serial.println(buf);
        }
    }
    lv_task_handler();
    delay(5);
}
