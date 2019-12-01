#   MINISHELL PART
##  Require function
- malloc, free
- access
	http://manpagesfr.free.fr/man/man2/access.2.html
- open, close, read
	http://manpagesfr.free.fr/man/man2/open.2.html
	http://manpagesfr.free.fr/man/man2/close.2.html
	http://manpagesfr.free.fr/man/man2/read.2.html
- write
	http://manpagesfr.free.fr/man/man2/write.2.html
- opendir
	http://manpagesfr.free.fr/man/man3/opendir.3.html
- readdir
	http://manpagesfr.free.fr/man/man3/readdir.3.html
- closedir
	http://manpagesfr.free.fr/man/man3/closedir.3.html
- getcwd
	http://manpagesfr.free.fr/man/man3/getcwd.3.html
- chdir
	http://manpagesfr.free.fr/man/man2/chdir.2.html
- stat, lstat, fstat
	http://manpagesfr.free.fr/man/man2/stat.2.html
- fork
	http://manpagesfr.free.fr/man/man2/fork.2.html
- execve
	http://manpagesfr.free.fr/man/man2/execve.2.html
- wait, waitpid
	http://manpagesfr.free.fr/man/man2/wait.2.html
- wait3
	https://linux.die.net/man/2/wait3
- wait4
	http://manpagesfr.free.fr/man/man2/wait4.2.html
- signal
	http://manpagesfr.free.fr/man/man2/signal.2.html
- kill
	http://manpagesfr.free.fr/man/man2/kill.2.html
- exit
	http://manpagesfr.free.fr/man/man3/exit.3.html

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

- exit
	shell_lvl...

##  Bonus
- PS1 or (and?) bashrc compatible
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