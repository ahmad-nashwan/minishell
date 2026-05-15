#Changes Report

##Summary

			Fixed the `cd` (change directory)builtin command that was not functioning.The original implementation only printed paths instead of actually changing the directory.Two separate tasks were completed :

		1. *
		*Generated `get_env_value` function
			* *-utility to retrieve environment variables 2.
			* *Fixed `cd` builtin command *
		*-to actually change the directory

			-- -

	##Task 1 : Generated `get_env_value` Function

				## #Files Modified

				- `inc / minishell.h` - `src / utils /
					shell_utils.c`

					## #What Was Added

					####In `inc
					/
					minishell.h` (Helpers section)
	:

```c char * get_env_value(char **env_vars, const char *key);
```

		**Location : **Added to function declarations in the Helpers section

						####In `src /
						utils /
						shell_utils.c`:

```c char *get_env_value(char **env_vars, const char *key)
{
	size_t	key_len;
	int		i;

	if (!env_vars || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env_vars[i])
	{
		if (ft_strncmp(env_vars[i], key, key_len) == 0
			&& env_vars[i][key_len] == '=')
			return (env_vars[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
```

**Location:** Added after the `free_env()` function

### Logic Behind It

- **Purpose:** Search through the environment variable array and return the value for a given key
- **Parameters:**
 
	- `char **env_vars`: pointer to environment variable array (format: "KEY=VALUE")
  - `const char *key`: the environment variable name to find
- **Process:**
  1. Validate inputs (check for NULL pointers)
  2. Calculate key length using `ft_strlen()`
  3. Iterate through env_vars array
  4. For each entry, compare the variable name using `ft_strncmp()`
  5. Check if the character after the key is '=' (ensuring exact match)
  6. If found, return pointer to value (everything after the '=')
  7. If not found, return NULL
- **Use Case:** Used to retrieve HOME, PATH,
	and other environment variables during shell operations

---

## Task 2: Fixed `cd` Builtin Command

### Files Modified

- `inc/minishell.h`
- `src/builtins/builtins.c`
- `src/execution/excute.c`

### What Was Removed

#### From `src/builtins/builtins.c`:

**Old broken implementation:**

```c
void	cd(t_shell shell)
{
	char	*home;
	char	*target;

	home = NULL;
	target = NULL;
	if (!shell.env_vars)
		return ;
	home = get_env_value(shell.env_vars, "HOME");
	if (!home)
	{
		report_error(&shell, ERR, "cd: HOME not set");
		return ;
	}
	target = get_env_value(shell.env_vars, "CDPATH");
	if (target)
		ft_putendl_fd(target, STDOUT_FILENO);
	else
		ft_putendl_fd(home, STDOUT_FILENO);
}
```

**Problems with old implementation:**

1. ❌ Function signature took `t_shell shell` (by value) instead of `t_shell *shell` (by pointer)
2. ❌ No parameters for the target directory argument
3. ❌ Only printed paths to stdout instead of changing directory
4. ❌ Retrieved CDPATH instead of using command argument
5. ❌ Didn't use `chdir()` system call
6. ❌ Didn't update `shell->cwd`
7. ❌ Returned `void` instead of `t_code` status

### What Was Added

#### In `inc/minishell.h` (Built-in functions section):

```c
t_code	cd(t_shell *shell, char **args);
```

		**Location : **Added after `shell_exit` declaration

						####In `src /
						builtins /
						builtins.c`:

```c t_code cd(t_shell *shell, char **args)
{
	char	*target;
	char	*home;

	target = NULL;
	home = NULL;
	if (!shell || !shell->env_vars)
		return (INTERNAL_ERROR);
	// If an argument is provided, use it; otherwise use HOME
	if (args && args[1])
		target = args[1];
	else
	{
		home = get_env_value(shell->env_vars, "HOME");
		if (!home)
		{
			report_error(shell, ERR, "cd: HOME not set");
			return (BUILTIN_ERROR);
		}
		target = home;
	}
	// Change directory
	if (chdir(target) == -1)
	{
		report_error(shell, ERR, target);
		return (BUILTIN_ERROR);
	}
	// Update shell.cwd with the new directory
	if (shell->cwd)
		free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	return (OK);
}
```

	####In `src /
	execution /
	excute.c` (`run_builtin` function)
	:

		**Added `cd` case : **

```c else if (ft_strncmp(name, "cd", 3) == 0) cd(shell, argv);
```

**Location:** Added between echo and exit cases in the if-else chain

### Logic Behind It

#### Function Signature Changes:

- **Old:** `void cd(t_shell shell)`
- **New:** `t_code cd(t_shell *shell, char **args)`
- **Why:**
  - Pointer allows modifications to shell state (cwd) to persist
  - `t_code` return type allows error reporting
  - `char **args` provides the target directory from command arguments

#### Implementation Flow:

1. **Validation:**
   - Check if shell pointer is valid
   - Check if env_vars exist
   - Return INTERNAL_ERROR if not

2. **Determine Target Directory:**
   - If `args[1]` exists (user provided a path), use it
   - Otherwise, get HOME from environment variables
   - If HOME not found, report error and return BUILTIN_ERROR

3. **Change Directory:**
   - Call `chdir(target)` to actually change the directory
   - If fails (returns -1), report error and return BUILTIN_ERROR
   - chdir() is the POSIX system call that does the actual work

4. **Update Shell State:**
   - Free old `shell->cwd` if it exists (prevent memory leak)
   - Get new current working directory using `getcwd(NULL, 0)`
   - This allocates memory and returns absolute path of new directory

5. **Return Status:**
   - Return OK on success
   - Return BUILTIN_ERROR on failure

#### Integration with Execution Flow:

- Added `cd` case to `run_builtin()` so it's properly called during command execution
- The function is already detected as a builtin by `is_builtin()` function

### Behavior After Fix

**Example Usage:**

```bash
cd /tmp              # Changes to /tmp directory
cd                   # Changes to HOME directory
cd /nonexistent      # Prints error and stays in current directory
pwd                  # Shows new directory (if cd was successful)
```

---

## System Calls Used

| System Call       | Purpose                                           |
| ----------------- | ------------------------------------------------- |
| `chdir(path)`     | Changes the current working directory             |
| `getcwd(NULL, 0)` | Gets current working directory (allocates memory) |

---

## Error Handling

| Error Case                 | Behavior                                             |
| -------------------------- | ---------------------------------------------------- |
| No shell pointer           | Returns INTERNAL_ERROR                               |
| No env_vars                | Returns INTERNAL_ERROR                               |
| No argument & HOME not set | Reports error,
	returns BUILTIN_ERROR                 |
| Invalid directory path     | Reports error,
	returns BUILTIN_ERROR                 |
| getcwd() fails             | shell->cwd may be NULL (should be handled elsewhere) |

---

## Memory Management

- **Allocated:** `shell->cwd` is allocated by `getcwd(NULL,
	0)` (returns dynamically allocated string)
- **Freed:** Old `shell->cwd` is freed before assigning new value (prevents memory leak)
- **Cleanup:** Should be freed in shell's cleanup routine when exiting

---

## Dependencies

- `chdir.h` / `unistd.h` - for `chdir()` function
- `stdlib.h` - for `getcwd()` function
- `get_env_value()` - helper function to retrieve environment variables
- `report_error()` - error reporting function

---

## Testing Recommendations

1. Test changing to existing directory: `cd /tmp`
2. Test changing to home: `cd` (with HOME set)
3. Test with non-existent path: `cd /nonexistent123`
4. Test pwd after cd: `cd /tmp && pwd` (should show /tmp)
5. Test cd without HOME set (edge case)
6. Test relative paths: `cd ..`, `cd ./subdir`
