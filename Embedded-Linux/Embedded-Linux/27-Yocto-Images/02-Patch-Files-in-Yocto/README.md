# Using Patch Files in Yocto

### What is a Patch File?
A patch file is a text file that contains a list of differences between two versions of a file or set of files. It's used to apply changes to source code, making it easy to share and apply modifications without needing to redistribute entire files.

### Example Scenario
Suppose you have a `main.c` file in your project where you want to change the `loading_address` from `0x3000` to `0x4000`. Instead of distributing the entire modified file, you create a patch file that reflects only this change.

### Steps to Create and Apply a Patch

1. **Edit the Source File**:
   Modify the source file (`main.c`) as needed:
   ```c
   int main(){
       /* code */
       loading_address = 0x3000;  // Original line
       /* code */
   }
   ```

   Change it to:
   ```c
   int main(){
       /* code */
       loading_address = 0x4000;  // Modified line
       /* code */
   }
   ```

2. **Create the Patch File**:
   After making your changes, you can create a patch file using the `git diff` command:
   ```bash
   git diff main.c > myPatch.patch
   ```

   This command generates a patch file `myPatch.patch` that contains the difference between the original and modified versions of `main.c`.

3. **Revert the Changes**:
   If you want to revert the changes in your working directory to the original state:
   ```bash
   git reset --hard
   ```

4. **Apply the Patch File**:
   You can apply the patch to revert to your modifications or apply the patch on a different system:
   ```bash
   git apply ../myPatch.patch
   ```

### Using Patch Files in Yocto Recipes

In Yocto, patch files are commonly used to modify source code during the build process, especially when you don't control the upstream source.

1. **Add Patch File to `SRC_URI`**:
   In your recipe file (`.bb`), you specify the patch file in the `SRC_URI` variable:
   ```bash
   SRC_URI = "file://main.c \
              file://myPatch.patch"
   ```

   - `file://` indicates that the files are located in the same directory as your recipe or in a directory listed in `FILESPATH`.

2. **Patch Task (`do_patch`)**:
   The `do_patch` task is automatically included in most recipes and is responsible for applying patches specified in `SRC_URI`:
   ```bash
   do_patch() {
       # Applies patches listed in SRC_URI
       # No need to manually define this unless you have custom patching logic
   }
   ```

   Yocto will automatically apply the patch during the build process, ensuring that your modifications are included in the final build.

## Summary

- **Patch files** allow you to share and apply changes to code without distributing the entire file.
- In **Yocto**, you use patch files to modify the source code during the build process.
- You include patch files in the `SRC_URI` variable, and the `do_patch` task automatically applies them.

