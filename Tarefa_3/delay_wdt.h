#ifndef WDT_DELAY_H_
#define WDT_DELAY_H_

#include <stdint.h>

void config_wd_as_timer(void);

void delay_wdt(uint16_t time);


#endif /* WDT_DELAY_H_ */
