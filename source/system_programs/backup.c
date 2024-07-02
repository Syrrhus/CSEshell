#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void main() {
    char *backupDir = getenv("BACKUP_DIR");
    if (!backupDir) {
        printf("Error: BACKUP_DIR environment variable is not set.\n");
        return;
    }

    char *projectDir = "/usr/bin";
    if (!projectDir) {
        printf("Error: PROJECT_DIR environment variable is not set.\n");
        return;
    }

    // Construct the archive path
    char archivePath[1024];
    snprintf(archivePath, sizeof(archivePath), "%s/archive/", projectDir);

    // Get the current datetime
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char dateStr[128];
    strftime(dateStr, sizeof(dateStr), "%Y%m%d%H%M%S", t);

    // Create the filename with datetime
    char zipFile[2048];
    snprintf(zipFile, sizeof(zipFile), "%sbackup-%s.zip", archivePath, dateStr);

    // Construct the zip command
    char command[2048];
    snprintf(command, sizeof(command), "zip -r %s %s", zipFile, backupDir);

    // Execute the zip command
    printf("Creating backup of '%s' at '%s'\n", backupDir, zipFile);
    if (system(command) == -1) {
        perror("Failed to execute command");
    } else {
        printf("Backup created successfully.\n");
    }
}


