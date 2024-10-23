int get_year(const char *date) {
    char buffer[strlen(date) + 1];
    strcpy(buffer, date);
    return atoi(strtok(buffer, "-/ "));
}
