#include "system_program.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <string.h>

void get_uptime(char *uptime_str)
{
    struct sysinfo s_info;
    if (sysinfo(&s_info) != 0)
    {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }

    long uptime = s_info.uptime;
    int days = uptime / (24 * 3600);
    uptime %= (24 * 3600);
    int hours = uptime / 3600;
    uptime %= 3600;
    int minutes = uptime / 60;

    sprintf(uptime_str, "%d days, %d hours, %d minutes", days, hours, minutes);
}

void get_username_info()
{
    struct passwd *pw;
    uid_t uid;

    uid = geteuid();
    pw = getpwuid(uid);
    if (pw)
    {
        printf("User: %s\n", pw->pw_name);
    }
    else
    {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
}

void get_cpu_info(char *cpu_info)
{
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), cpuinfo))
    {
        if (strncmp(buffer, "model name", 10) == 0)
        {
            strtok(buffer, ":");
            strcpy(cpu_info, strtok(NULL, "\n"));
            break;
        }
    }
    fclose(cpuinfo);
}

void get_memory_info(char *mem_info)
{
    struct sysinfo s_info;
    if (sysinfo(&s_info) != 0)
    {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }

    long total_ram = s_info.totalram / 1024 / 1024;
    long free_ram = s_info.freeram / 1024 / 1024;
    sprintf(mem_info, "%ld MB / %ld MB", total_ram - free_ram, total_ram);
}

int main()
{
    struct utsname unameData;
    printf("Simple System Information\n");
    uname(&unameData);

    // Get the current user
    struct passwd *pw;
    uid_t uid = geteuid();
    pw = getpwuid(uid);
    if (pw == NULL)
    {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    char username[128];
    get_username_info(username);

    // Get uptime
    char uptime_str[128];
    get_uptime(uptime_str);

    // Get CPU info
    char cpu_info[256];
    get_cpu_info(cpu_info);

    // Get memory info
    char mem_info[128];
    get_memory_info(mem_info);
    printf("Hostname:\033[1;32m%s\033[0m@\033[1;32m%s\033[0m\n", pw->pw_name, unameData.nodename);
    printf("OS: \033[1;34m%s\033[0m\n", unameData.sysname);
    printf("Kernel: \033[1;34m%s\033[0m\n", unameData.release);
    printf("Uptime: \033[1;34m%s\033[0m\n", uptime_str);
    printf("CPU: \033[1;34m%s\033[0m\n", cpu_info);
    printf("Memory: \033[1;34m%s\033[0m\n", mem_info);

    return 0;
}
