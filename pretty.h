#ifndef _PRETTY
#define _PRETTY

#include <vlc/vlc.h>
#include <unistd.h>
#include <sys/ioctl.h>

/* Given the filename and duration in milliseconds of a media file,
   print the filename and the duration in minutes and seconds. */
void print_minutes_seconds(char* name, int64_t duration)
{
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int seconds = (duration / 1000) % 60;
        int minutes = duration / 1000 / 60;
        printf("%-*s %d:%02d\n",w.ws_col - 10, name, minutes, seconds);
}

#endif
