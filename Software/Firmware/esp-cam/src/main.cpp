#undef EPS
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#define EPS 192

#include <esp_log.h>
#include <string>
#include "sdkconfig.h"
#include <iostream>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <esp_err.h>
#include <esp_spiffs.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using namespace cv;
using namespace std;

static char TAG[] = "hello_opencv";

extern "C"
{
     void app_main(void);
}

void wait()
{
     vTaskDelay(100 / portTICK_PERIOD_MS);
}

void app_main(void)
{
     ESP_LOGI(TAG, "Starting main");


     while (true)
     {
     }
}