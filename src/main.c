#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // mock up

    FILE *file = fopen("data.json", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_content = malloc(file_size + 1);
    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';
    fclose(file);

    printf("Original JSON:\n%s\n\n", json_content);

    char *old_value = "\"old_value\"";
    char *new_value = "\"new_value\"";

    char *pos = strstr(json_content, old_value);
    if (pos != NULL) {
        // Create new string with replacement
        char *modified = malloc(file_size + 50);  // Extra space
        long before_len = pos - json_content;

        strncpy(modified, json_content, before_len);
        modified[before_len] = '\0';
        strcat(modified, new_value);
        strcat(modified, pos + strlen(old_value));

        free(json_content);
        json_content = modified;
    }

    printf("Modified JSON:\n%s\n\n", json_content);

    file = fopen("data.json", "w");
    if (file == NULL) {
        printf("Error writing file\n");
        free(json_content);
        return 1;
    }

    fwrite(json_content, 1, strlen(json_content), file);
    fclose(file);

    printf("File saved, mission accomplished!");

    free(json_content);

    return 0;
}
