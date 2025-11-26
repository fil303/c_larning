#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <limits.h>

#define WALLPAPER_DIR "wallpapers"
#define MAX_PATH 4096
#define MAX_FILES 256

int has_image_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot) return 0;
    return (strcasecmp(dot, ".jpg") == 0 || strcasecmp(dot, ".jpeg") == 0 || strcasecmp(dot, ".png") == 0);
}

int main(int argc, char *argv[]) {
    int loop_time;
    if (argc < 2) {
        printf("No time passed. default is 15 minutes\n");
        loop_time = 15;
    }else{
        loop_time = atoi(argv[1]);
    }
    srand(time(NULL));
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }



    char username[128]; // buffer to store username
    FILE *fp;

    // run the command "whoami" and open pipe
    fp = popen("whoami", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // read the output into username buffer
    if (fgets(username, sizeof(username), fp) != NULL) {
        // remove trailing newline if any
        size_t len = strlen(username);
        if (len > 0 && username[len-1] == '\n') {
            username[len-1] = '\0';
        }
        printf("Current user: %s\n", username);
    }

    pclose(fp);

    char wallpaper_dir_path[MAX_PATH];
    snprintf(wallpaper_dir_path, sizeof(wallpaper_dir_path), "/home/%s/Pictures/%s", username, WALLPAPER_DIR);

    while (1) {
        DIR *d;
        struct dirent *dir;
        d = opendir(wallpaper_dir_path);
        
        if (d) {
            char *files[MAX_FILES];
            int file_count = 0;

            while ((dir = readdir(d)) != NULL) {
                if (dir->d_type == DT_REG && has_image_extension(dir->d_name)) {
                    if (file_count < MAX_FILES) {
                        files[file_count] = strdup(dir->d_name);
                        file_count++;
                    }
                }
            }
            closedir(d);
            if (file_count > 0) {
                int random_index = rand() % file_count;
                char full_path[MAX_PATH];

                snprintf(full_path, sizeof(full_path), "%s/%s", wallpaper_dir_path, files[random_index]);
                char command[MAX_PATH * 2];
                // Set for both light and dark modes to be safe on newer GNOME versions
                snprintf(command, sizeof(command), "gsettings set org.mate.background picture-filename '%s'", full_path);
                system(command);

                // snprintf(command, sizeof(command), "gsettings set org.gnome.desktop.background picture-uri-dark '%s'", full_path);
                // system(command);

                printf("Changed wallpaper to: %s\n", files[random_index]);

                // Free memory
                for (int i = 0; i < file_count; i++) {
                    free(files[i]);
                }
            } else {
                printf("No images found in %s\n", wallpaper_dir_path);
            }
        } else {
            printf("Could not open directory %s\n", wallpaper_dir_path);
        }

        sleep(loop_time*60);
    }

    return 0;
}
