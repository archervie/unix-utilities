# UNIX Utilities

This repository consists of rewritings of commonly used UNIX commands: `cat`, `grep`, and `sed`. Each new command is named differently, with a "av" (Archervie's) appended to the beginning of each command to avoid confusion

---

## avcat

The command `avcat` is a rewriting of the `cat` command, printing out the contents of FILE(s) to standard output.

- **Usage:** `avcat [OPTION] [FILE]...`
- **Options:** `-h, --help: Displays help and exits.`
- **Example:**
```
$ avcat file.txt
This is a text file!
```

## avgrep

The command `avgrep` is a rewriting of the `grep` command. The command looks through FILE, line by line, trying to find the specified search term in the line. If a line has the word within it, the line is printed out to standard output, otherwise it is not. The command will read standard input if no FILE is specified.

- **Usage:** `avgrep [OPTION] PATTERN [FILE]`
- **Options:** `-h, --help: Displays help and exits.`
- **Example:**
```
$ avgrep foo bar.txt
This line has 'foo' in it.
Bigfoot is actually a grizzly bear on its hind legs!
I really like food.
```

## avsed

The command `avsed` is a rewriting of the stream editor `sed`. While the main command has various features, this command focuses on two of those features, string substitution and character translation. Substitution mode replaces a term with another term within FILE. Translation mode replaces the characters of the first input with the corresponding characters of the second input in FILE.
- **Usage:** `avsed [OPTION]... [INITIAL] [FINAL] [FILE]`
- **Options:** 
```
-h, --help: Displays help and exits.
-m, --mode: Determines the mode of the command. Can be either 'substitution' or 'translation'.
```
- **Example:**
```
$ avsed -m substitution foo bar myfile.txt
Barbar! I like bard, and those who don't are barlish.
```

---

## Usage
To use these commands, simply clone the repository and compile the commands under `gcc`. 

```
$ git clone https://github.com/archervie/unix-utilities.git ~/projects/
$ cd ~/projects/unix-utilities
$ gcc -Wall -Wextra -Werror -O2 -o avcat avcat.c
$ gcc -Wall -Wextra -Werror -O2 -o avgrep avgrep.c
$ gcc -Wall -Wextra -Werror -O2 -o avsed avsed.c
```

You can add them to `PATH` by copying the binaries over to `~/.local/bin`: `$ cp avcat avgrep avsed ~/.local/bin/`

And exporting the directory by adding it to `PATH`:

- For `bash` or `zsh`: `$ export PATH="$HOME/.local/bin:$PATH"`
- For `fish`: `fish_add_path ~/.local/bin`
