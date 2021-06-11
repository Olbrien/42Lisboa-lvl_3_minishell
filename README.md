![GitHub Logo](/extras/images/Success.png)

###### <i>Recent Update on 17/04/2021.</i>
• Fixed many bugs in between.\
• Finished the project.

###### <i>Old Update on 21/04/2021.</i>
• Started the project.

## Subject:

You can find the subject of this project [here.](https://github.com/Olbrien/42Lisboa-lvl_3_minishell/blob/main/extras/lvl_3_minishell.pdf)

![GitHub Logo](/extras/images/Minishell.png)

## How to run:

First download the repository.

If you are on Mac, just type "make".
If you are on Linux type "make linux".

## Info:

Minishell is a pretty lenghty project. The hardest challenge so far. You have to do a lot of things and make
sure everything runs smoothly and that it doesn't crash.

Minishell has 3 important parts:

- Reading your standard input.
- Parsing what you've written.
- Executing what you've parsed.

Looks easy, but it isn't.

There are not a lot of information on the internet how to do a proper Minishell, but I've written informations down there
that might help people doing this project and how we did it. Specially the parsing, it's not as straighforward as you
might think it is.

Also one thing that is really hard to find are the termcaps.
I have an explanation on how to do termcaps and the history required by the subject on the folder [/extras/termcaps_history_explanation/](https://github.com/Olbrien/lvl_3_minishell/blob/main/extras/termcaps_history_explanation/termcaps.c)

#### Some important links:

[Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)\
[Chapter 5. Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)\
[Tiny Shell](http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/index.html)

[AST Viewer](https://ast-viewer.datacamp.com/editor?code=echo%20%22hello%22%20%7C%20wc%20%3E%20file1%20%3E%20fileb&start=NA&grammar=shell)

[Termcaps](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)\
[Signals ASCII Table](http://www.physics.udel.edu/~watson/scen103/ascii.html)

[Shell Documentation](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_01)

## Research:

<pre>
------------------------------------------------------------------------------

Lifetime of a Shell:

A shell does three main things in its lifetime:

	Initialize:
	In this step, a typical shell would read and execute its configuration files.
	These change aspects of the shell’s behavior.

	Interpret:
	Next, the shell reads commands from stdin (which could be interactive, or a file)
	and executes them.

	Terminate: After its commands are executed, the shell executes any shutdown
	commands, frees up any memory, and terminates.


The program needs to loop in order to work. And in the most basic form, the loop
will do 3 things:

	Read:
	Read the command from standard input.

	Parse:
	Separate the command string into a program and arguments.

	Execute:
	Run the parsed command.

------------------------------------------------------------------------------

get_next_line (fd, buffer(**line)).


stdin:  Same as fd = 0.		<--- This is what the keyboard writes.
stdout: Same as fd = 1. 	<--- This is what the shell terminal shows.
stderr: Same as fd = 2. 	<--- This is what the shell terminal shows.

------------------------------------------------------------------------------

We don't know which process starts first using fork() that's why we use
wait on the parent so the child goes first and the parent waits until the child
finishes.

------------------------------------------------------------------------------

Commands:

	builtin:

		history		  (NO Options, NO Args) // List of the history of things you did.
		debugger	  (NO Options, NO Args) // Debug 1 , Debug 2, Debug 0

		echo		  (-n Option,  YES Args) // -n  Do not output a trailing newline.
		pwd			  (NO Options, YES Args)
		export		  (NO Options, YES Args)
		unset		  (NO Options, YES Args)
		env			  (NO Options,  NO Args)
		exit		  (NO Options, YES Args)
		cd			  (relative / abs path)

------------------------------------------------------------------------------

$? - Shows the exit status of the last command.

	Example:

		Type ls on the console. It worked.
		Type now $?, the previous exited status was succesful (0).

		Type wqweqwe. It gave an error.
		Type now $?, the previous exited status gave an error (127).

		Value 127 is returned by your shell /bin/bash when any given
		command within your bash script or on bash command line is not
		found in any of the paths defined by PATH system environment variable.
		The solution is to make sure that the command your are using can be
		found within your $PATH.

		https://tldp.org/LDP/abs/html/exitcodes.html

------------------------------------------------------------------------------

How our program works with examples:

	These examples don't mention error handlings. If you're following the steps you'll be
	able to identify them and do your error handlings easily.


	- Parsing to Command Tables:

	Global Variable:
		Our global variable (mini_sh) is a struct that contains these essential variables
		for parsing:
		- char *line = The line you wrote on your prompt and got from get_next_line().
		- char **cmd_tables = Where you're going to store your command tables.


	Example in action:	 > echo "hello" how are "you

	Step 1:
		We do "get_next_line(0, &line)" to take what the user writes in the prompt.
		It's stored in -> mini_sh.line.

							mini_sh.line = echo "hello" how are "you

		We check if it's NULL (or if the user pressed entered without printing anything).
		If the user did, we do "continue;" until he writes something.

	Step 2:
		Check if the mini_sh.line has wrong quotations. check_complete_quotation().
		It can't have open " or open '.
		" " = Valid!
		'"' = Valid!
		"'  = Invalid!

							echo "hello" how are "you

		Has a open ". Therefor it's	incorrect.
		We return a (0).
		We start all over again from Step 1.
		We now put a new line on the STDIN.



	Example in action:	 > echo "hello ; bye" how are "you" ; echo "I'm fine!" thank you ; ls -a ; env

		Step 1:
			mini_sh.line = echo "hello ; bye" how are "you" ; echo "I'm fine!" thank you ; ls -a ; env

		Step 2:
			It is valid! Quotations are not open!

		Step 3:
			We now check if mini_sh.line has ; so we can divide it by command tables.
			To do that we check the entire string for ";" that are NOT inside " " or ' '.
			After doing that, we take the locations of the ";" and how many there are.

				 echo "hello ; bye" how are "you" ; echo "I'm fine!" thank you ; ls -a ; env
					     .						       .       .
				            /|\						      /|\     /|\
				             |					               |       |
					    38						      61      69

			We have 3 ";" at locations 38, 61 and 69.
			We now have to divide the first line from 0 to 38, the second from 39 to 61, the
			third from 62 to 69 and the last one from 70 to the end.

			We now have:

			line 1:		echo "hello ; bye" how are "you" ;
			line 2:		echo "I'm fine!" thank you ;
			line 3:		ls -a ;
			line 4:		env
			line 5:		NULL

			Always add a last line that is NULL why is that?

			If you do "while (cmd_tables[i] != NULL)", it will scroll all the way to the last
			line. If you don't put line 5 as NULL, that function won't work and it will read
			an empty line and it will give segmentation fault.

		Step 4:
			We now check if we have an empty last line. Where it says line 4: env , there are
			cases it's empty "'\0", if it's empty, we set it to NULL.
			After doing that we remove all ";" from the last character.

			line 1:		echo "hello ; bye" how are "you"
			line 2:		echo "I'm fine!" thank you
			line 3:		ls -a
			line 4:		env
			line 5:		NULL

		Step 5:
			We now put the lines we made into the global variable we called cmd_tables.
			It's our global variable called mini_sh.cmd_tables.

			mini_sh.cmd_tables[0]:	echo "hello ; bye" how are "you"
			mini_sh.cmd_tables[1]:	echo "I'm fine!" thank you
			mini_sh.cmd_tables[2]:	ls -a
			mini_sh.cmd_tables[3]:	env
			mini_sh.cmd_tables[4]:	NULL

			We did this to separate several commands. We're going to send these commands
			to be executed one by one instead of all of them together.







line = echo "hello" olah" " ; echo "adeys" olah" " | grep la

command table[0] = echo "hello" olah" ";
command table[1] = echo "adeys" olah" " | grep la;

args[0] = echo
args[1] = "hello"
args[2] = olah
args[3] = " "
args[4] = '\0'

execve()

------------------------------------------------------------------------------

Signals:

	You can type "stty -a" on your console to see what all terminal line settings are.

	intr = ^C;				SIGINT
	eof = ^D;
	quit = ^\;				SIGQUIT


	intr CHAR
		CHAR will send an interrupt signal
	eof CHAR
		CHAR will send an end of file (terminate the input)
	quit CHAR
		CHAR will send a quit signal

	https://pubs.opengroup.org/onlinepubs/7908799/xsh/signal.h.html


------------------------------------------------------------------------------

https://man7.org/linux/man-pages/man3/termios.3.html

https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_4.html

https://translate.google.com/translate?hl=en&sl=ko&tl=en&u=https%3A%2F%2Fhyeonski.tistory.com%2F5&prev=search

https://translate.google.com/translate?hl=en&sl=ko&tl=en&u=https%3A%2F%2Fhyeonski.tistory.com%2F&prev=search

https://p3tvohguut3jev2d2v27po3nce-adv7ofecxzh2qqi-m-blog-naver-com.translate.goog/PostView.nhn?blogId=y851004&logNo=20063499242&proxyReferer=https://www.google.com/


Termcaps:

					gcc -lncurses


	Canonical Input - When you write on your terminal and you have to press enter
	to enter the command.

	Non Canonical Input - When you type on your terminal, and each letter you type
	it enters immediately.

	You're going to use non canonical input because you'll need to get the

		^[[A -> Up Key
		^[[B -> Down Key


	Struct Termios:

		Struct has 5 modes (input, output, control, local, special control character).

		First you set it up.

		***
		*	struct termios term;
		*
		*	tcgetattr(fd, &term);
		***

		After setting it up you can change it's modes.

		***
		*	term.c_lflag &= ~ICANON;    // Enable canonical mode.
		*	term.c_lflag &= ~ECHO;      // Invisible to the terminal when typing
		*	term.c_cc[VMIN] = 1;        // Minimum input buffer size.
		*	term.c_cc[VTIME] = 0;       // Buffer emptying time (timeout)
		***

		Now you initialize it with tcsetattr(int fd, int action, &term);

		Actions are
			TCSANOW: Change value immediately.
			TCSADRAIN: Change the value when the current output is completed.
			TCSAFLUSH: Change the value when the current output is completed.

		***
		*	struct termios term;
		*
		*	tcgetattr(fd, &term);
		*
		*	term.c_lflag &= ~ICANON;    // Enable canonical mode.
		*	term.c_lflag &= ~ECHO;      // Invisible to the terminal when typing
		*	term.c_cc[VMIN] = 1;        // Minimum input buffer size.
		*	term.c_cc[VTIME] = 0;       // Buffer emptying time (timeout)
		*
		*	tcsetattr(STDIN_FILENO, TCSANOW, &term);
		***



------------------------------------------------------------------------------

Each bash has an identification. If you open a bash and type tty you get an information.

For example it might be 	/dev/pts/1

If you open another bash and type tty the other one will probably be /dev/pts/2
Each bash has it's own identification.

Open 2 bashes, type tty take their infos:

/dev/pts/1
/dev/pts/2

Now on /dev/pts/1 (the first bash you opened) type " echo Olah! > /dev/pts/2

On your /dev/pts/1 should not appear anything, but it should appear on /dev/pts/2



------------------------------------------------------------------------------

Parsing:							(Major headache)

	Example:
		ps -a ";" ; ping -c 1 google.com | grep rtt | wc > aqui.txt ; echo ola < ali.txt < aqui.txt


	1st Step - Command Tables:

		Divide into Command Tables. Command tables are seperated by ; . It can't be inside
		";".
		char **cmd_tables;

		cmd_tables[0] = "ps -a ";" ";
		cmd_tables[1] = "ping -c 1 google.com | grep rtt | wc > aqui.txt ";
		cmd_tables[2] = "echo ola < alix.txt < aqui.txt";
		cmd_tables[3] = NULL;

		Always finish with NULL. Because when you do
		while (cmd_tables != NULL) it finishes at the last one and not give segmentation fault.


	2nd Step - Lists:

		Put it into lists. You have to put one cmd_tables[i] into a list at a time. You
		don't put every cmd_table in lists at once. Once you list cmd_tables[0], you free it
		and then do cmd_tables[1] etc... Heres how.

		Let's do cmd_tables[1]. It has more things.

		This is our list structure.

		typedeft struct s_list
		{
			char			**args;
			char			type;
			struct s_list	*next;

		}				t_list;

		t_list->args[0] = "ping";						t_list->type = '|';
		      ->args[1] = "-c";
		      ->args[2] = "1";						// The root of the t_list is a Pipe.
		      ->args[3] = "google.com";
		      ->args[4] = NULL;

		t_list->next->args[0] = "grep";						t_list->type = '|';
			    ->args[1] = "rtt";
			    ->args[2] = NULL;

		t_list->next->next->args[0] = "wc";					t_list->type = '>';
				  ->args[1] = NULL;

		t_list->next->next->next->args[0] = "aqui.txt";		t_list->type = '>';
						  		->args[1] = NULL;


		Now we have it divided in lists. Now it's easier to divide it into the next
		step.


	3rd Step - Simple Commands:

		Continuing our example.
		S.C. = Simple Commmand.

					    ping -c 1 google.com | grep rtt | wc > aqui.txt
					   |			 |	    |		   |
					   |			 |	    |		   |
					   |	    S.C.	 |   S.C.   |	  S.C.     |

		Simple commands are divided when they find a '|'. If you find a > or >> or <
		you're still on the simple command.

		Another example:

		    ping google.com | grep rtt | wc > aqui.txt < ali.txt > aqui.txt | wc
		   |		    |	       |				    |     |
		   |		    |	       |				    |     |
		   |	  S.C.	    |   S.C.   |		    S.C.	    | S.C.|


		Ok. Back on the cmd_tables[1].

						ping -c 1 google.com | grep rtt | wc > aqui.txt".

		Now we have to divide these in simple commands.
		We make a struct.

		typedeft struct s_simplecommand
		{
			char			**command;
			char			**outfile;	// These are all outfiles.
			char			**infile;	// These are all infile.
			struct s_list	*next;

		}				t_simplecommand;

		t_simplecommand->command[0] = "ping";					..->outfile = NULL;
			       ->command[1] = "-c";					..->infile  = NULL;
			       ->command[2] = "1";
			       ->command[3] = "google.com";
			       ->command[4] = NULL;

		t_simplecommand->next->command[0] = "grep";				..->outfile = NULL;
				     ->command[1] = "rtt";				..->infile  = NULL;
			             ->command[2] = NULL;

		t_simplecommand->next->next->command[0] = "wc";				..->outfile[0] = "aqui.txt";
					   ->command[1] = NULL;				..->outfile[1] = NULL;

											..->infile = NULL;

		The parsing is all done!


	How it will look in the code:

		Input on the bash:
			"ping -c 1 google.com | wc > aqui.txt ; echo ola < ali.txt < aqui.txt";

		void loop()
		{
			int i = 0;

			command_tables(); // Here we divide the Input on the bash in command tables.
							  // It's on a global struct. gstruct->cmd_tables;

			while(cmd_tables[i] != NULL) // We loop one command table at a time.
			{
				convert_to_lists(cmd_tables[i]); // This is the Step 2.
												 // It goes to gstruct->t_list.

				convert_to_simple_commands(gstruct->t_list); // This is Step 3.
												 // It goes to gstruct->simple_commands.

				// Now we have simple commands we do a while loop on it.

				int a = 0;

				while(gstruct->simple_commands[a] != NULL)
				{
					execute(gstruct->simple_commands[a]);
					a++;
				}
				i++;
			}
		}



Info:

outfile '>'
		open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);

outfile '>>'
		open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);

infile	'<'
		open(infile, O_RDONLY);



In any simple command there is only one and only ONE command!
And the only command is ALWAYS the first argument of the simple command. Always.

	 echo ola | echo adeus > te.txt < aqui.txt | ls | wc | wc >> ali.txt
       |	  |				   |    |    |		    |
       |	  |				   |    |    |		    |
       | echo     | echo			   | ls	| wc | wc	    |



Example : "echo ola > aqui.txt > alo.txt"

	You're going to open 2 files in the loop.
	open("aqui.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	open("alo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	Only "ola" of the echo is going to alo.txt
	Aqui.txt is going to be empty.

Example : "echo ola > aqui.txt adeus > alo.txt ali"

	In this example you save "adeus" and "ali" and you put inside alo.txt.
	The outline is always arg[0], the other arguments, in this case, adeus and ali,
	you save it a part and store it in alo.txt.
	Inside alo.txt you're going to have "ola adeus ali".

Example : "cat < ali.txt"

	int fd = open("ali.txt", O_RDONLY);
	If the file doesn't exist fd is going to be -1, if it exists it's going to be another value.

Example : "cat < ali.txt < aqui.txt"

	The file that's going to be "cat" is aqui.txt.
	int fd = open("ali.txt", O_RDONLY);
	int fd = open("aqui.txt", O_RDONLY);

Example : "cat < ali.txt aqui.txt"

	O ficheiro que vai levar o cat é sempre o ultimo argumento.
	int fd = open("ali.txt", O_RDONLY);
	int fd = open("aqui.txt", O_RDONLY);

Example : "echo ola >> aqui.txt adeus > alo.txt ali"

	Here only counts >. It only does O_TRUNC.

Example : "echo ola > aqui.txt adeus >> alo.txt ali"

	Here it only counts >>. Only does O_APPEND.


------------------------------------------------------------------------------

Tests:

	Tokens:

	✅	;;
	✅	;
	✅	echo ola;
	✅	echo ola;;
	✅	; echo ola
	✅	;echo ola
	✅	echo ola ";" ; echo cadela;
	✅	echo ola ; echo adeus
	✅	asdasd
	✅	asdasd ola
	✅	>>
	✅	> echo ola
	✅	echo ola || adeus

	CD:

	✅	cd ../../../../../..
	✅	cd $HOME
	✅	cd ./path_not_found
	✅	cd "srcs"
	✅	cd hello allo
	✅	cd -
	✅	cd $HOME/Documents
	✅	unset HOME; cd

	Echo:

	✅	echo abcd
	✅	echo $HOME
	✅	echo '$HOME'
	✅	echo "$HOME"
	✅	echo -n lalalal
	✅	echo -nABC
	✅	echo $ a
	✅	echo "$     a"
	✅	echo
	✅	echo ""
	✅	echo a"bc"d			
	✅	echo a'bcd'e			
	✅	echo $"HOME"			
	✅	echo $HO"ME"			

	Env:

	✅	env

	Exit:

	✅	exit				
	✅	exit 0				
	✅	exit 1				
	✅	exit -1				
	✅	exit -1				
	✅	exit 12; exit 20		
	✅	exit 12; exit 20		
	✅	exit 1 2 3				

	Export:

	✅	export a=10
	✅	export _abc=10
	✅	export					
	✅	export 111=222			
	✅	export 1abc=123			

	PWD:

	✅	pwd
	✅	pwd hello

	Unset:

	✅	unset a					
	✅	unset babasadasd		
	✅	unset					
	✅	unset a=10				

	Executable Files:

	✅	./exectest
	✅	./exectest teste teste

	Pipes:

	✅	env | grep "_="
	✅	env | grep "SHLVL"
	✅	echo oui | cat -e
	✅	echo oui | echo non | echo something | grep oui
	✅	echo oui | echo non | echo something | grep non
	✅	echo oui | echo non | echo something | grep something
	✅	cat exemplo.txt | grep "FLAGS"
	✅	cat exemplo.txt | cat -e | cat -e
	✅	cat exemplo.txt | grep "FLAGS" | grep "FLAGS" | cat -e
	✅	echo test | cat -e | cat -e | cat -e
	✅	whereis ls | cat -e | cat -e > test
	✅	echo test | cat -e | cat -e | cat -e | cat -e | cat -e |cat -e | cat -e | cat -e \
		| cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e \
		| cat -e | cat -e | cat -e
	✅	ls -la | grep "."
	✅	pwd ; cd .. | echo "something"
	✅	pwd ; cd .. | echo "something" ; pwd
	✅	pwd ; cd .. | echo "something" ; pwd
	✅	cd .. | pwd
	✅	whoami | grep $USER
	✅	export TEST=123 | cat -e | cat -e ; echo $TEST
	✅	unset TEST | cat -e

	Redirections > >>:

	✅	ls > text.txt
	✅	ls > text.txt > texto.txt
	✅	ls > text.txt >> texto.txt // Empty texto.txt
	✅	ls > text.txt >> texto.txt // Not empty texto.txt
	✅	ls > text.txt thrash > texto.txt bla
	✅	ls -la > tmp/file ; cat tmp/file
	✅	echo text > file text2 > file1 ; cat file file1
	✅	echo text > file ; cat file
	✅	echo text > file ; echo text > tmp ; cat file tmp
	✅	echo text$USER > file; cat file
	✅	echo "text" > file >> file1 ; cat file file1
	✅	whereis grep > tmp/file ; cat tmp/file ; ls -la tmp/file
	✅	echo ola > aqui.txt | cat aqui.txt

	Redirections <:

	✅	cat < teste.txt
	✅	cat < teste.txt < teste.txt
	✅	cat < teste.txt < li.txt
	✅	echo ola < aqui.txt < ali.txt
	✅	echo ola < aqui.txt < ali.txt | echo ola
	✅	ls -la > tmp/file ; cat < tmp/file tmp/doesntexist

	Mixed:

	✅	whereis grep > tmp/file ; cat tmp/file ; ls -la tmp/file | grep "grep"
	✅	echo ola < alo.txt
	✅	echo ola < exemplo.txt
	✅	echo ola | cat exemplo.txt
	✅	echo ola | cat alo
	✅	echo ola | cat exemplo.txt > aqui.txt
	✅	echo ola | cat < exemplo.txt
	✅	echo ola | cat < alo


------------------------------------------------------------------------------
</pre>
