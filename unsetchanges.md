# Unset Command Report

## Overview

The `unset` command is a bash builtin that removes environment variables from the shell's environment array. It allows users to delete one or more variables from the shell session.

---

## Files Modified/Created

### Modified Files

1. **`inc/minishell.h`** - Added function declaration
2. **`src/execution/excute.c`** - Added unset case to `run_builtin()`

### New Files Created

1. **`src/builtins/unset.c`** - Implementation file

---

## Function Signature

```c
t_code unset(t_shell *shell, char **args)
```

### Parameters

- **`t_shell *shell`:** Pointer to the shell structure containing environment variables
  - `shell->env_vars`: Array of environment variable strings (format: "KEY=VALUE")
- **`char **args`:\*\* Command arguments array
  - `args[0]`: Command name ("unset")
  - `args[1]..args[n]`: Variable names to unset (format: "VAR_NAME")

### Return Value

- **`OK`** (0): Always returns OK (unset succeeds even if variable doesn't exist)

---

## What Was Added

### 1. Header Declaration (inc/minishell.h)

```c
t_code      unset(t_shell *shell, char **args);
```

**Location:** Added after `export` declaration in Built-in functions section

### 2. Run Builtin Integration (src/execution/excute.c)

```c
else if (ft_strncmp(name, "unset", 6) == 0)
    unset(shell, argv);
```

**Location:** Added between export and exit cases in `run_builtin()` function

### 3. New Implementation File (src/builtins/unset.c)

```c
#include "../../inc/minishell.h"

t_code unset(t_shell *shell, char **args)
{
	int		i;
	int		j;
	size_t	name_len;
	size_t	env_count;

	if (!shell || !shell->env_vars || !args)
		return (OK);
	i = 1;
	while (args && args[i])
	{
		name_len = ft_strlen(args[i]);
		j = 0;
		while (shell->env_vars[j])
		{
			if (ft_strncmp(shell->env_vars[j], args[i], name_len) == 0
				&& shell->env_vars[j][name_len] == '=')
			{
				free(shell->env_vars[j]);
				env_count = j;
				while (shell->env_vars[env_count])
				{
					shell->env_vars[env_count] = shell->env_vars[env_count + 1];
					env_count++;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (OK);
}
```

---

## Logic Flow Diagram

```
unset VAR1 VAR2 VAR3
    |
    v
Validate inputs (shell, env_vars, args)
    |
    v
Initialize: i = 1
    |
    v
Loop through args[i] (each variable name to unset)
    |
    +---> Get variable name length
    |
    +---> Initialize: j = 0
    |
    +---> Search through env_vars array
    |        |
    |        +---> Compare env_vars[j] with variable name
    |        |
    |        +---> Check if format matches "NAME="
    |        |
    |        +---> YES: Found the variable
    |        |        |
    |        |        +---> Free memory of env_vars[j]
    |        |        |
    |        |        +---> Shift all following elements up
    |        |        |        |
    |        |        |        +---> env_vars[j] = env_vars[j+1]
    |        |        |        +---> env_vars[j+1] = env_vars[j+2]
    |        |        |        +---> ... (until NULL)
    |        |        |
    |        |        +---> Break inner loop
    |        |
    |        +---> NO: Move to next variable
    |        |
    |        +---> End of array? (NULL found)
    |
    +---> Move to next argument
    |
    v
Return OK
```

---

## Detailed Implementation

### Step 1: Input Validation

```c
if (!shell || !shell->env_vars || !args)
    return (OK);
```

**Purpose:** Check for NULL pointers

- If any critical pointer is NULL, return OK without doing anything
- This is safe behavior - nothing to unset if no environment exists

### Step 2: Initialize Loop Variables

```c
i = 1;
while (args && args[i])
{
    name_len = ft_strlen(args[i]);
    j = 0;
```

**Purpose:** Set up to process each variable name

- `i = 1`: Skip command name (args[0])
- `name_len`: Calculate length of current variable name to search
- `j = 0`: Reset search index for each new variable

**Example:**

```
args = ["unset", "PATH", "HOME", "VAR"]
         [0]      [1]     [2]     [3]

i = 1 → Process "PATH"    (name_len = 4)
i = 2 → Process "HOME"    (name_len = 4)
i = 3 → Process "VAR"     (name_len = 3)
```

### Step 3: Search for Variable in Environment

```c
while (shell->env_vars[j])
{
    if (ft_strncmp(shell->env_vars[j], args[i], name_len) == 0
        && shell->env_vars[j][name_len] == '=')
    {
        // Found it - proceed to removal
    }
    j++;
}
```

**Purpose:** Find the matching environment variable

- Compare first `name_len` characters of env_vars[j] with variable name
- Check that the character at position `name_len` is `=`
- This ensures exact match and correct format

**Example Search:**

```
Looking for: "PATH" (name_len = 4)

env_vars = [
    "PATH=/usr/bin",      <- Match! (0 == 0) && ('=' == '=')
    "HOME=/root",
    "USER=root",
    NULL
]
```

### Step 4: Remove Variable from Array

```c
free(shell->env_vars[j]);
env_count = j;
while (shell->env_vars[env_count])
{
    shell->env_vars[env_count] = shell->env_vars[env_count + 1];
    env_count++;
}
break;
```

**Purpose:** Delete the variable and compact the array

#### Substep 4.1: Free Memory

```c
free(shell->env_vars[j]);
```

- Release the allocated memory for this environment variable string
- Example: frees the string "PATH=/usr/bin"

#### Substep 4.2: Shift Elements Up

```c
env_count = j;
while (shell->env_vars[env_count])
{
    shell->env_vars[env_count] = shell->env_vars[env_count + 1];
    env_count++;
}
```

**Visual representation:**

```
BEFORE unset PATH:
[0] = "PATH=/usr/bin"
[1] = "HOME=/root"
[2] = "USER=root"
[3] = NULL

FREE [0], then shift:

AFTER:
[0] = "HOME=/root"    (was [1])
[1] = "USER=root"     (was [2])
[2] = NULL            (was [3])
```

**Process:**

- `env_vars[j] = env_vars[j+1]` moves the next element to current position
- Continue until NULL is copied
- This effectively removes the element and compacts the array

#### Substep 4.3: Break Loop

```c
break;
```

- Exit the inner search loop after finding and removing variable
- Continue to next variable name in outer loop

### Step 5: Move to Next Variable

```c
i++;
```

- Increment to process next variable name
- If multiple variables: `unset PATH HOME USER`
  - First removes PATH
  - Then removes HOME (from updated array)
  - Then removes USER (from updated array)

### Step 6: Return Status

```c
return (OK);
```

- Always returns OK (success code)
- Even if variable didn't exist, return OK

---

## Key Design Decisions

### Why Always Return OK?

Unlike bash, which also returns 0 even if variable doesn't exist:

- Attempting to unset non-existent variables is not an error
- This is POSIX-compliant behavior
- Simplifies shell usage

### Why In-Place Array Modification?

Instead of creating new array like `export` does:

- **Advantage:** No reallocation needed
- **Advantage:** All references stay valid
- **Advantage:** More efficient for single removals
- **Trade-off:** Array gaps would form with multiple removals (but we shift)

### Why Search Every Time?

Linear search through environment variables:

- **Pro:** Simple to implement
- **Pro:** No extra data structures needed
- **Con:** O(n) time complexity for each variable
- **Alternative:** Could use hash table for O(1) lookup

---

## Memory Management

### What Gets Freed

| Memory                     | When                | Why                       |
| -------------------------- | ------------------- | ------------------------- |
| `env_vars[j]` (the string) | When variable found | Variable is being removed |

### What Doesn't Get Freed

| Memory                       | Why                                |
| ---------------------------- | ---------------------------------- |
| Array structure (`env_vars`) | Still in use, just compacted       |
| Other variable strings       | Still in environment, just shifted |

### Memory Leak Prevention

- ✅ Free exact variable being removed
- ✅ Don't free the array itself (still need it)
- ✅ Proper pointer shifting prevents dangling references

---

## Error Handling

| Situation                        | Behavior                             |
| -------------------------------- | ------------------------------------ |
| NULL shell pointer               | Return OK (do nothing)               |
| NULL env_vars                    | Return OK (do nothing)               |
| NULL args                        | Return OK (do nothing)               |
| Variable doesn't exist           | Return OK (no error)                 |
| Multiple removals in one command | Each variable processed individually |

**Philosophy:** `unset` is permissive - it doesn't fail even if nothing matches

---

## Usage Examples

### Example 1: Unset single variable

```bash
export MY_VAR=hello
unset MY_VAR
# MY_VAR is removed from environment
```

### Example 2: Unset multiple variables

```bash
export A=1 B=2 C=3
unset A B C
# All three variables removed
```

### Example 3: Unset non-existent variable

```bash
unset NONEXISTENT_VAR
# No error, just succeeds
```

### Example 4: Partial unset

```bash
export PATH=/custom HOME=/root USER=testuser
unset HOME
# Only HOME removed, PATH and USER remain
```

### Example 5: Unset with environment variables

```bash
export VAR1=value1 VAR2=value2
unset VAR1
env
# Shows VAR2=value2 (VAR1 removed)
```

---

## Integration with Shell

### Execution Flow

1. User types: `unset MY_VAR`
2. `tokenizer` → Breaks into tokens
3. `parser` → Creates command structure
4. `excute_cmds()` → Detects it's a builtin
5. `is_builtin()` → Confirms "unset" is builtin
6. `run_builtin()` → Calls `unset(shell, argv)`
7. `unset()` → Removes variable from `shell->env_vars`
8. Returns to shell prompt

### Called From

- [src/execution/excute.c](src/execution/excute.c) - `run_builtin()` function

### Detection

- Already registered in `is_builtin()` function
- Checks with: `ft_strncmp(name, "unset", 6) == 0`

---

## Dependencies

### Libft Functions Used

| Function       | Purpose                            |
| -------------- | ---------------------------------- |
| `ft_strlen()`  | Get length of variable name        |
| `ft_strncmp()` | Compare strings up to n characters |

### System Functions

| Function | Purpose                           |
| -------- | --------------------------------- |
| `free()` | Release memory of variable string |

### Helper Functions

| Function         | Purpose                                           |
| ---------------- | ------------------------------------------------- |
| `report_error()` | Would report errors (not currently used in unset) |

---

## Time and Space Complexity

### Time Complexity

- **Per variable:** O(m) where m = number of environment variables
- **All variables:** O(n × m) where n = number of variables to unset
- **Array shifting:** O(m) for each removal

### Space Complexity

- **O(1)** - No extra space allocated (in-place modification)

### Worst Case Scenario

- Unset first variable in environment with 1000 variables
- Must shift 999 elements up
- Time: O(m) where m = 1000

---

## Comparison with `export`

| Aspect               | Export                    | Unset                  |
| -------------------- | ------------------------- | ---------------------- |
| Array reallocation   | YES (allocates new array) | NO (modifies in-place) |
| Memory efficiency    | Lower                     | Higher                 |
| String concatenation | Needs "=" joining         | Just comparison        |
| Complexity           | O(n × m) + allocations    | O(n × m) shifts only   |
| Error handling       | Can report errors         | Always returns OK      |

---

## Testing Recommendations

### Functional Tests

1. ✅ Unset existing variable: `export TEST=1; unset TEST; env`
2. ✅ Unset non-existent variable: `unset NOTHERE`
3. ✅ Unset multiple: `unset VAR1 VAR2 VAR3`
4. ✅ Verify removal: `export X=1; unset X; echo $X` (should be empty)
5. ✅ Check array integrity: After unset, other variables accessible
6. ✅ Unset with special names: `unset PATH HOME USER`
7. ✅ Multiple unserts in sequence: `unset A; unset B; unset C`

### Edge Cases

- Unset first variable in array
- Unset last variable in array
- Unset middle variable in array
- Unset with empty arguments
- Unset variable that partially matches others

### Memory Tests

- Monitor memory with valgrind
- Verify no dangling pointers
- Check array structure integrity after removals

### Integration Tests

- After unset, exported variables should not be visible
- After unset, environment reflects changes
- Unset + export cycle works correctly

---

## Potential Improvements

### 1. Error Reporting

Currently unset always succeeds. Could enhance to:

```c
if (variable_not_found)
    report_error(shell, BUILTIN_ERROR, "unset: variable not found");
```

### 2. Performance Optimization

Use hash table for variable lookup:

```c
// Current: O(n) linear search
// Optimized: O(1) hash lookup
```

### 3. Protected Variables

Prevent unsetting critical variables like PATH:

```c
if (ft_strncmp(args[i], "PATH", 4) == 0)
{
    report_error(shell, BUILTIN_ERROR, "unset: cannot unset PATH");
    continue;
}
```

### 4. Return Value Consistency

Match bash behavior more closely:

```c
// Return BUILTIN_ERROR if any variable not found
// Currently: always returns OK
```

---

## POSIX Compliance

### Bash Documentation Reference

```
unset: unset [-f] [-v] [name ...]
  Unset values and attributes of shell variables and functions.
  ...
  Exit Status:
  Returns success unless an invalid option is given or a readonly
  variable or function is attempted to be unset.
```

### Implementation Status

- ✅ Basic functionality: Removes variables from environment
- ⚠️ No `-f` flag (function removal)
- ⚠️ No `-v` flag (variable mode)
- ⚠️ No readonly variable protection
- ⚠️ Always returns success (even when variable doesn't exist)

---

## Summary

The `unset` command implementation:

- ✅ Successfully removes environment variables
- ✅ Handles multiple variables in one command
- ✅ Properly manages memory (frees removed variables)
- ✅ Maintains array integrity (shifts elements to compact)
- ✅ Integrated with shell execution flow
- ✅ Follows POSIX behavior of returning success always
- ⚠️ Could be enhanced with error reporting and protected variables
- ⚠️ Linear search could be optimized with hash table

**Status:** Ready for production use in basic shell operations
