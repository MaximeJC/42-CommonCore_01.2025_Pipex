## :warning: Disclaimer

[ :uk: ] Please do not copy-paste this code. In this way, you won't learn a lot. Instead, you can use it to understand how to do some tricky part, but try to redo it by your own.
Just to let you know, some files may be incorrect. Some bugs may have passed through, or subject may have changed since I did this project.

[ :fr: ] S'il vous plait, ne copier-coller pas ce code. De cette manière, vous n'apprendrez pas grand chose. A la place, vous pouvez l'utiliser pour comprendre certaines parties plus complexes du sujet, mais essayez de le refaire par vos propres moyens.
Pour information, certains exercices pourraient être incorrects. Quelques bugs pourraient avoir réussi à passer au travers les mailles du filet, ou le sujet a peut-être changé depuis que j'ai complété le projet.

---
# 42-CommonCore_01.2025_Pipex

The goal of this 42 common core project is to create a program able to execute commands in forks and to make them communicate with pipes. It's kind of a preview of an upcoming project in common core rank 3, "Minishell". 

Mandatory project takes 4 arguments: two files (one in, one out) and two commands. A pipe will be used in code between the commands.
In the bonus part (compile using `make bonus`), you can use more commands, execute more pipes and/or begin with "here_doc" as first argument to use some here_doc instead of the infile, and use the given outfile in append mode. 

## Usage

Mandaroty project:

```bash
./pipex "infile" "command 1" "command 2" "outfile"
```

Bonus project:

```bash
./pipex "infile" "command 1" "command 2" ... "command n" "outfile"
   OR
./pipex here_doc "limiter" "command 1" "command 2" ... "command n" "outfile"
```

_Common Core Rank 02 - Completed in January 2025_  
_Code by me_
