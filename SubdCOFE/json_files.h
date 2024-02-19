#ifndef JSON_FILES_H
#define JSON_FILES_H

char* extract_json_data(char* request);
const char* read_json_file(const char* filename);
void save_json_to_file(const char* json_data, const char* filename);

#endif