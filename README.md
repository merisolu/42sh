# 42sh

This is it, "The Big One", 42sh is a milestone project at [Hive, Helsinki](https://www.hive.fi/en/). The aim is to build the most complete and stable Unix Shell possible.

This shell does a lot, like A LOT. Here's an overview video if you'd like a 'guided tour' of the basic features and few more nifty things:

## Video overview of 42sh:
[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/b0ElN0rlrEs/0.jpg)](http://www.youtube.com/watch?v=b0ElN0rlrEs)

## Intro

Utilising the skills we learned while completeing [21sh](https://github.com/AlexMannDesigns/21sh), this is a more enhanced and "semi-POSIX-compliant" implementation of a Unix Shell. 

This shell is effectively 'built on top of' 21sh, although to create some of the features needed for 42sh, some parts of the program had to be completely overhauled. As such, please see the 21sh readme, everything that shell can do, this shell can do better! Only the features unique to 42sh are covered here. 

My project partner and I used [Bash](https://www.gnu.org/software/bash/) as a reference, and frequently referred to the [POSIX standard](https://pubs.opengroup.org/onlinepubs/9699919799/), while working on this project.

## Features included:
This shell boasts the following features:

```
  - Execution of simple commands
  - Pipes "|"
  - The following redirection operations: ">", "<", ">>" and "<<"
  - File descriptor aggregation ">&"
  - Command line separators ";" and logical-operators "&&" and "||"
  - Both environment and internal shell variables (export, set, unset)
  - Job control monitoring (jobs, fg, bg, and the '&' operator)
  - Correct monitoring of all signals
  - Inhibitors (" ", ' ', \)
  - Tilde expansion and additional parameter expansion formats (e.g. '${parameter:+word}')
  - Complete history management, including expansions such as '!!' or '!word' and the fc built-in
  - Contextual dynamic autocompletion of commands, built-ins, filepaths and variables
  - A hash table
```

...and the following built-in functions. All POSIX compliant except for set and unset:

```
  - cd
  - echo
  - exit
  - export
  - fc
  - unset
  - hash
  - jobs
  - fg
  - bg
  - test
  - true
  - false
  - type
  - set
```
  
## Installing and running:
To compile and run this program you will need:
  - A Unix or Unix-like operating system (preferrably MacOs or Linux)
  - GNU Make 3.81

Clone this repository and in the root directory run the following command to enter the shell: `make; ./42sh`

## Modular features

- Inhibitors

42sh includes full handling of single quotes, double quotes and backslashes. Text input can be edited across multiple lines and single quotes and backslashes can be used to inhibit the expasion of variables. Double quotes will only inhibit tilde expansion.

- Additional parameter expansion formats

The following formats are fully handled in this shell, and will even autocomplete [this is something even bash can't do ;) ]. I also added a basic implementation of globbing with '*', to demonstrate the pattern matching functionalities of the last 4 formats listed below:

```
  - ${parameter:-word}
  - ${parameter:=word}
  - ${parameter:?word}
  - ${parameter:+word}
  - ${#parameter}
  - ${parameter%}
  - ${parameter%%}
  - ${parameter#}
  - ${parameter##}
```

## Resources we found very useful:

- [The Bash Hackers Wiki](https://wiki.bash-hackers.org/)
- The Open Group's documentation, specifically, [this page on Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [The Art Of Unix Programming](http://www.catb.org/esr/writings/taoup/html/)
