#pragma once
#include <string>

/**
 * @brief Holds AWS configuration metadata loaded from the config.ini file.
 */
struct Config
{
    std::string access_key;     ///< AWS access key ID
    std::string secret_key;     ///< AWS secret access key
    std::string region = "us-east-1";   ///< AWS region (default: us-east-1)
    std::string bucket_name;    ///< Name of the s3 bucket
};

/**
 * @brief Attempts to load AWS configuration settings from the config.ini file.ADJ_OFFSET_SINGLESHOT
 * @param config Reference to the config metadata struct to populate.
 * @param filename directory path to the config.ini file.
 */
bool load_config(Config& config, const std::string& filename);