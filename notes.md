There are some notes:
1. In expansion, this case: $"var" prints: $var
This is because: The expander looks at the right character of the dollar sign to find it a quote
This is not a valid veriable name, therefore it prints the literal dollar sign
This behavior makes perfect sense, though we must make sure it's properly handled according to 42 standards


interesting stuff:
https://linuxize.com/post/linux-tee-command/ <= heredoc can be used with `tea`
another cool command: https://linuxize.com/posthow-to-use-sed-to-find-and-replace-string-in-files/

heredoc: https://linuxize.com/post/bash-heredoc/

what is a time matrix 

to do:
understand pipe man page[DONE]

we have a still reachable block of memory for the PIDs array in process_pipeline
the reason for that is we reach exit without freeing the PIDs array
the OS reclaims this memory as soon as we exit
consider freeing it in the future