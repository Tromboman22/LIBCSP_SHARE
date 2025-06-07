/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <hal_init.h>
#include <hpl_pmc.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hpl_tc.h>

struct timer_descriptor TIMER_0;

struct wdt_descriptor WDT_0;

void TIMER_0_PORT_init(void)
{
}
/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	_pmc_enable_periph_clock(ID_TC0_CHANNEL0);
	TIMER_0_PORT_init();
	timer_init(&TIMER_0, TC0, _tc_get_timer());
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void WDT_0_init(void)
{
	wdt_init(&WDT_0, WDT);
}

void system_init(void)
{
	init_mcu();

	TIMER_0_init();

	delay_driver_init();

	WDT_0_init();
}
