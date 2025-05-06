#pragma once
#include "config.h"

/**
* @brief Lists all S3 objects in the bucket specified by the Config struct.
* @param config Reference to the config metadata struct.
*/
void list_s3_objects(const Config& config);

/**
 * @brief Generates a presigned URL for a specified s3 bucket object.
 * @param config Reference to the config metadata struct.
 * @param object_key Key (name) of S3 object to presign.
 * @param expiration_seconds Number of seconds before the presigned URL expires.
 * @return The generated presigned URL as a string.
 */
std::string generate_presigned_url(const Config& config, const std::string& object_key, long expiration_seconds);

/**
 * @brief Checks the connection status to AWS and the specified S3 bucket.
 * @param config Reference to the config metadata struct.
 */
void check_connection_status(const Config& config);

/**
 * @brief Uploads a local file to a specific S3 bucket.
 * @param config Reference to the config metadata struct.
 * @param local_path Path to the local file to upload.
 * @param object_key S3 object key (name) to assign to the uploaded file.
 * @return True if the upload suceeds, false otherwise.
 */
bool upload_file(const Config& config, const std::string& local_path, const std::string& object_key);
