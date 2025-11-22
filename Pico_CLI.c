#include "pico_cli.h"

char sPath[ILINE];
volatile uint8_t iCB_Irq;
bool bAuto;
/** @brief Example from Rasberry Pico blink - add reverse LED  */
// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

// Perform initialisation
int pico_led_init(void) {
    gpio_init(PROBE_DAP_CONNECTED_LED);
    gpio_set_dir(PROBE_DAP_CONNECTED_LED, GPIO_OUT);
    gpio_put(PROBE_DAP_CONNECTED_LED, 0);
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(PROBE_DAP_CONNECTED_LED, !led_on);
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

bool repeating_timer_callback(__unused struct repeating_timer *t) {
  iCB_Irq++;
  iCB_Irq = iCB_Irq % 2;
    return true;
}

/// @brief MAIN-Proc
/// @return integer (unused)
int main() {
    char inChar;
    static bool bEM;
    static bool bLed= false;
    uint64_t iStTime = 0 ;
    static char sLine[ILINE]; 
    char *psLine= &sLine[0];
    char datetime_buf[ILINE];
    int hour, min, sec, year, mon, day;
    struct repeating_timer timer;

    strcpy(sPath, "/");
    stdio_init_all();
    while (!stdio_usb_init()) {}
    while (!stdio_usb_connected()) {}
    int iRet= pico_led_init();
    puts("\e[0H\e[2J");
    puts("  \e[7m  The Raspberry Pico  \e[0m");
    add_repeating_timer_ms(LED_DELAY_MS, repeating_timer_callback, NULL, &timer); 
    if (iRet == PICO_OK){
      puts("Set Realtime clock - value from Software build");
      /* get Date and time from software build and set RTC */
      char sMon[5];
      sscanf( __DATE__, "%3s %2d %4d", &sMon[0], &day, &year);
      sscanf( __TIME__, "%02d:%02d:%02d", &hour, &min, &sec);
      datetime_t ti = {
            .year  = year,
            .month = func_MonParser(&sMon[0]),
            .day   = day,
            .hour  = hour,
            .min   = min,
            .sec   = sec
          };
      rtc_init();
      rtc_set_datetime(&ti);
      printf("\r%s>", sPath);
      /* while forever */
      while (true) {
          int iInKey = getchar_timeout_us(0);
          if ((iInKey >= 0x01)&&(iInKey <= 0x7f)) {
            inChar= (char) iInKey;
            if (bEM= editLine(psLine, inChar)) {
               psLine = strupr(psLine);
               fnSDOS_Parser(sLine);
               printf("\r%s>", sPath);
               *psLine= 0;
            }
          } else {
            if (iCB_Irq == 1) {
              if (bLed) pico_set_led(false);
              bLed = false;
            } else {
              if (!bLed) {
                pico_set_led(true);
              }
              bLed = true;
            }
          } 
        }  /* end while */
        bool cancelled = cancel_repeating_timer(&timer);
        printf("Timer cancelled... %d\n", cancelled);
    }
}
