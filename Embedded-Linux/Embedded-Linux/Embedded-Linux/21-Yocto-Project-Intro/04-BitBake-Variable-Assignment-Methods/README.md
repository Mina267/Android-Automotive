# BitBake Variable Assignment Methods

In BitBake, there are several methods to assign values to variables, each with its own behavior:

1. **Normal Assignment (`=`):**
   ```plaintext
   MYVAR = "5"
   ```
   - Directly assigns the value "5" to `MYVAR`. This is the standard way of setting a variable.

2. **Weak Assignment (`?=`):**
   ```plaintext
   MYVAR = "3"
   MYVAR ?= "4"
   ```
   - The weak assignment (`?=`) only assigns the value if the variable is not already set. In this case, `MYVAR` is already set to "3", so the `?=` assignment does not change it. If `MYVAR` was not set before, it would have been assigned "4".

3. **Weak Weak Assignment (`??=`):**
   ```plaintext
   MYVAR ??= "4"
   MYVAR ??= "3"
   ```
   - This works similarly to weak assignment but will only set the variable if it has not been assigned before any weak assignment. Here, `MYVAR` will be set to "4" if it wasn't set before, otherwise it will retain the value from the weak assignment. The second weak weak assignment does not change the value if it was set already.

4. **Appending (`+=` and `:append`):**
   ```plaintext
   MYVAR = "4"
   MYVAR += "5"
   MYVAR:append = "6"
   ```
   - `+=` adds a space before appending "5" to `MYVAR`, resulting in "4 5".
   - `:append` directly appends "6" without a space, resulting in "45" if `MYVAR` was "4".
   - If you use `+=` and `:append` together, like:
     ```plaintext
     MYVAR += "5"
     MYVAR:append = "6"
     ```
     The result will be "56 4" since `+=` adds "5" with a space and `:append` adds "6" directly.

5. **Prepend (`prepend:`):**
   ```plaintext
   MYVAR = "5"
   MYVAR = prepend:"4"
   ```
   - Adds "4" before the existing value of `MYVAR`, resulting in "45".

6. **Immediate Assignment (`:=`):**
   ```plaintext
   XAR = "3"
   MYVAR := "${XAR}"
   XAR = "4"
   ```
   - `:=` assigns the value of `XAR` to `MYVAR` immediately when the assignment is processed, so `MYVAR` will end up with "3" because `XAR` was "3" at the time of assignment.
   - If you use `:=` with changing values:
     ```plaintext
     MYVAR := "${XAR}"
     XAR = "4"
     XAR = "5"
     ```
     `MYVAR` will be "4" because the assignment was immediate and took the value when `XAR` was "4".

7. **Dot Append (`.`):**
   ```plaintext
   MYVAR ?= "5"
   MYVAR .= "6"
   ```
   - Similar to `:append`, but uses a dot. It does not add a space before appending. It is used for appending strings without spaces.

8. **Remove (`:remove`):**
   ```plaintext
   MYVAR = "4 5 6"
   MYVAR:remove = "5"
   ```
   - Removes "5" from `MYVAR`, resulting in "4 6".

## Local Variables in Recipes

In a BitBake recipe, variables such as `S`, `B`, and `D` are local variables that specify paths for various stages:

- `S`: Source directory path.
- `B`: Build directory path.
- `D`: Destination (install) directory path.

These variables are used within the recipe to define where different build steps occur.

## Summary

Understanding these variable assignment methods and their effects helps in controlling how and when values are set or modified in BitBake recipes. This knowledge is crucial for managing complex builds and ensuring that the correct values are used at each stage of the build process.