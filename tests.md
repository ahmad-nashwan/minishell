# Minishell Edge Cases

> Most cases should be tested in `valgrind` with `--trace-children` and `--track-fds` to check for leaks and open fds in child processes. There should be no unclosed inherited fds from parent in child.

```bash
valgrind --trace-children=yes --track-fds=yes ./minishell
```

> Use `ps aux` to check for zombie processes:

```bash
ps aux | grep Z
```

---

## Syntax

| Case        | Expected Output                                           | `$?` | Required |
| ----------- | --------------------------------------------------------- | ---- | -------- |
| [✅] `ls >` | `minishell: syntax error near unexpected token 'newline'` | 2    | ✅       |
| [✅] `>>>`  | `minishell: syntax error near unexpected token '>'`       | 2    | ✅       |
| [✅] `<<<`  | `minishell: syntax error near unexpected token '<'`       | 2    | ✅       |
| [✅] `\|`   | `minishell: syntax error near unexpected token 'newline'` | 2    | ✅       |
| [✅] `\|\|` | `minishell: syntax error near unexpected token '\|'`      | 2    | ✅       |
| [✅] `<<`   | `minishell: syntax error near unexpected token 'newline'` | 2    | ✅       |
| [✅] `>>`   | `minishell: syntax error near unexpected token 'newline'` | 2    | ✅       |

---

## Expander

| Case                                                                                            | Expected Output                | `$?` | Required |
| ----------------------------------------------------------------------------------------------- | ------------------------------ | ---- | -------- |
| [✅] `$non_exist $SHELL`                                                                        | `shell> `                      | 0    | ✅       |
| [✅] `export test="            "` then `echo $test $test $test abcd $non_exist $test 123 $test` | `abcd 123`                     | 0    | ✅       |
| [✅] `export test="      abcd     123 "` then `echo $test "$test"`                              | `abcd 123       abcd     123 ` | 0    | ✅       |
| [✅] `echo $0$1230$0`                                                                           | `minishell230minishell`        | 0    | ✅       |
| [✅] `export test="ls    -la"` then `$test`                                                     | `ls` with `-la` flag output    | 0    | ✅       |

---

## Env

| Case                                                             | Expected Output                                                    | `$?` | Required     |
| ---------------------------------------------------------------- | ------------------------------------------------------------------ | ---- | ------------ |
| [X] `echo $SHLVL` then `./minishell` then `echo $SHLVL`          | First echo outputs current shell level, second outputs `SHLVL + 1` | 0    | ⚠️ Debatable |
| [X] `export SHLVL=999` then `./minishell`                        | `minishell: warning: shell level (1000) too high, resetting to 1`  | 0    | ⚠️ Debatable |
| [O] `export SHLVL=-129139` then `./minishell` then `echo $SHLVL` | `0`                                                                | 0    | ⚠️ Debatable |
| [O] `ls -la` then `echo $_`                                      | `ls` output then `-la`                                             | 0    | ⚠️ Debatable |

---

## Export

| Case                                                     | Expected Output                                      | `$?` | Required |
| -------------------------------------------------------- | ---------------------------------------------------- | ---- | -------- |
| [✅] `export test1="abcd" test2="123" test3="minishell"` | Adds `test1`, `test2`, `test3` to envs               | 0    | ✅       |
| [✅] `export 1test`                                      | `minishell: export: '1test': not a valid identifier` | 1    | ✅       |
| [✅] `export test="123" 1test="test" test3="abcd"`       | Adds `test` and `test3` to envs, skips invalid       | 0    | ✅       |
| [✅] `export test_empty` then `bash` then `export`       | All envs except `test_empty`                         | 0    | ✅       |

---

## Pipes

| Case                                                                    | Expected Output                                  | `$?` | Required |
| ----------------------------------------------------------------------- | ------------------------------------------------ | ---- | -------- |
| [✅] `cat \| cat \| cat \| echo`                                        | ` ` (empty line)                                 | 0    | ✅       |
| [✅] `cat Makefile \| base64 \| xxd -p \| xxd -r -p \| base64 --decode` | Makefile contents                                | 0    | ✅       |
| [✅] `cat Makefile \| cat -e \| cat -e \| ... (10x)`                    | Makefile with `$$$$$$$$$$` appended to each line | 0    | ✅       |
| [✅] `yes yes \| head -n 10000000 \| wc`                                | `10000000 10000000 40000000`                     | 0    | ✅       |
| [X] `echo \| echo \| echo \| ... (13x)` then `./minishell`              | ` `                                              | 0    | ✅       |
| [O] `. \| .. \| .`                                                      | `minishell> `                                    | 0    | ✅       |
| [O] `exit 1 \| exit 255 \| exit 2`                                      | `minishell> `                                    | 2    | ✅       |

---

## Echo

| Case                                  | Expected Output                | `$?` | Required |
| ------------------------------------- | ------------------------------ | ---- | -------- |
| [✅] `echo -n test`                   | `testminishell> ` (no newline) | 0    | ✅       |
| [✅] `echo -nnnnnnn -n -nnnnnnb test` | `-nnnnnnb test`                | 0    | ✅       |
| [X] `echo -nnnnnnn -n -nnnennE test`  | `test`                         | 0    | ❌ No    |
| [✅] `echo test`                      | `test` + newline               | 0    | ✅       |

---

## Unset

| Case                   | Expected Output                    | `$?` | Required |
| ---------------------- | ---------------------------------- | ---- | -------- |
| [✅] `unset USER`      | Removes `USER` from env            | 0    | ✅       |
| [✅] `unset USER PATH` | Removes `USER` and `PATH` from env | 0    | ✅       |

---

## cd

| Case                   | Expected Output                            | `$?` | Required |
| ---------------------- | ------------------------------------------ | ---- | -------- |
| [✅] `cd test/`        | `minishell: cd: No such file or directory` | 1    | ✅       |
| [✅] `cd /dev/vboxusb` | `minishell: cd: Permission denied`         | 1    | ✅       |
| [✅] `cd ../../`       | `minishell> `                              | 0    | ✅       |
| [✅] `cd a b`          | `minishell: cd: too many arguments`        | 1    | ✅       |

---

## Exit

| Case                             | Expected Output                                                     | `$?` | Required |
| -------------------------------- | ------------------------------------------------------------------- | ---- | -------- |
| [✅] `exit -1`                   | `exit`                                                              | 255  | ✅       |
| [X] `exit 9223372036854775808-`  | `minishell: exit: 9223372036854775808- : numeric argument required` | 2    | ✅       |
| [✅] `exit -9223372036854775808` | `exit`                                                              | 0    | ✅       |
| [X] `exit 9223372036854775808`   | `minishell: exit: 9223372036854775808 : numeric argument required`  | 2    | ✅       |
| [✅] `exit 9223372036854775807`  | `exit`                                                              | 255  | ✅       |
| [✅] `exit 1 abcd`               | `minishell: exit: too many arguments`                               | 1    | ✅       |

---

## Signals

| Case                                                        | Expected Output     | `$?` | Required |
| ----------------------------------------------------------- | ------------------- | ---- | -------- |
| [✅] `sleep 1000 \| ls \| sleep 1000` then `Ctrl+C`         | `minishell> `       | 130  | ✅       |
| [✅] `sleep 1000 \| ls \| sleep 1000` then `Ctrl+\`         | `minishell> `       | 131  | ✅       |
| [O] `sleep 1 \| ls \| sleep 1000` — after 1s check `ps aux` | No zombie processes | 0    | ✅       |
| [✅] `Ctrl+C` (at prompt)                                   | `minishell> `       | 130  | ✅       |
| [✅] `Ctrl+\` (at prompt)                                   | `minishell> `       | 0    | ✅       |

---

## Error Handling

| Case                                                         | Expected Output                 | `$?` | Required |
| ------------------------------------------------------------ | ------------------------------- | ---- | -------- |
| [✅] `./`                                                    | `minishell: ./: Is a directory` | 126  | ✅       |
| [O] `.`                                                      | `minishell> `                   | …    | ✅       |
| [✅] `/`                                                     | `minishell: /: Is a directory`  | 126  | ✅       |
| [X] `file/`                                                  | `file/: Not a directory`        | 126  | ✅       |
| [O] `touch file_test` + `chmod +x file_test` + `./file_test` | Must not leak or leave open fds | …    | ✅       |

---

## Redirections

| Case                                            | Expected Output                                                                                   | `$?` | Required |
| ----------------------------------------------- | ------------------------------------------------------------------------------------------------- | ---- | -------- |
| [X] `in < in2 < in3 cat > out > out2 > out3`    | `cat` reads from `in3`, writes to `out3`                                                          | 0    | ✅       |
| [✅] `<< 123 cat << 234 -e > out`               | `cat` reads from `234` heredoc with `-e`, outputs to `out`                                        | …    | ✅       |
| [✅] `> /`                                      | `minishell: /: Is a directory`                                                                    | 1    | ✅       |
| [✅] `<< 123` then `Ctrl+C`                     | `minishell> `                                                                                     | 130  | ✅       |
| [O] `<< 123 cat` then type `1234` then `Ctrl+D` | `minishell: warning: here-document at line 1 delimited by end-of-file (wanted '123')` then `1234` | 0    | ✅       |
| [X] `export test="123 test"` then `< $test`     | `minishell: $test: ambiguous redirect`                                                            | 1    | ✅       |
| [X] `export test="123 test"` then `ls > $test`  | `minishell: $test: ambiguous redirect`                                                            | 1    | ✅       |

---

## Bonus

| Case                                                                                             | Expected Output                                                   | `$?` | Required |
| ------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------- | ---- | -------- |
| [ ] `test && echo hi \| sleep 10 \|\| echo nice`                                                 | `nice`                                                            | 0    | ✅       |
| [ ] `test && exit \|\| yes yes \| head -n 100 && cat` then `Ctrl+D`                              | 100 lines of `yes`                                                | 0    | ✅       |
| [ ] `test \|\| exit && echo hi`                                                                  | `exit`                                                            | 0    | ✅       |
| [ ] `(ls && pwd && ls -la)`                                                                      | `ls`, `pwd`, `ls -la` outputs                                     | 0    | ✅       |
| [ ] `in < (cat && ls && pwd && ls -la && (ls && test \|\| yes yes \| head -n 100) > out1) > out` | `minishell> `                                                     | 0    | ❌ No    |
| [ ] `************M*******a******k*****`                                                          | `Makefile: command not found`                                     | 127  | ✅       |
| [ ] `echo .*`                                                                                    | `. .. .git .gitignore .vscode`                                    | 0    | ✅       |
| [ ] `echo *`                                                                                     | `Include.mk Makefile build includes libft minishell out out1 src` | 0    | ✅       |
| [ ] `echo .*.`                                                                                   | `..`                                                              | 0    | ✅       |

---

Good luck with your minihell 🔥🔥🔥🔥🔥
