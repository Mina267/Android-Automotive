In Android, both the **Low Memory Killer (LMK)** and the **Out of Memory (OOM) Killer** are mechanisms designed to manage memory and prevent the system from running out of resources. They work in different layers of the system but share the same objective: freeing up memory to keep the device responsive and stable.

### 1. **Low Memory Killer (LMK)**

The Low Memory Killer is a specialized Android process designed specifically for mobile devices and embedded systems, where resources are limited, and memory management is critical. Here’s a breakdown of how LMK works:

#### **How LMK Works**
- **Kernel Layer**: LMK is implemented as part of the Linux kernel with specific parameters tuned for Android's memory management needs.
- **Threshold Monitoring**: LMK monitors predefined memory thresholds (usually set by Android’s configuration files like `lowmemorykiller` kernel driver). When free memory drops below these thresholds, LMK is triggered to start freeing memory by killing processes.

#### **Main Functionality of LMK**
- **Process Prioritization**: LMK uses the *OOM score* and categories from Android’s *ActivityManager* to decide which processes to kill. For instance, cached apps (background apps that the user is not currently interacting with) are prioritized for termination before more critical system processes.
- **Process Killing**: LMK removes the processes from memory by sending them termination signals.
- **Avoiding User Disruption**: LMK primarily targets background apps and cached services, so the user experience remains as smooth as possible.

#### **What Happens After LMK Kills a Process?**
- **Temporary Termination**: LMK does not permanently disable an app. If the app is reopened, the system will restart it as usual.
- **Automatic Restart**: For services (like media playback) that are required to run in the background, the system may automatically restart them after they’re killed if they are marked as persistent or have a notification-bound service.

### 2. **Out of Memory (OOM) Killer**

The OOM Killer is a more general memory management tool built into the Linux kernel, which Android inherits. It serves as a last resort when system memory becomes critically low and LMK has not managed to free up enough memory.

#### **How OOM Killer Works**
- **System-Wide Check**: Unlike LMK, which is configured specifically for Android’s memory needs, the OOM Killer is activated when the entire system is dangerously low on memory.
- **Process Selection**: The OOM Killer evaluates processes based on the OOM score (a measure of how safe it is to kill a process), which is influenced by factors like memory usage, priority, and importance to the user.
- **Immediate Termination**: When a process is selected for termination, the OOM Killer frees up its memory immediately to prevent the system from crashing.

#### **Main Functionality of OOM Killer**
- **Last-Resort Measure**: OOM Killer is intended as a “panic button” for memory management. It operates independently of LMK but takes over when the memory situation becomes dire.
- **Prevention of System Failure**: By killing processes, the OOM Killer ensures that the device does not entirely run out of memory, which could lead to a system freeze or crash.

#### **What Happens After OOM Killer Kills a Process?**
- **Process Termination**: Processes killed by the OOM Killer do not automatically restart, as the system is focusing on conserving memory.
- **System Restart**: In cases where critical system processes are killed (very rare), the system may require a reboot to stabilize.

### **How LMK and OOM Killer Interact in Android**

- **LMK First, OOM as Backup**: Android’s memory management prioritizes LMK over the OOM Killer. The system tries to prevent hitting a critical low-memory threshold by utilizing LMK’s Android-optimized memory management. The OOM Killer is only activated when LMK is not enough to resolve a severe memory shortage.
- **Configured for Different Memory Levels**: LMK has specific memory thresholds and scales with Android’s memory requirements, while the OOM Killer acts as a system safeguard. These thresholds can vary by device type and the amount of available RAM.
  
### **Under the Hood: Process and Memory Management**

1. **OOM Scores and Adjacent Levels**: Each process in Android is assigned an OOM score based on its importance to the user and system, such as `FOREGROUND_APP`, `VISIBLE_APP`, `BACKGROUND_APP`, and `CACHED_APP`. The system dynamically adjusts these scores, so high-priority apps (foreground apps) are the last to be killed.

2. **Killing Decisions**: LMK or the OOM Killer reads the OOM score, checks the current memory pressure, and sends a `SIGKILL` to the selected process. LMK is more aggressive at lower memory thresholds, where it continually manages cached or background apps, while OOM Killer only intervenes when LMK cannot keep up.

3. **Application Lifecycle**: Android applications follow a specific lifecycle (e.g., `onPause`, `onStop`, `onDestroy`). LMK leverages this lifecycle, killing lower-priority processes while keeping higher-priority processes (foreground apps) active. Processes killed by LMK or OOM Killer can typically restart based on user interaction or system demand.

### **In Summary**

- **LMK** is an Android-specific memory management tool, optimized for mobile use and works to kill processes based on priority and memory levels to keep the device responsive.
- **OOM Killer** is a Linux kernel feature that serves as a last resort to free memory in critical situations and works without knowledge of Android-specific process priorities.

Both mechanisms ensure that an Android device does not run out of memory entirely. LMK frequently kills lower-priority processes, which can be restarted when needed, while the OOM Killer’s actions are generally more permanent, especially for non-critical applications.