// ---------------------------------------------------------------------
// Wrapper for gatttool
//
// By Hugo Arends
// May 2017
// ---------------------------------------------------------------------

#include "gatt_wrapper.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variables
int fdX[2];
int fdY[2];

void gatt_start(const char *mac)
{
   pid_t cpid;

   if (pipe(fdX) == -1)
   {
      printf("Error: could not create pipe!\n");
      exit(0);
   }

   if (pipe(fdY) == -1)
   {
      printf("Error: could not create pipe!\n");
      exit(0);
   }

   cpid = fork();
   switch (cpid)
   {
      case -1:
      {
         printf("Error: could not start a child process!\n");
         exit(0);
      }

      case 0:
      {
         // CHILD PROCESS

         // Close unused file descriptors
         close(fdX[1]);
         close(fdY[0]);

         // Connect child's stdin to pipe X output
         //
         //         fdX[0]   stdin
         //  _________|        |_______
         //  _________|------->|_______|
         //    pipe X            CHILD
         //
         close(0);
         dup(fdX[0]);

         // Connect child's stdout to pipe Y input
         //
         //         fdY[1]   stdout
         //  _________|        |_______
         //  _________|<-------|_______|
         //    pipe Y            CHILD
         //
         close(1);
         dup(fdY[1]);

         //close(fdX[0]);
         //close(fdY[1]);

         int ret = execl("/usr/bin/gatttool",
                         "gatttool",
                         "-b",
                         mac,
                         "-I",
                         NULL);
         if(ret == -1)
         {
            printf("Error: could not start gatttool!\n");
            exit(0);
         }
         close(fdX[0]);
         close(fdY[1]);

         //break;

         //wait(NULL);
         // Child stops
         exit(0);
      }

      default:
      {
         // PARENT PROCESS

         //int flags = fcntl(fdY[0], F_GETFL, 0);
         //fcntl(fdY[0], F_SETFL, flags | O_NONBLOCK);

         // Close unused file descriptors
         close(fdX[0]);
         close(fdY[1]);

         // Write to child through pipe X
         //
         //       write()    fdX[1]
         //   ________|        |_________
         //  |________|------->|_________
         //      PARENT            pipe X

         // Read from child through pipe Y
         //
         //        read()    fdY[0]
         //   ________|        |_________
         //  |________|<-------|_________
         //    PARENT            pipe Y

         return;
      }
   }
}

int gatt_connect(void)
{
   char s[80] = {'\0'};

   // Try to connect
   sprintf(s, "connect\n");
   gatt_write(s);
   gatt_read(s);
   DBG("gatt-connect", 1, s);

   if (strstr(s, "Error") != NULL)
   {
      return -1;
   }

   sleep(1);

   // Await several responses from gatttool
   gatt_read(s);
   DBG("gatt_connect", 2, s);

   if (strstr(s, "Error") != NULL)
   {
      return -1;
   }

   gatt_read(s);
   DBG("gatt_connect", 3, s);

   if (strstr(s, "Error") != NULL)
   {
      return -1;
   }

   gatt_read(s);
   DBG("gatt_connect", 4, s);

   if (strstr(s, "Connection successful") != NULL)
   {
      return 0;
   }

   return -1;
}

int gatt_disconnect(void)
{
   char s[60] = {'\0'};

   sprintf(s, "disconnect\n");
   gatt_write(s);
   gatt_read(s);
   DBG("gatt",5,s);

   return 0;
}

int gatt_exit(void)
{
   char s[60] = {'\0'};

   sprintf(s, "exit\n");
   gatt_write(s);
   gatt_read(s);
   DBG("gatt",6,s);

   sleep(1);

   close(fdX[1]);
   close(fdY[0]);

   return 0;
}

void gatt_write(const char *s)
{
   DBG("gatt_write", 1, s);
   write(fdX[1], s, strlen(s)+1);
}

// TODO: strip VT100 commands from response
// TODO: implement timeout
void gatt_read(char *r)
{
   unsigned char c;
   unsigned int i = 0;

   r[0] = '\0';
   do
   {
      // Read one character from gatttool
      read(fdY[0], &c, 1);
      // Replace CR for LF
      if(c == '\r'){
         c = '\n';
      }
      // Save the character in the response string
      r[i++] = c;
      //printf("%02X ", c);
   } while(c != '\n');
   //printf("\n");
   // Terminate the response string
   r[i] = '\0';
   DBG("gatt_read", 1, r);
}
