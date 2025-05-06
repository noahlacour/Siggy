#include "aws_s3.h"
#include <aws/core/auth/AWSCredentials.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsV2Request.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/core/utils/DateTime.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/core/utils/memory/stl/AWSStreamFwd.h>
#include <fstream>
#include <iostream>

// Creates a S3 client object using the configuration parameters.
std::shared_ptr<Aws::S3::S3Client> create_s3_client(const Config& config)
{
    Aws::S3::S3ClientConfiguration s3config;
    s3config.region = config.region;

    Aws::Auth::AWSCredentials credentials(config.access_key, config.secret_key);
    return std::make_shared<Aws::S3::S3Client>(credentials, s3config, Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false, Aws::S3::US_EAST_1_REGIONAL_ENDPOINT_OPTION::LEGACY);
}

void list_s3_objects(const Config& config)
{
    // Initialize the S3 client and prepare the ListObjectsV2 request.
    auto s3_client = create_s3_client(config);
    Aws::S3::Model::ListObjectsV2Request request;
    request.WithBucket(config.bucket_name);
    auto outcome = s3_client->ListObjectsV2(request);

    // Print the list of objects if the request succeeds; otherwise, display the error.
    if (outcome.IsSuccess())
    {
        std::cout << "Objects in bucket '" << config.bucket_name << "':\n";
        for (const auto& object : outcome.GetResult().GetContents())
        {
            std::cout << " - " << object.GetKey() << "\n";
        }
    }
    else
    {
        std::cerr << "Failed to list objects: " << outcome.GetError().GetMessage() << "\n";
    }
}

std::string generate_presigned_url(const Config& config, const std::string& object_key, long expiration_seconds)
{
    // Initialize the S3 client and perpare the presigned URL request.
    auto s3_client = create_s3_client(config);
    Aws::Http::URI uri;
    Aws::S3::Model::GetObjectRequest request;
    request.WithBucket(config.bucket_name).WithKey(object_key);

    // Generate and return the presigned URL.
    uri = s3_client->GeneratePresignedUrl(config.bucket_name, object_key, Aws::Http::HttpMethod::HTTP_GET, expiration_seconds);
    return uri.GetURIString();
}

void check_connection_status(const Config& config)
{
    // Initialize the S3 client and prepare the ListObjectsV2 request.
    auto s3_client = create_s3_client(config);
    Aws::S3::Model::ListObjectsV2Request request;
    request.WithBucket(config.bucket_name);
    auto outcome = s3_client->ListObjectsV2(request);

    // Print vitial connection parameters if request succeeds; otherwise, display the error.
    if (outcome.IsSuccess())
    {
        std::cout << "Connection status: CONNECTED\n";
        std::cout << "Bucket: " << config.bucket_name << "\n";
        std::cout << "User (access key): " << config.access_key << "\n";
    }
    else
    {
        std::cerr << "Connection status: FAILED - " << outcome.GetError().GetMessage() << "\n";
    }

}

bool upload_file(const Config& config, const std::string& local_path, const std::string& object_key)
{
    // Initialize the S3 client and prepare the upload request.
    auto s3_client = create_s3_client(config);
    Aws::S3::Model::PutObjectRequest request;
    request.WithBucket(config.bucket_name).WithKey(object_key);
    auto input_data = Aws::MakeShared<Aws::FStream>("UploadTag", local_path.c_str(), std::ios_base::in | std::ios_base::binary);

    // Display an error and return false if the file cannot be opened.
    if (!input_data->good())
    {
        std::cerr << "Error: Unable to open file: " << local_path << "\n";
        return false;
    }

    // Set the request body and execute the upload.
    request.SetBody(input_data);
    auto outcome = s3_client->PutObject(request);

    // Return true if the upload succeeds; otherwise, display the error and return false.
    if (outcome.IsSuccess())
    {
        return true;
    }
    else
    {
        std::cerr << "PutObject error: " << outcome.GetError().GetMessage() << "\n";
        return false;
    }
}

