*This project has been created as part of the 42 curriculum by **grui-ant** and **joapedro**.*

# $> 42-Minishell 🖥️

## A project most commonly known as "Mini Hell".

*If we're able to do this project, we can do anything.* Or so they say.

## Description

We made our own, actually usable, **Unix Shell**! And you can try it out yourself!
Fully written in **C**, this Unix Shell includes a lot of the features found on the **[Bourne Again SHell](https://www.gnu.org/software/bash/)**, which we used as our reference.

### Features:
- **Fully working history** of past commands (as of the start time of the program);
- Starting/running programs <ins>from the shell</ins>;
- **Basic redirections**: This includes `<`, `>`, `<<`, and `>>`;
- **Pipes**;
- **Environment variables**, as well as setting and unsetting new ones;
- Handling of signals via `CTRL-C`, `CTRL-D`;
- A handful of **built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`;
- <ins>Partially statically linked library</ins>: we use our own **C Library** for some functions, the **[42-Libft](https://git.the-wired.org/TreezZ/42-Libft)**.

## Instructions
### Building

You will need to compile this program yourself, as no binaries are provided.  
This project was was made with Ubuntu 22.04 as the target platform, so this guide will assume you are on Ubuntu.  
However, you should be able to install the equivalent packages and build on your distro of choice.

**Prequisites:**

Install the following <ins>dependencies</ins>:

WE STILL NEED TO CHECK THIS:

`sudo apt install clang gcc git libxext-dev libbsd-dev make xorg zlib1g-dev`

**Clone** this repository using **Git**, `cd` into it, and pull all dependencies:

`git clone https://github.com/42-Minishell-Spablob3-TreezZ-Project/42-Minishell.git`
`cd 42-Minishell && git submodule update --init --recursive`

Once that's done, run **GNU Make** to build the source code into a **executable binary**:

`make`

The `make clean` and `make fclean` flags are also available to **clean up** the files created during compilation, as well as the binary, from the repository.

### Instructions
Once the project is compiled, you can start using the **Minishell** by running this on your terminal, while on the <ins>same directory you compiled it on</ins>:
`./minishell`

And that's it! You're using it! You can now use it like you would use any **sh-compatible Unix Shell.**
You can additionally add it to your terminal emulator as the default shell.

If you're feeling lazy, you can set your current shell to run it on startup by adding this to your `.zshrc` or `.bashrc`:
`/path/to/minishell/directory/minishell`

## Resources
TODO LIST:
Resources
Exit/execution/error status codes
Unset failure error message
Replace printf's with perror or write 2

## License
This project, including the **42-Libft Library**, is licensed under the **GNU GPL-2.0-or-later.**
This means you are free to <ins>clone this repository</ins>, <ins>study</ins>, <ins>modify</ins>, and use this code for your own **private use**.
If you make modifications to it, and wish to <ins>distribute</ins> binaries of your modified version however, you **must** release the source code <ins>under the same terms.</ins>