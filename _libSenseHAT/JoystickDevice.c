#define _GNU_SOURCE
#include "JoystickDevice.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <time.h>
#include <poll.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define DEV_INPUT_EVENT "/dev/input"
#define EVENT_DEV_NAME "event"

static struct pollfd evpoll;

static int is_event_device(const struct dirent *dir)
{
	return strncmp(EVENT_DEV_NAME, dir->d_name,
		       strlen(EVENT_DEV_NAME)-1) == 0;
}

static int open_evdev(const char *dev_name)
{
	struct dirent **namelist;
	int i, ndev;
	int fd = -1;

	ndev = scandir(DEV_INPUT_EVENT, &namelist, is_event_device, versionsort);
	if (ndev <= 0)	{
		return ndev;
	}
	for (i = 0; i < ndev; i++)
	{
		char fname[64];
		char name[256];

		snprintf(fname, sizeof(fname),
			 "%s/%s", DEV_INPUT_EVENT, namelist[i]->d_name);
		fd = open(fname, O_RDONLY);
		if (fd < 0) {
			continue;
		}
		ioctl(fd, EVIOCGNAME(sizeof(name)), name);
		if (strcmp(dev_name, name) == 0) {
			break;
		}
		close(fd);
	}

	for (i = 0; i < ndev; i++) {
		free(namelist[i]);
	}

	return fd;
}

int initEventDevice(void)
{
   evpoll.events = POLLIN;
   evpoll.fd = open_evdev("Raspberry Pi Sense HAT Joystick");
   if (evpoll.fd < 0) {
      fprintf(stderr, "Event device Sense HAT Joystick not found.\n");
   }
   return evpoll.fd;
}

input_event_t pollingEventDevice(void)
{
   struct input_event event = {0,0,0,0,0};
   while (poll(&evpoll, 1, 0) > 0)
      event = handle_events(evpoll.fd);
   return event;
}

input_event_t handle_events(int evfd)
{
	input_event_t ev[64] = {{0,0,0,0,0}};
	int i = 0;
	int rd = read(evfd, ev, sizeof(input_event_t) * 64);
	/* printf("rd = %d type = %d value = %d code = %d\n", rd,
	       ev->type, ev->value, ev->code); */
	if (rd < (int)sizeof(input_event_t)) {
		fprintf(stderr, "expected %d bytes, got %d\n",
		        (int) sizeof(struct input_event), rd);
		return ev[0];
	}
	for (i = 0; i < rd / (int)sizeof(struct input_event); i++)
	{
		if (ev->type != EV_KEY) {
			continue;
		}
		if (ev->value != 1) {
			continue;
		}
		switch (ev->code)
		{
			case KEY_ENTER:
            return ev[0];
				break;
			default:
            return ev[0];
		}
	}
   return ev[0];
}
