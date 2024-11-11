

# Package Management

Package management in Linux involves installing, updating, and removing software packages. Different distributions use different package managers. Below is a detailed guide for Debian and RedHat-based systems, and an overview of the `apt` package manager.

### Debian
- **Package Manager**: `dpkg`
- **Commands**:
  - **Install a package**: 
    ```sh
    dpkg -i file_name.deb
    ```
    This command installs the specified `.deb` package.
  - **List files in a package**:
    ```sh
    dpkg -L package_name
    ```
    This command lists all the files installed by the specified package.

### RedHat
- **Package Manager**: `rpm`
- **General Information**:
  - Packages are collections of files that are bundled together for easy installation and management.

### APT (Advanced Package Tool)
- **Type**: High-level package manager
- **Functionality**:
  - Uses `dpkg` for installing dependencies.
  - Maintains a server containing all packages.
- **Commands**:
  - **Install a package and all required libraries**:
    ```sh
    sudo apt install package_name
    ```
    This command installs the specified package along with all its dependencies.
  - **Upgrade packages to the latest versions**:
    ```sh
    sudo apt upgrade
    ```
    This command upgrades all installed packages to their latest available versions.
  - **Update the package list to fetch new updates from the repository**:
    ```sh
    sudo apt update
    ```
    This command updates the local package list with the latest information from the repositories.
- **Notes**:
  - Packages like VS Code are fetched from the server, not directly from the website. You need to know the package name on the server.

### Snap
- **Notes**:
  - Does not depend on the distribution.
  - Works only on PCs.
  - Provides a way to package and distribute software that works across different Linux distributions.

## Compressing and Archiving

Compression and archiving are essential for packaging files to send them efficiently.

### Archiving
- **Create an archive**:
  ```sh
  tar -cf archive.tar file1 file2 dir1/
  ```
  - **Options**:
    - `-c`: Create a new archive.
    - `-f`: Specify the output file.

- **Determine file type**:
  ```sh
  file archive.tar
  ```
  This command shows the type of the specified file.

- **Extract files from an archive**:
  ```sh
  tar -xf archive.tar -C mydir/
  ```
  - **Options**:
    - `-x`: Extract files.
    - `-C`: Change to directory.

### Compression Algorithms
- **Algorithms**: gzip, xz, bzip2
- **Formats**:
  - `tar.gz`: Uses gzip (`-z` option).
  - `tar.xz`: Uses xz (`-J` option).
  - `tar.bz2`: Uses bzip2 (`-j` option).

- **Gzip Compression**:
  - **Compress a file**:
    ```sh
    gzip file
    ```
    This command compresses the specified file using gzip.
  - **Decompress a file**:
    ```sh
    gzip -d file.gz
    ```
    This command decompresses the specified gzip file.

- **Bzip2 Compression**:
  - **Compress a file**:
    ```sh
    bzip2 file
    ```
    This command compresses the specified file using bzip2.
  - **Decompress a file**:
    ```sh
    bunzip2 file.bz2
    ```
    This command decompresses the specified bzip2 file.

## User Management

Linux systems have different types of users with unique IDs and roles.

### User Types
- **Normal User**: ID range 1000 - 40000
- **System User**: ID range 1 - 199
- **Service User**: ID range 200 - 999

### SSH
- **Function**: Secure shell for remote access.
- **Connection**: Server <--- Client

### User and Group Information
- **List ownership and group**:
  ```sh
  ls -lh
  ```
  This command lists files along with their ownership and group information.
- **User Information**:
  - Primary user information is stored in `/etc/passwd`.
  - Encrypted passwords are stored in `/etc/shadow`.
  - **Format**: `Name:UID:GID:Comment:HomeDirectory:ShellType`

- **Commands**:
  - **Find user information**:
    ```sh
    cat /etc/passwd | grep username
    ```
    This command searches for a specific username in the `/etc/passwd` file.
  - **Count users using specific shells**:
    ```sh
    cat /etc/passwd | grep /bin/bash | wc -l
    ```
    This command counts the number of users using the `/bin/bash` shell.

### Sudo
- **Notes**:
  - `sudo`: A group that allows users to execute commands as the superuser.
  - **Configuration file**: `/etc/sudoers`

### Adding Users and Groups
- **Add a new user**:
  ```sh
  sudo adduser NEW_USER
  ```
  Follow the prompts for password and comment.

- **Add a new group**:
  ```sh
  sudo groupadd GROUP_NAME
  ```

- **Edit sudoers file**:
  ```sh
  sudo visudo
  ```
  - Example entry to grant sudo privileges:
    ```sh
    %sudo ALL=(ALL:ALL) ALL
    %hero ALL=(ALL:ALL) ALL
    ```

- **Add a user to a group**:
  - Edit `/etc/group`:
    ```sh
    GROUP_NAME:x:GID:NEW_USER
    ```
  - Alternatively, use:
    ```sh
    sudo usermod -aG GROUP_NAME NEW_USER
    ```

- **Switch to a new user**:
  ```sh
  su NEW_USER
  ```

