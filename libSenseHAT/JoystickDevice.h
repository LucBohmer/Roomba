#ifndef JOYSTICKDEVICE_H
#define JOYSTICKDEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/input.h>

#define input_event_t struct input_event

int initEventDevice(void);
input_event_t pollingEventDevice(void);
input_event_t handle_events(int evfd);

#ifdef __cplusplus
}
#endif

#endif
