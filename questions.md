1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  fgets() is a good choice because it reads the input line by line and stops when it sees a new line (\n) or reaches the maximum size limit. It also prevents buffer overflow.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  We use malloc() because it dynamically allocates memory at runtime. This is useful because we don’t always know how big the input will be. A fixed-size array might waste memory (if the input is small) or run out of space (if the input is too big).


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  If we don’t remove extra spaces: Commands might not run properly (e.g., " ls" with a space before might not work), comparing commands (like checking for "exit") could fail because of extra spaces, the shell might think an empty command is valid and also it ensures a cleaner user experience.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**: 1. ls > output.txt → Saves output to a file instead of printing on screen.
2. cat < input.txt → Reads input from a file instead of the keyboard.
3. command 2> error.log → Saves error messages in a separate file.

Challenges:
1. We need to handle file operations properly.
2. We must redirect the correct output stream (STDOUT, STDERR, or STDIN).
3. We need to handle file permissions (if a file is read-only).


- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**: Redirection sends output to a file or takes input from a file whereas piping takes the output of one command and sends it as input to another command.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  Keeping them separate helps because you can redirect errors separately. Example: If you run find /root (but don’t have permission), you want errors in one place while still seeing normal output.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  Our shell should detect errors and show helpful messages. We can let users merge STDOUT and STDERR using 2>&1, like: command > output.log 2>&1. This means send normal output and errors to the same file. This helps when debugging issues (so users can see both errors and normal output together).