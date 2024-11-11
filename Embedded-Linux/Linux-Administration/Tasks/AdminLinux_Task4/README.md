
# Section 1: 

<p align="center">
	<img src="https://github.com/user-attachments/assets/705c81f5-3086-476f-8013-46896711398b" width=100% height=100% />
</p>

# Section 2: 

## 1. Create a supplementary (Secondary) group called pgroup with group ID of 30000  

<p align="center">
	<img src="https://github.com/user-attachments/assets/f24d9226-a123-4d14-adf6-88ece85e6028" width=100% height=100% />
</p>

## 2. Lock any user created account so he can't log in  

<p align="center">
	<img src="https://github.com/user-attachments/assets/73987fb5-2285-45f9-ad6b-3d7a7301fa74" width=100% height=100% />
</p>

## 3. Delete user account  
## 4. Delete group account 

<p align="center">
	<img src="https://github.com/user-attachments/assets/efb1b2c4-333f-41c9-bc15-d1a68aad9a2c" width=100% height=100% />
</p>



## 5. State the difference between adduser and useradd with example shown. 

<p align="center">
	<img src="https://github.com/user-attachments/assets/3f55a2f6-7417-4afe-9ca0-023b9ba9b97b" width=100% height=100% />
</p>




## Difference between `adduser` and `useradd`

### `useradd`
- **Type**: Low-level utility
- **Functionality**: Directly modifies system files to create a user
- **Defaults**: Does not create home directory or set shell unless specified

**Example:**
```sh
sudo useradd -m -d /home/newuser -s /bin/bash newuser
```
- `-m`: Creates home directory
- `-d /home/newuser`: Specifies home directory path
- `-s /bin/bash`: Sets default shell
- `newuser`: Username

### `adduser`
- **Type**: High-level utility
- **Functionality**: User-friendly script that uses `useradd` and handles additional setup
- **Defaults**: Creates home directory, sets shell, prompts for password and user information

**Example:**
```sh
sudo adduser newuser
```
- Prompts for password
- Creates home directory
- Sets default shell
- Collects additional user information

### Summary
- **Ease of Use**: `adduser` is more user-friendly, `useradd` requires more options
- **Defaults**: `adduser` handles defaults automatically, `useradd` does not
- **Functionality**: `adduser` is a script with additional setup, `useradd` is a binary

Use `adduser` for simplicity and interactive setup. Use `useradd` for more control over user creation options.
