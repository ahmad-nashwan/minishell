# Export Function Report

## Overview

The `export` function is a builtin command that allows users to add or update environment variables in the shell. It ensures environment variables are stored in the correct `NAME=VALUE` format and properly managed in memory.

---

## File Location

- **Implementation:** `src/builtins/builtins.c`
- **Declaration:** `inc/minishell.h`

---

## Function Signature

```c
t_code export(t_shell *shell, char **args)
```

### Parameters

- **`t_shell *shell`:** Pointer to the shell structure containing environment variables
  - `shell->env_vars`: Array of environment variable strings (format: "KEY=VALUE")
- **`char **args`:\*\* Command arguments array
  - `args[0]`: Command name ("export")
  - `args[1]..args[n]`: Variables to export (format: "KEY=VALUE")

### Return Value

- **`OK`** (0): All variables exported successfully
- **`BUILTIN_ERROR`** (11): Invalid argument format (missing `=` sign)
- **`INTERNAL_ERROR`** (7): Memory allocation failed

---

## Logic Flow Diagram

```
export MY_VAR=value
    |
    v
Initialize: i = 1
    |
    v
Loop through args[i] (each variable)
    |
    +---> Find '=' sign in argument
    |        |
    |        +---> No '=' found? ---> Report error & return BUILTIN_ERROR
    |        |
    |        +---> '=' found? Continue
    |
    +---> Extract variable name (substring before '=')
    |
    +---> Extract variable value (substring after '=')
    |
    +---> Validate memory allocation
    |
    +---> Check if variable already exists in env_vars
    |
    +---> YES: Update existing variable
    |        |
    |        +---> Find matching entry (name + "=")
    |        +---> Free old entry
    |        +---> Create new entry: name + "=" + value
    |        +---> Replace in env_vars array
    |
    +---> NO: Add new variable
    |        |
    |        +---> Count current env variables
    |        +---> Allocate new array (env_count + 2)
    |        +---> Copy existing variables to new array
    |        +---> Create new entry: name + "=" + value
    |        +---> Add at end of array (before NULL terminator)
    |        +---> Replace old env_vars pointer
    |
    +---> Free temporary strings
    |
    +---> Move to next argument
    |
    v
Return OK
```

---

## Detailed Implementation

### 1. Argument Parsing

```c
char *arg = args[i];
char *equal_sign = ft_strchr(arg, '=');
```

**Purpose:** Find the `=` sign in the argument

- Uses `ft_strchr()` to locate `=` character
- If not found, it's an invalid argument format
- **Error Check:** If no `=`, report error and return

**Example:**

- Input: `"MY_VAR=hello"` → `equal_sign` points to `=`
- Input: `"MY_VAR"` → `equal_sign` is NULL → Error

### 2. Extract Name and Value

```c
size_t name_len = equal_sign - arg;
char *name = ft_substr(arg, 0, name_len);
char *value = ft_strdup(equal_sign + 1);
```

**Purpose:** Split "NAME=VALUE" into name and value

**Process:**

- Calculate name length: pointer arithmetic (`equal_sign - arg`)
- Extract name: `ft_substr(arg, 0, name_len)`
  - Starts at position 0
  - Takes `name_len` characters
- Extract value: `ft_strdup(equal_sign + 1)`
  - Duplicates string starting after `=` character
  - Allocates new memory for the value

**Example:**

- Input: `"MY_VAR=hello"`
- `name_len`: 6 (length of "MY_VAR")
- `name`: `"MY_VAR"`
- `value`: `"hello"`

### 3. Memory Validation

```c
if (!name || !value)
{
    free(name);
    free(value);
    report_error(shell, INTERNAL_ERROR, "export: memory allocation failed");
    return INTERNAL_ERROR;
}
```

**Purpose:** Ensure memory allocation succeeded

- Checks if `ft_substr()` or `ft_strdup()` failed
- Cleans up partial allocations
- Prevents segmentation faults

### 4. Check if Variable Exists

```c
char *existing_value = get_env_value(shell->env_vars, name);
if (existing_value)
{
    // Update existing variable
}
else
{
    // Add new variable
}
```

**Purpose:** Determine if we're updating or adding

- Uses helper function `get_env_value()` to search env_vars
- Returns pointer to value if found, NULL otherwise

---

## Update Path (Variable Already Exists)

```c
size_t existing_index = 0;
while (shell->env_vars[existing_index])
{
    if (ft_strncmp(shell->env_vars[existing_index], name, name_len) == 0
        && shell->env_vars[existing_index][name_len] == '=')
    {
        free(shell->env_vars[existing_index]);
        char *temp = ft_strjoin(name, "=");
        char *temp1 = ft_strjoin(temp, value);
        shell->env_vars[existing_index] = ft_strdup(temp1);
        free(temp1);
        free(temp);
        break;
    }
    existing_index++;
}
```

### Step-by-Step:

1. **Find the exact match:**
   - Compare variable name using `ft_strncmp()`
   - Check that character after name is `=` (ensures exact match)
   - Example: "MY_VAR=" matches, but "MY_VAR_2=" doesn't

2. **Free old entry:**
   - `free(shell->env_vars[existing_index])` releases old string memory

3. **Build new entry:**
   - `ft_strjoin(name, "=")` → `"MY_VAR="`
   - `ft_strjoin(temp, value)` → `"MY_VAR=hello"`
   - `ft_strdup(temp1)` → allocates new string for storage

4. **Clean up temporaries:**
   - `free(temp1)` - free result from second join
   - `free(temp)` - free result from first join
   - Original strings (name, value) freed later at end of loop

5. **Break loop:**
   - Exit after finding and updating the variable

### Memory Flow (Update):

```
OLD:  "MY_VAR=oldvalue"  (in array)
      |
      free()
      |
NEW:  "MY_VAR=hello"     (allocated by strdup)
      |
      stored in array

temp1 = "MY_VAR=hello"  (from strjoin) --> freed
temp = "MY_VAR="        (from strjoin) --> freed
```

---

## Add Path (New Variable)

```c
size_t env_count = 0;
while (shell->env_vars && shell->env_vars[env_count])
    env_count++;
```

### Step 1: Count existing variables

- Iterate through env_vars array until NULL terminator
- `env_count` = number of existing variables

**Example:**

```
env_vars = ["PATH=/usr/bin", "HOME=/root", NULL]
env_count = 2
```

### Step 2: Allocate new array

```c
char **new_env = malloc(sizeof(char *) * (env_count + 2));
```

**Why +2?**

- +1 for the new variable
- +1 for the NULL terminator

**Memory:**

```
new_env pointer array:
[0] --------
[1] --------
[2] -------- (new variable)
[3] NULL    (terminator)
```

### Step 3: Copy existing variables

```c
for (size_t j = 0; j < env_count; j++)
    new_env[j] = shell->env_vars[j];
```

**Purpose:** Transfer pointers to existing variables

- Does NOT duplicate strings
- Just copies the pointers
- Existing strings remain in memory

### Step 4: Create and add new variable

```c
char *temp = ft_strjoin(name, "=");
char *temp1 = ft_strjoin(temp, value);
new_env[env_count] = ft_strdup(temp1);
new_env[env_count + 1] = NULL;
```

**Process:**

1. `temp = "MY_VAR="`
2. `temp1 = "MY_VAR=hello"`
3. `new_env[env_count] = strdup(temp1)` - allocates new string
4. `new_env[env_count + 1] = NULL` - adds terminator

### Step 5: Replace env_vars

```c
free(temp);
free(temp1);
free(shell->env_vars);
shell->env_vars = new_env;
```

**Important:**

- Free temporary joined strings (not needed anymore)
- Free OLD array pointer (shell->env_vars)
- Individual variable strings are NOT freed (still in use)
- Replace with new array

### Memory Flow (Add):

```
OLD array:
["PATH=/usr/bin", "HOME=/root", NULL]
       |
       free()  <-- only frees array structure, not strings

NEW array:
["PATH=/usr/bin", "HOME=/root", "MY_VAR=hello", NULL]
       |
       stored in shell->env_vars

temp1 = "MY_VAR=hello"    (from strjoin) --> freed
temp = "MY_VAR="          (from strjoin) --> freed
```

---

## Key Bug Fix

### The Problem

**Previous implementation:**

```c
new_env[env_count] = ft_strjoin(name, value);  // WRONG!
```

**Result:** `"MY_VARhello"` (missing `=` sign)

### The Solution

```c
char *temp = ft_strjoin(name, "=");      // "MY_VAR="
char *temp1 = ft_strjoin(temp, value);   // "MY_VAR=hello"
new_env[env_count] = ft_strdup(temp1);   // Store in array
free(temp);   // Clean up intermediate string
free(temp1);  // Clean up intermediate string
```

**Result:** `"MY_VAR=hello"` (correct format)

---

## Error Handling

| Error Condition                         | Error Code       | Message                            | Action                        |
| --------------------------------------- | ---------------- | ---------------------------------- | ----------------------------- |
| No `=` in argument                      | `BUILTIN_ERROR`  | "export: invalid argument"         | Return error                  |
| Memory allocation fails (name/value)    | `INTERNAL_ERROR` | "export: memory allocation failed" | Free partials, return error   |
| Memory allocation fails (new_env array) | `INTERNAL_ERROR` | "export: memory allocation failed" | Free name/value, return error |

---

## Memory Management Summary

### Allocated Memory

| Memory             | Allocated By              | Freed By                                      |
| ------------------ | ------------------------- | --------------------------------------------- |
| `name`             | `ft_substr()`             | End of loop                                   |
| `value`            | `ft_strdup()`             | End of loop                                   |
| `temp`             | `ft_strjoin(name, "=")`   | Line after strdup or cleanup                  |
| `temp1`            | `ft_strjoin(temp, value)` | Line after strdup or cleanup                  |
| New variable entry | `ft_strdup(temp1)`        | During shell cleanup or next export           |
| `new_env` array    | `malloc()`                | When replaced by next export or shell cleanup |

### Critical: What's NOT Freed

- ✅ Existing env_vars strings (still in use in new array)
- ✅ Variable strings in environment (needed by shell)

### Critical: What IS Freed

- ✅ Temporary joined strings (`temp`, `temp1`)
- ✅ Old array structure (when replaced with new array)
- ✅ Name and value extracts (at end of each loop iteration)

---

## Usage Examples

### Example 1: Add new variable

```bash
export MY_VAR=hello
```

- Creates new entry in env_vars: `"MY_VAR=hello"`
- Allocates new array to accommodate it
- Increments total variable count

### Example 2: Update existing variable

```bash
export PATH=/custom/bin
```

- Finds existing "PATH=" entry
- Frees old value
- Replaces with new: `"PATH=/custom/bin"`
- Array size unchanged

### Example 3: Multiple variables in one command

```bash
export VAR1=value1 VAR2=value2
```

- Loops through each argument
- Processes VAR1, then VAR2
- Each iteration may allocate new array or update entry

### Example 4: Invalid argument (no `=`)

```bash
export MY_VAR
```

- No `=` found in argument
- Reports error: "export: invalid argument"
- Returns BUILTIN_ERROR
- Does not modify env_vars

---

## Dependencies

### Libft Functions Used

| Function       | Purpose                                        |
| -------------- | ---------------------------------------------- |
| `ft_strchr()`  | Find `=` character in argument                 |
| `ft_substr()`  | Extract variable name                          |
| `ft_strdup()`  | Duplicate variable value and formatted strings |
| `ft_strjoin()` | Concatenate strings (name + "=" + value)       |
| `ft_strncmp()` | Compare variable names                         |

### System Functions Used

| Function   | Purpose                                        |
| ---------- | ---------------------------------------------- |
| `malloc()` | Allocate memory for new env array              |
| `free()`   | Release memory for old entries and temporaries |

### Helper Functions

| Function          | Purpose                          |
| ----------------- | -------------------------------- |
| `get_env_value()` | Check if variable already exists |
| `report_error()`  | Report error messages to user    |

---

## Integration Points

### Called From

- [src/execution/excute.c](src/execution/excute.c) - `run_builtin()` function
- Detected by `is_builtin()` as a builtin command

### Modifies

- `shell->env_vars` - adds or updates environment variables

### Used By

- Other builtins and commands that need environment variables
- Expansion functions that resolve `$VARIABLE` references

---

## Testing Recommendations

### Functional Tests

1. ✅ Add new variable: `export TEST=value`
2. ✅ Update existing: `export PATH=/new/path`
3. ✅ Check format: `env` (should show `TEST=value`, not `TESTvalue`)
4. ✅ Multiple variables: `export A=1 B=2 C=3`
5. ✅ Special characters: `export PATH=/path:with:colons`
6. ✅ Empty value: `export EMPTY=`
7. ✅ Invalid format: `export NOEQUAL` (should error)

### Memory Tests

- Monitor memory usage before/after exports
- Check for memory leaks with valgrind
- Export many variables to test array reallocation

### Edge Cases

- Export variable with same name multiple times in one command
- Export with no arguments (should probably list exported variables)
- Very long variable names/values
- Variables with special characters
- Update and add in same command

---

## Performance Considerations

### Time Complexity

- **For each export command:** O(n × m)
  - n = number of arguments
  - m = number of existing environment variables
- **Searching for existing:** O(m) - linear search through all variables

### Space Complexity

- **Adding new variable:** Allocates (env_count + 2) _ sizeof(char_)
- **Updating existing:** No additional array allocation

### Optimization Opportunities

- Hash table for faster variable lookup (currently O(m))
- Avoid reallocation if array is pre-allocated with extra capacity
- Cache environment variable count instead of recounting each time
