# ssh_wall for “Born to Be Root”

## Description

In the new version of Debian, the wall command no longer broadcasts messages to TTY pseudo-terminals (pts).

I wrote this program, which retrieves the list of pts and executes the monitoring script, carefully redirecting STDOUT to /dev/pts/{0..}.

A file descriptor is opened for each pts, and the output stream is redirected to each of them using dup2().

## Instructions

### Compile the program

``` Makefile
make
```

### Set the monitoring script path in ssh_wall.h

```c
#define SCRIPT_PATH "/root/./monitoring.sh"

```

### ⚠️ Important: If the monitoring script is located in a directory requiring root privileges, the program must be run with root privileges.

### Set up crontab (optional logging)

```bash

*/10 * * * * /root/./monitoring.sh 2> /var/log/cron/monitoring_error.log | wall -n
*/10 * * * * /root/./wall_ssh 2> /var/log/cron/monitoring_error.log

```