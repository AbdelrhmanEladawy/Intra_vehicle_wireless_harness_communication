/**
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SERVER_COMMON_H_
#define SERVER_COMMON_H_
#define HEARTBEAT_PERIOD_MS 500
#define ADC_CHANNEL_TEMPSENSOR 4

#include "FreeRTOS.h"
#include "queue.h"

void BleServerClient_Init(void);
void queueRecieve(uint x);
#endif
