#   MINISHELL PART
##  Require function
- malloc
- free
- access
- open
- close
- read
- write
- opendir
- readdir
- closedir
- getcwd
- chdir
- stat
- lstat
- fstat
- fork
- execve
- wait
- waitpid
- wait3
- wait4
- signal
- kill
- exit

##  Mandatory
- fork, PID manager for execve

- error handling

- `$` and `~`

##  Builtin's
- echo
	-e lire les char en tenant compte du '\'

- cd
	use `access` to check right

- setenv


- unsetenv
	make a 'reset default env' (cause my keybord is shity HF)

- env
	env parser

- exit
	shell_lvl...

##  Bonus
- auto-completion
- history of all typed cmd (to implement thinks like !!)
- `;` separator
- Handling signal (global variable autorized)


#   21SH PART
##	Require function
- malloc, free
- access
- open, close, read, write
- opendir, readdir, closedir
- getcwd, chdir
- stat, lstat, fstat
- fork, execve
- wait, waitpid, wait3; wait4
- signal, kill
- exit
- pipe
- dup, dup2
- isatty, ttyname, ttyslot
- ioctl
- getenv
- tcsetattr, tcgetattr
- tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
##  mandatory
- `Ctrl+C` `Ctrl+D` in line edit and process execution

- `;` `|` separator's

- `<` `>` `<<` `>>` redirector

- Agrégations de descripteurs de fichier
	https://abs.traduc.org/abs-5.3-fr/ch19.html

- Line edition & cursor & keybord maping
	1. edit line were the cursor is
	2. move cursor with `←` and `→` arrow
	3. reload history line with `↑` and `↓` arrow and edit copy 	(not directly history)
	4. copy/cut/paste (free to decide wich key)
	5. `Ctrl + ←` and `Ctrl + →` to move cursor by word
	6. `home` and `end` to move at begining or end of line
	7. write and edit multi-line command (Ctrl+`↑` and `↓` to 		change line seems good)
	8. handle 'quotes' and "doubles quotes" even on multi-line 		(no expension)
##  bonus
- history with `Ctrl+R`
- auto-completion using `tab`
- syntaxic coloration (on/off)