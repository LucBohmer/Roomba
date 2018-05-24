#include "LedMatrixDevice.h"

#include <pthread.h>
#include <errno.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//static pthread_mutex_t sense_hat_mutex = PTHREAD_MUTEX_INITIALIZER;
static const char SENSE_HAT_FB_NAME[] = "RPi-Sense FB";
static int fbfd = -1;

static uint16_t pack_pixel(uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t r16 = (r >> 3) & 0x1F;
	uint16_t g16 = (g >> 2) & 0x3F;
	uint16_t b16 = (b >> 3) & 0x1F;
	return (r16 << 11) + (g16 << 5) + b16;
}

static void unpack_pixel(uint16_t pixel, uint8_t *r, uint8_t *g, uint8_t *b)
{
	*r = (pixel & 0xF800) >> 8;
	*g = (pixel & 0x07E0) >> 3  ;
	*b = (pixel & 0x001F) << 3;
}

static void sense_hat_rstrip(char* s)
{
	size_t l = strlen(s);
	if(l == 0) return;
	char* end = s + l - 1;
	while(end >= s && isspace(*end)) {
		end--;
	}
	end[1] = '\0';
}

int init_fb(void)
{
	if(fbfd != -1) {
		return 0;
	}
	DIR* d = opendir("/sys/class/graphics");
	if(d == NULL) {
		fprintf(stderr, "can't open dir /sys/class/graphics\n");
		return errno;
	}
	struct dirent* dent = (struct dirent*)malloc(offsetof(struct dirent, d_name) + NAME_MAX + 1);
	struct dirent* dentp;
	while(1) {
		int rc = readdir_r(d, dent, &dentp);
		if(rc == 0 && dentp == NULL) {
			fprintf(stderr, "ENOENT\n");
			rc = ENOENT;
		}
		if(rc != 0) {
			free(dent);
			closedir(d);
			fprintf(stderr, "rc != 0\n");
			return rc;
		}
		if(strncmp("fb", dent->d_name, 2) == 0) {
			char path[PATH_MAX];
			snprintf(path, PATH_MAX, "/sys/class/graphics/%s/name", dent->d_name);
			FILE* f = fopen(path, "r");
			if(f == NULL) continue;
			char name[1024];
			fgets(name, sizeof(name), f);
			sense_hat_rstrip(name);
			if(strcmp(name, SENSE_HAT_FB_NAME) == 0) {
				snprintf(path, PATH_MAX, "/dev/%s", dent->d_name);
				fbfd = open(path, O_RDWR);
				free(dent);
				closedir(d);
				if(fbfd == -1) {
				   fprintf(stderr, "fnfd == -1\n");
					return errno;
				}
				break;
			}
		}
	}
	return 0;
}

int blank(void)
{
	int rc = init_fb();
	if(rc != 0) {
		fprintf(stderr, "init_fb error\n");
		return rc;
	}
	char buf[128];
	memset(buf, 0, 128);
	if(pwrite(fbfd, buf, 128, 0) != 128) {
		fprintf(stderr, "pwrite error\n");
		return errno;
	}
	return 0;
}

int clear(uint8_t r, uint8_t g, uint8_t b)
{
	int i = 0;
	int rc = init_fb();
	if(rc != 0) {
		fprintf(stderr, "init_fb error\n");
		return rc;
	}
	uint16_t tempBuf[64];
	for (i = 0; i < 64; i++) tempBuf[i] = pack_pixel(r, g, b);

	if (pwrite(fbfd, (uint8_t*)tempBuf, 128, 0) != 128) {
		fprintf(stderr, "pwrite error\n");
		return errno;
	}
	return 0;
}

int invert(void)
{
	int i = 0;
	int rc = init_fb();
	if(rc != 0) {
		fprintf(stderr, "init_fb error\n");
		return rc;
	}
	uint8_t tempBuf[128];
	if (pread(fbfd, tempBuf, 128, 0) != 128) {
		return errno;
	}
	for (i = 0; i < 128; i++) tempBuf[i] = ~tempBuf[i];

	if (pwrite(fbfd, tempBuf, 128, 0) != 128) {
		fprintf(stderr, "pwrite error\n");
		return errno;
	}
	return 0;
}

int set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	int rc = init_fb();
	if(rc != 0) {
		return rc;
	}
	uint16_t pixel = pack_pixel(r, g, b);
	if(pwrite(fbfd, &pixel, sizeof(pixel), (x+y*8)*2) != sizeof(pixel)) {
		return errno;
	}
	return 0;
}

int get_pixel(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b)
{
	int rc = init_fb();
		if(rc != 0) {
			return rc;
		}
		uint16_t pixel;
		if(pread(fbfd, &pixel, sizeof(pixel), (x+y*8)*2) != sizeof(pixel)) {
			return errno;
		}
	   //fprintf(stderr, "p = %x\n", pixel);
		unpack_pixel(pixel, r, g, b);
		return 0;
}
