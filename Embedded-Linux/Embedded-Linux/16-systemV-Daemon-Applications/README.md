
# Creating and Managing Daemon Applications with Init Scripts and Runlevels

This guide will walk you through the steps to create a simple daemon application, set up init scripts, and manage the application through runlevels.

### Start Qemu
```sh
cd /home/mina/bulidroot/buildroot/output/images
```

```sh
source start-qemu.sh
```


### Step 1: Create the Daemon Application

1. **Navigate to the `/bin` directory**:
    ```sh
    cd /bin/
    ```

2. **Create the daemon application script**:
    ```sh
    touch daemonapp
    vim daemonapp
    ```

3. **Add the following content to `daemonapp`**:
    ```bash
    #!/bin/sh
    while true
    do
        echo "Daemonapp is running!" >> /tmp/daemon.test
        sleep 10
    done
    ```

4. **Make the script executable**:
    ```sh
    chmod +x daemonapp
    ```

### Step 2: Edit the `inittab` File

1. **Navigate to the `/etc` directory**:
    ```sh
    cd /etc/
    ```

2. **Edit the `inittab` file**:
    ```sh
    vim inittab
    ```

3. **Add the following runlevel entries**:
    ```bash
    rc1:1:wait:/etc/init.d/rc 1
    rc2:2:wait:/etc/init.d/rc 2
    rc3:3:wait:/etc/init.d/rc 3
    rc4:4:wait:/etc/init.d/rc 4
    rc5:5:wait:/etc/init.d/rc 5
    ```

### Step 3: Create Init Scripts

1. **Navigate to the `/etc/init.d` directory**:
    ```sh
    cd /etc/init.d
    ```

2. **Create the init script for the daemon application**:
    ```sh
    touch daemonapp
    vim daemonapp
    ```

3. **Add the following content to the `daemonapp` script**:
    ```bash
    #!/bin/sh
    case "$1" in
      start)
           echo "Starting daemonapp..."
           start-stop-daemon -S -n daemonapp -a /bin/daemonapp &
           ;;
      stop)
           echo "Stopping daemonapp..."
           start-stop-daemon -K -n daemonapp -a /bin/daemonapp
           ;;
      *)
           echo "Usage: $0 {start|stop}"
           exit 1
    esac
    exit 0
    ```

4. **Make the init script executable**:
    ```sh
    chmod +x daemonapp
    ```

### Step 4: Create Directories for Each Runlevel

1. **Navigate to the `/etc` directory**:
    ```sh
    cd /etc/
    ```

2. **Create directories for runlevels 2 and 3**:
    ```sh
    mkdir rc2.d
    mkdir rc3.d
    ```

### Step 5: Create Symbolic Links

1. **Navigate to the `rc2.d` directory**:
    ```sh
    cd /etc/rc2.d
    ```

2. **Create a symbolic link to start the daemon application**:
    ```sh
    ln -s /etc/init.d/daemonapp S01daemonapp.sh
    ```

3. **Navigate to the `rc3.d` directory**:
    ```sh
    cd /etc/rc3.d
    ```

4. **Create a symbolic link to stop the daemon application**:
    ```sh
    ln -s /etc/init.d/daemonapp K01daemonapp.sh
    ```

### Step 6: Create the `rc` Script

1. **Navigate to the `/etc/init.d` directory**:
    ```sh
    cd /etc/init.d
    ```

2. **Create the `rc` script**:
    ```sh
    touch rc
    vim rc
    ```

3. **Add the following content to the `rc` script**:
    ```bash
    #!/bin/sh
    # Check if one argument is provided
    if [ $# -ne 1 ]; then
        echo "Usage: $0 <runlevel>"
        exit 1
    fi
    # Define the folder path based on the argument
    folder="rc$1.d"
    # Kill scripts starting with K
    for i in /etc/$folder/K??* ;do
         # Ignore dangling symlinks (if any).
         [ ! -f "$i" ] && continue
         case "$i" in
            *.sh)
                # Source shell script for speed.
                (
                    trap - INT QUIT TSTP
                    set stop
                    . $i
                )
                ;;
            *)
                # No sh extension, so fork subprocess.
                $i stop
                ;;
        esac
    done
    # Start scripts starting with S
    for i in /etc/$folder/S??* ;do
         # Ignore dangling symlinks (if any).
         [ ! -f "$i" ] && continue
         case "$i" in
            *.sh)
                # Source shell script for speed.
                (
                    trap - INT QUIT TSTP
                    set start
                    . $i
                )
                ;;
            *)
                # No sh extension, so fork subprocess.
                $i start
                ;;
        esac
    done
    ```

4. **Make the `rc` script executable**:
    ```sh
    chmod +x rc
    ```

### Verifying the Setup

1. **Reboot the system** to apply the changes and ensure the runlevel scripts are executed correctly.

2. **Check the `/tmp/daemon.test` file** to verify that the daemon application is running:
    ```sh
    cat /tmp/daemon.test
    ```

3. **Manually start and stop the daemon application** to test the init script:
    ```sh
    /etc/init.d/daemonapp start
    /etc/init.d/daemonapp stop
    ```

---
---
<p align="center">
	<img src="https://github.com/user-attachments/assets/c90535af-1aa0-4dd3-a324-39e14cf24f91" width=75% height=75% />
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/11fd8dea-b571-481e-96ec-09a59b99385a" width=75% height=75% />
</p>




<p align="center">
	<img src="https://github.com/user-attachments/assets/deb8fed0-5b53-45dd-a136-e469c8b8e7c6" width=75% height=75% />
</p>






