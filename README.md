<p align="center">
  <img src="assets/siggyLogo.png" alt="Siggy Logo" width="150"/>
</p>

<h1 align="center">Siggy - AWS S3 Pre-Signed URL Generator</h1>

<p align="center">
  <em>A minimal C++ CLI tool for managing S3 files and generating secure pre-signed URLs</em>
</p>

<p align="center">
  <a href="LICENSE">
    <img src="https://img.shields.io/github/license/noahlacour/Siggy.svg" alt="License">
  </a>
  <a href="https://github.com/noahlacour/Siggy/stargazers">
    <img src="https://img.shields.io/github/stars/noahlacour/Siggy?style=social" alt="GitHub stars">
  </a>
</p>

Siggy is a lightweight C++ command-line tool for interacting with AWS S3 buckets.

It lets you:
- Check connection status to an S3 bucket.
- Upload local files to the bucket.
- Generate pre-signed URLs for secure, time-limited access to bucket objects.

## Features
- Easy configuration using a `config.ini` file.
- Interactive CLI with multiple operations for ease of use.
- Upload new files or generate URLs for existing ones.
- Modular and clean C++ design with AWS SDK integration.

## Requirements
- AWS account with an access key, secret key, and S3 bucket.
- AWS IAM permissions for S3 operations (`ListObjects`, `GetObject`, `PutObject`).
- AWS SDK for C++ installed.
- C++17 compiler.

## Setup

1. Fill in `config/config.example.ini` with your specific credentials.
2. Rename the config file to `config.ini`.
3. Build the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
4. Run:
    ```bash
    ./siggy
    ```

## CLI Options
- Check connection status.
- List all objects in the bucket.
- Generate pre-signed link for existing object.
- Upload new object and generate link.
- Exit.

## License
MIT License

## Author
Noah LaCour-Thistle
