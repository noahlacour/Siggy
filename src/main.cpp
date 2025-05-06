#include "config.h"
#include "aws_s3.h"
#include <aws/core/Aws.h>
#include <iostream>

// Displays the main CLI menu options.
void show_main_menu()
{
    std::cout << "\n===== Siggy AWS S3 Tool =====\n"
    << "1) Check connection status\n"
    << "2) Create pre-signed link\n"
    << "3) List all objects in bucket\n"
    << "4) Exit\n"
    << "Enter choice: ";
}

// Displays the submenu for creating pre-signed links.
void show_link_menu()
{
    std::cout << "\n-- Create Link --\n"
    << "1) For existing object\n"
    << "2) Upload new object + create link\n"
    << "Enter choice: ";
}

int main()
{
    Config config;

    // Load configuration from the config.ini file.
    if(!load_config(config, "../config/config.ini"))
    {
        return 1;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        int choice = 0;
        while (choice != 4)
        {
            show_main_menu();
            std::cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    // Check connection status to the S3 bucket.
                    check_connection_status(config);
                    break;
                }
                
                case 2:
                {
                    show_link_menu();
                    int link_choice;
                    std::cin >> link_choice;

                    switch (link_choice)
                    {
                        case 1:
                        {
                            // Generate a pre-signed URL for an existing S3 object.
                            std::string object_key;
                            long expiry;
                            std::cout << "Enter object key: ";
                            std::cin >> object_key;
                            std::cout << "Enter expiry time in seconds: ";
                            std::cin >> expiry;
                            std::string url = generate_presigned_url(config, object_key, expiry);
                            std::cout << "Pre-signed URL:\n" << url << "\n";
                            break;
                        }

                        case 2:
                        {
                            // Upload a new file to S3 and generate a pre-signed URL.
                            std::string local_path, object_key;
                            long expiry;
                            std::cout << "Enter local file path: ";
                            std::cin >> local_path;
                            object_key = local_path.substr(local_path.find_last_of("/\\") + 1);
                            std::cout << "Enter expiry time in seconds: ";
                            std::cin >> expiry;

                            if (upload_file(config, local_path, object_key))
                            {
                                std::cout << "Upload successful.\n";
                                std::string url = generate_presigned_url(config, object_key, expiry);
                                std::cout << "Pre-signed URL:\n" << url << "\n";
                            }
                            else
                            {
                                std::cerr << "Upload failed.\n";
                            }
                            break;
                        }

                        default:
                        {
                            std::cout << "Invalid link option. try again.\n";
                        }
                    }
                    break;
                }

                case 3:
                {
                    // List all objects in the connected S3 bucket.
                    list_s3_objects(config);
                    break;
                }

                case 4:
                {
                    std::cout << "Goodbye!\n";
                    break;
                }

                default:
                {
                    std::cout << "Invalid choice. Try again.\n";
                    break;
                }
            }
        }
    }
    Aws::ShutdownAPI(options); // Clean up AWS SDK.

    return 0;
}