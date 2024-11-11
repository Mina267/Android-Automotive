
## 1. **Install Required Packages**
   To set up the environment, you'll need to install several packages using the following command:

   ```bash
   sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python3 python3-pip python3-pexpect
   ```

   - **gawk**: Text processing and pattern matching.
   - **wget**: Downloads files from the internet.
   - **git-core**: Version control system (may be called `git` in some distributions).
   - **diffstat**: Provides statistics on file changes.
   - **unzip**: Extracts files from ZIP archives.
   - **texinfo**: Produces documentation in various formats.
   - **gcc-multilib**: Enables cross-compilation for multiple architectures.
   - **build-essential**: Installs essential tools for building software.
   - **chrpath**: Modifies rpath or runpath in executables.
   - **socat**: Facilitates bidirectional data transfer between channels.
   - **cpio**: Archiving utility.
   - **python3**: Python 3 interpreter.
   - **python3-pip**: Package installer for Python 3.
   - **python3-pexpect**: Controls interactive programs, useful for automation.

## 2. **Create Yocto Directory and Navigate to It**
   Create a directory for the Yocto Project and enter it:

   ```bash
   mkdir ~/yocto && cd ~/yocto
   ```

## 3. **Clone the Yocto Project Repository**
   Clone the `kirkstone` branch of the Poky repository:

   ```bash
   git clone -b kirkstone https://git.yoctoproject.org/git/poky.git
   cd poky
   ```

   - **git clone -b kirkstone**: Clones the specific `kirkstone` branch from the repository.

## 4. **Set Up the Poky Environment**
   Source the environment setup script:

   ```bash
   source oe-init-build-env
   ```

   - **source oe-init-build-env**: Configures the environment for building with Yocto by setting up necessary environment variables and tools.

## 5. **Edit the Configuration File**
   Modify the `local.conf` file to set the target machine:

   ```bash
   cd conf
   vim local.conf
   ```

   - Change `MACHINE` variable to `Target you desire`.

## 6. **Build the Yocto Project**
   Start the build process:

   ```bash
   bitbake -k core-image-minimal
   ```

   - **bitbake -k core-image-minimal**: This command builds a minimal image for the specified target machine. The `-k` option allows the build process to continue even if some tasks fail.

## Error
* in distribution `ubuntu-24.04`
```bash
sudo apparmor_parser -R /etc/apparmor.d/unprivileged_userns
```
