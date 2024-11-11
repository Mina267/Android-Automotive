#  Systemd and Service Files

Systemd is a powerful system and service manager for Linux operating systems, designed to start, stop, and manage services and daemons efficiently. It introduces parallelism in service startup, which significantly improves boot times compared to the traditional System V init.

### Systemd vs. System V Init

**Systemd:**
- Uses parallel startup to improve boot times.
- Introduces the concept of units and targets for better management.
- Centralized logging via `journald`.
- More granular control over service dependencies and states.

**System V Init:**
- Sequential startup of services.
- Uses runlevels for different system states.
- Limited dependency handling.
- Separate logging for each service.

### Directory Structure

Systemd unit files are stored in specific directories:

- **/etc/systemd/system/**: Custom unit files and user-defined configurations.
- **/lib/systemd/system/**: Default unit files provided by the package manager.
- **/run/systemd/system/**: Runtime unit files and configurations, often temporary.

### Types of Units

Systemd units are categorized by their types. Here are a few common ones:

1. **Service**: Defines a system service.
2. **Socket**: Describes an IPC or network socket.
3. **Mount**: Describes a mount point.
4. **Automount**: Describes an automount point.
5. **Target**: Groups units together, similar to runlevels.
6. **Path**: Describes a path for path-based activation.
7. **Timer**: Describes a timer for timer-based activation.

### Unit File Structure

A unit file consists of multiple sections, each with specific directives. Here is a detailed breakdown:

#### Example Unit File: `myservice.service`

```ini
[Unit]
Description=My Custom Service
Documentation=https://example.com/docs
After=network.target
Wants=another.service
Requires=some.service
Before=final.target

[Service]
Type=simple
ExecStart=/usr/bin/myservice
ExecStop=/usr/bin/stop-myservice
Restart=on-failure
RestartSec=3
WorkingDirectory=/usr/bin

[Install]
WantedBy=multi-user.target
```

#### Section Details

1. **[Unit]**
    - **Description**: A human-readable description of the unit.
    - **Documentation**: URL to the documentation.
    - **After**: Defines the order in which units are started. The unit will start after the specified unit.
    - **Wants**: Specifies optional dependencies. The listed unit is started if present but does not cause a failure if it fails to start.
    - **Requires**: Specifies mandatory dependencies. The listed unit must start successfully for the current unit to be activated.
    - **Before**: Ensures the current unit starts before the specified unit.

2. **[Service]**
    - **Type**: Defines the service type.
        - `simple`: The service is considered started as soon as the `ExecStart` process is forked.
        - `oneshot`: A service that runs a single task and then exits.
        - `forking`: The service starts in the background (daemonizes).
    - **ExecStart**: The command to start the service.
    - **ExecStop**: The command to stop the service.
    - **Restart**: When to restart the service.
        - `on-failure`: Restart on non-zero exit status.
        - `always`: Always restart the service when it exits.
    - **RestartSec**: Time to wait before restarting the service.
    - **WorkingDirectory**: The directory in which the service should run.

3. **[Install]**
    - **WantedBy**: Specifies the target under which this service should be enabled. For example, `multi-user.target` is analogous to runlevel 3 in System V, which is a multi-user, non-graphical environment.

### Creating and Managing Unit Files

#### Creating a Service Unit File

1. **Navigate to the systemd directory**:
    ```bash
    cd /etc/systemd/system
    ```

2. **Create a new service file**:
    ```bash
    sudo touch myservice.service
    ```

3. **Edit the service file**:
    ```bash
    sudo vim myservice.service
    ```

4. **Add the unit configuration**:
    ```ini
    [Unit]
    Description=My Custom Service
    After=network.target
    Wants=another.service
    Requires=some.service
    Before=final.target

    [Service]
    Type=simple
    ExecStart=/usr/bin/myservice
    ExecStop=/usr/bin/stop-myservice
    Restart=on-failure
    RestartSec=3
    WorkingDirectory=/usr/bin

    [Install]
    WantedBy=multi-user.target
    ```

5. **Reload systemd to recognize the new service**:
    ```bash
    sudo systemctl daemon-reload
    ```

6. **Enable the service to start at boot**:
    ```bash
    sudo systemctl enable myservice
    ```

7. **Start the service**:
    ```bash
    sudo systemctl start myservice
    ```

8. **Check the status of the service**:
    ```bash
    sudo systemctl status myservice
    ```

#### Enabling and Linking Unit Files

When you enable a service, Systemd creates a symbolic link from the service file in `/etc/systemd/system/` to the appropriate target directory. For example:

```bash
sudo systemctl enable myservice
```

This command creates a symlink:

```bash
/etc/systemd/system/multi-user.target.wants/myservice.service -> /etc/systemd/system/myservice.service
```

### Targets

Targets group units together and are used to manage system states. Common targets include:

- **graphical.target**: Multi-user system with graphical interface.
- **multi-user.target**: Multi-user system without graphical interface (analogous to runlevel 3).
- **rescue.target**: Single-user mode with minimal services (similar to runlevel 1).
- **emergency.target**: Emergency shell.

#### Changing the Default Target

1. **Get the current default target**:
    ```bash
    systemctl get-default
    ```

2. **Set a new default target**:
    ```bash
    sudo systemctl set-default multi-user.target
    ```

3. **Reboot to apply changes**:
    ```bash
    sudo reboot
    ```

### Practical Example

#### Creating a Ping Service

1. **Create a service file**:
    ```bash
    sudo nano /etc/systemd/system/pingtest.service
    ```

2. **Add the following configuration**:

    ```ini
    [Unit]
    Description=Ping Test Service
    After=network.target

    [Service]
    Type=simple
    ExecStart=/bin/ping -c 4 8.8.8.8
    Restart=on-failure
    RestartSec=5

    [Install]
    WantedBy=multi-user.target
    ```

3. **Reload systemd**:
    ```bash
    sudo systemctl daemon-reload
    ```

4. **Enable the service**:
    ```bash
    sudo systemctl enable pingtest
    ```

5. **Start the service**:
    ```bash
    sudo systemctl start pingtest
    ```

6. **Check the status of the service**:
    ```bash
    sudo systemctl status pingtest
    ```

7. **View logs for the service**:
    ```bash
    journalctl -u pingtest
    ```

### Commands Summary

- **Start a service**:
    ```bash
    sudo systemctl start myservice
    ```

- **Stop a service**:
    ```bash
    sudo systemctl stop myservice
    ```

- **Restart a service**:
    ```bash
    sudo systemctl restart myservice
    ```

- **Enable a service to start at boot**:
    ```bash
    sudo systemctl enable myservice
    ```

- **Disable a service**:
    ```bash
    sudo systemctl disable myservice
    ```

- **Check the status of a service**:
    ```bash
    sudo systemctl status myservice
    ```

- **View logs for a service**:
    ```bash
    journalctl -u myservice
    ```

- **Reload systemd manager configuration**:
    ```bash
    sudo systemctl daemon-reload
    ```

### Understanding Process Types

1. **Foreground Process**: Runs in the foreground, blocking the shell until it completes.
2. **Background Process**: Runs in the background, allowing the shell to be used for other commands.
3. **Orphan Process**: A process whose parent has been killed. Systemd (PID 1) adopts orphan processes.
4. **Zombie Process**: A process that has completed but still has an entry in the process table. It occurs when the parent has not read the exit status of the terminated child process.
5. **Daemon Process**: A background process that is detached from the terminal and runs continuously, often started by Systemd as a service.

By understanding and using these concepts, you can effectively manage and configure services in a Systemd-based Linux environment. This guide provides a solid foundation for creating, managing, and troubleshooting services and units with Systemd.