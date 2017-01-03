       -c     with  -lt:  sort  by, and show, ctime (time of last modification of file status information); with -l:
              show ctime and sort by name; otherwise: sort by ctime, newest first


       -f     do not sort, enable -aU, disable -ls --color

       -F, --classify
              append indicator (one of */=>@|) to entries

       --file-type
              likewise, except do not append '*'

       --format=WORD
              across -x, commas -m, horizontal -x, long -l, single-column -1, verbose -l, vertical -C



       --group-directories-first
              group directories before files;

              can be augmented with a --sort option, but any use of --sort=none (-U) disables grouping

       -G, --no-group
              in a long listing, don't print group names

       --si   likewise, but use powers of 1000 not 1024

       -H, --dereference-command-line
              follow symbolic links listed on the command line

       --dereference-command-line-symlink-to-dir
              follow each command line symbolic link

              that points to a directory


       --indicator-style=WORD
              append indicator with style WORD to entry names: none (default), slash (-p), file-type  (--file-type),
              classify (-F)


       -L, --dereference
              when  showing  file information for a symbolic link, show information for the file the link references
              rather than for the link itself


       -N, --literal
              print raw entry names (don't treat e.g. control characters specially)



       --show-control-chars
              show nongraphic characters as-is (the default, unless program is 'ls' and output is a terminal)

       -s, --size
              print the allocated size of each file, in blocks


       --time-style=STYLE
              with  -l,  show times using style STYLE: full-iso, long-iso, iso, locale, or +FORMAT; FORMAT is inter‐
              preted like in 'date'; if FORMAT is FORMAT1<newline>FORMAT2, then FORMAT1 applies to non-recent  files
              and  FORMAT2  to recent files; if STYLE is prefixed with 'posix-', STYLE takes effect only outside the
              POSIX locale

       -u     with -lt: sort by, and show, access time; with -l: show access time and sort by name; otherwise:  sort
              by access time

       -w, --width=COLS
              assume screen width instead of current value


       -Z, --context
              print any security context of each file



       The SIZE argument is an integer and optional unit (example: 10K is 10*1024).  Units are K,M,G,T,P,E,Z,Y (pow‐
       ers of 1024) or KB,MB,... (powers of 1000).

       Using color to distinguish file types is disabled both by default and with --color=never.  With --color=auto,
       ls  emits  color codes only when standard output is connected to a terminal.  The LS_COLORS environment vari‐
       able can change the settings.  Use the dircolors command to set it.

   Exit status:
       0      if OK,

       1      if minor problems (e.g., cannot access subdirectory),

       2      if serious trouble (e.g., cannot access command-line argument).

       GNU  coreutils  online  help:  <http://www.gnu.org/software/coreutils/>  Report  ls   translation   bugs   to
       <http://translationproject.org/team/>

AUTHOR
       Written by Richard M. Stallman and David MacKenzie.

COPYRIGHT
       Copyright   ©   2014   Free   Software  Foundation,  Inc.   License  GPLv3+:  GNU  GPL  version  3  or  later
       <http://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent  per‐
       mitted by law.

SEE ALSO
       The  full  documentation  for ls is maintained as a Texinfo manual.  If the info and ls programs are properly
       installed at your site, the command

              info coreutils 'ls invocation'

       should give you access to the complete manual.

GNU coreutils 8.23                                    July 2014                                                LS(1)
