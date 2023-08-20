# pipex
<img width="2099" alt="Screen Shot 2023-08-20 at 5 57 51 PM" src="https://github.com/bsanjok/pipex/assets/32704316/cc8ba737-c73a-4ddd-a331-8b81dbadb1cf">
<p>The project deals with handling pipes and processes to mimic the piping behaviour of shell. </p>
pipex program takes 4 arguments as below:
<p><b>./pipex file1 cmd1 cmd2 file2</b></p>
where,
<br>• file1 and file2 are file names.
<br>• cmd1 and cmd2 are shell commands with their parameters.
<p>It must behave exactly the same as the shell.</p>
<br>As bonus, I also handle multiple pipes and heredoc feature. For example:
<br> <b>./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2</b>
<br>shell equivalent: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
<br>and heredoc as: 
<br>$> <b>./pipex here_doc LIMITER cmd cmd1 file </b>
<br>shell equivalent: cmd << LIMITER | cmd1 >> file
