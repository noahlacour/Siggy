#include "config.h"
#include <ini.h>
#include <cstring>
#include <iostream>

// INI handler callback: parses each section/key/value and updates the Config struct.
static int handler(void* user, const char* section, const char* name, const char* value)
{
    Config* pconfig = (Config*)user;    // casts user data pointer to Config metadata struct.

    // Check for specific sections within the config.ini and update corresponding fields.
    // Check the [aws] section.
    if (strcmp(section, "aws") == 0)
    {
        if (strcmp(name, "access_key") == 0) { pconfig->access_key = value; }
        else if (strcmp(name, "secret_key") == 0) { pconfig->secret_key = value; }
        else if (strcmp(name, "region") == 0) { pconfig->region = value; }
    }
    // Check the [s3] section.
    else if (strcmp(section, "s3") == 0)
    {
        if (strcmp(name, "bucket_name") == 0) { pconfig->bucket_name = value; }
    }

    return 1;
}

bool load_config(Config& config, const std::string& filename)
{
    // Attempt to parse the config.ini file; return false if it fails.
    if(ini_parse(filename.c_str(), handler, &config) < 0)
    {
        std::cerr << "Can't load config file: " << filename << "\n";
        return false;
    }

    return true;
}