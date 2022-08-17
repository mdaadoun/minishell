
#include "../../inc/minishell.h"

void	test_quotes(t_minishell *ms, int debug)
{
	test_run_command(ms, "'echo \"lol 'lol' lol\" lol'", debug);
	// test_run_command(ms, "'echo lol'", debug);
	// test_run_command(ms, "'hello' hello hello", debug);
    // test_run_command(ms, "'hello'", debug);
    // test_run_command(ms, "'he\"l\"lo'", debug);
    // test_run_command(ms, "test'123\"456\"123'test", debug);
    // test_run_command(ms, "test\"123'456'123\"test", debug);
    // test_run_command(ms, "test\"123'456'123\"test", debug);
    // test_run_command(ms, "'hello' hello hello", debug);
    // test_run_command(ms, "cat \"cat cat\"", debug);
    // test_run_command(ms, "cd '$home'", debug);
    // test_run_command(ms, "'$home'cd cd cd", debug);
}

void	test_env(t_minishell *ms, int debug)
{
	test_run_command(ms, "echo $PAGER", debug);
	test_run_command(ms, "echo $BA", debug);
	// test_run_command(ms, "$BA", debug);
	// test_run_command(ms, "$BA echo", debug);
	// test_run_command(ms, "export a=$BA", debug);
	// test_run_command(ms, "echo \"$LOGNAME\"", debug);
	// test_run_command(ms, "echo \'$LOGNAME\'", debug);
	// test_run_command(ms, "echo test     \\    test", debug);
	// test_run_command(ms, "echo \"test", debug);
	// test_run_command(ms, "echo $TEST", debug);
	// test_run_command(ms, "echo \"$TEST\"", debug);
	// test_run_command(ms, "\"echo '$TEST'\"", debug);
	// test_run_command(ms, "echo \"$TEST$TEST$TEST\"", debug);
	// test_run_command(ms, "echo \"$TEST$TEST=lol$TEST\"", debug);
	// test_run_command(ms, "echo \"   $TEST lol $TEST\"", debug);
	// test_run_command(ms, "echo $TEST$TEST$TEST", debug);
	// test_run_command(ms, "echo $TEST$TEST=lol$TEST""lol", debug);
	// test_run_command(ms, "echo    $TEST lol $TEST", debug);
	// test_run_command(ms, "echo test "" test "" test", debug);
	// test_run_command(ms, "echo \"\\$TEST\"", debug);
	// test_run_command(ms, "echo \"$=TEST\"", debug);
	// test_run_command(ms, "echo \"$\"", debug);
	// test_run_command(ms, "echo \"$?TEST\"", debug);
	// test_run_command(ms, "echo $TEST $TEST", debug);
	// test_run_command(ms, "echo \"$1TEST\"", debug);
	// test_run_command(ms, "echo \"$T1TEST\"", debug);
	// test_run_command(ms, "export =", debug);
	test_run_command(ms, "$a $b $c", debug);
	test_run_command(ms, "$a\" $b \"$c", debug);
	test_run_command(ms, "$a' $b '$c", debug);
	// test_run_command(ms, "export 1TEST= ; env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export TEST ; export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD", debug);
	// test_run_command(ms, "export ""="" ;  env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export TES=T="" ; env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export TE+S=T="" ; env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export TEST=LOL ; echo $TEST ; env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST", debug);
	// test_run_command(ms, "export TEST=LOL; export TEST+=LOL ; echo $TEST ; env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "env | sort | grep -v SHLVL | grep -v _=", debug);
	// test_run_command(ms, "export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD", debug);
	// test_run_command(ms, "export TEST=\"ls       -l     - a\"", debug);
	// test_run_command(ms, "echo $TEST", debug); 
	// test_run_command(ms, "$LS env | sort | grep -v SHLVL | grep -v _=", debug);
}

void	test_pipes(t_minishell *ms, int debug)
{
	test_run_command(ms, "env | wc", debug);
	test_run_command(ms, "env | wc | wc -l", debug);
	test_run_command(ms, "cat Makefile|wc -l", debug);
    test_run_command(ms, "cat Makefile | wc -l", debug);
    test_run_command(ms, "cat 'Makefile|wc' -l", debug);
    test_run_command(ms, "| | | | |", debug);
    test_run_command(ms, "'hello' | hello | hello", debug);
    test_run_command(ms, "cat | | \"cat | cat\"", debug);
    test_run_command(ms, "||cd | '$home'", debug);
    test_run_command(ms, "'$home'cd | cd | cd", debug);
    test_run_command(ms, "|", debug);
    test_run_command(ms, "|wc -l", debug);
    test_run_command(ms, "cat|ls", debug);
    test_run_command(ms, "|cat|ls", debug);
    test_run_command(ms, "ls|cat|", debug);
    test_run_command(ms, "|ls|cat|", debug);
    test_run_command(ms, "||||", debug);
    test_run_command(ms, "| | | |", debug);
    test_run_command(ms, "echo hi | cat | cat | cat | cat", debug);
    test_run_command(ms, "echo | cat | ls | cd | export a | export b", debug);
    test_run_command(ms, "echo echo cat | cat cat cat | ls ls cat | cd echo export | export cat cat | export export", debug);
    test_run_command(ms, "cat | \"cat | cat\"", debug);
    test_run_command(ms, "echo hi | 'cat' | cat | 'ls' | cat", debug);
    test_run_command(ms, "cat tests/lorem.txt | grep arcu | cat -e", debug);
    test_run_command(ms, "echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e", debug);
    test_run_command(ms, "cat /dev/random | head -c 100 | wc -c", debug);
    test_run_command(ms, "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls", debug);
    test_run_command(ms, "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls", debug);
}

void	test_redirections(t_minishell *ms, int debug)
{
    // test_run_command(ms, "> > <<", debug);
    // test_run_command(ms, "bb>cc <<dd", debug);
    // test_run_command(ms, ">>cc <<dd", debug);
    // test_run_command(ms, ">cc <<dd>", debug);
    // test_run_command(ms, "<<dxd>>", debug);
    // test_run_command(ms, ">cc <<dxd>>dcd>>ded<<dsd>dda<aa>><><>><<><><<<>", debug);
    // test_run_command(ms, ">><><>><<><><<<>", debug);
    // test_run_command(ms, "aa >dd bb>cc dd<<dd", debug);
    // test_run_command(ms, "asd>qw <as as<<", debug);
    // test_run_command(ms, "'>>'> > <", debug);
    // test_run_command(ms, ">>> > <<", debug);
    // test_run_command(ms, "> >> <<", debug);
    // test_run_command(ms, "> \">>\" <<", debug);
    // test_run_command(ms, "> '\">>\" <<\">>\" <<\">>\"' <<", debug);
	// test_run_command(ms, "echo hello > file | cat", debug);
	// test_run_command(ms, "echo test > ls | cat ls", debug);
	// test_run_command(ms, "echo test > ls >> ls >> ls | echo test >> ls | cat ls", debug);
	// test_run_command(ms, "> lol echo test lol | cat lol", debug);
	// test_run_command(ms, ">lol echo > test>lol>test>>lol>test mdr >lol test >test | cat test", debug);
	// test_run_command(ms, ">lol echo '> test>lol>test>>\"lol>test\" mdr >lol test >test' | cat test", debug);
	// test_run_command(ms, ">lol echo \"> test>lol>test>>'lol>test' mdr >lol test >test'\" | cat test", debug);
	// test_run_command(ms, ">>> < >> < << > <<< > > < < <<< >>>> <<<< > file | cat", debug);
	// test_run_command(ms, ">>> < >> < \"<< > <<< >\" > < < <<< >>>> <<<< > file | cat", debug);
	// test_run_command(ms, ">>> < >> '< << > <<< > > < < <<<' >>>> <<<< > file | cat", debug);
	// test_run_command(ms, "cat < ls", debug);
	// test_run_command(ms, "cat < ls > ls", debug);
	test_run_command(ms, "cat << EOF", debug);
	// test_run_command(ms, "cat << EOF1 << EOF2", debug);
	// test_run_command(ms, "cat << EOF1 << EOF2<<EOF3", debug);
	// test_run_command(ms, "cat << EOF1 << EOF2<<EOF3<<", debug);
	// test_run_command(ms, "cat << EOF1 | cat << EOF2", debug);
	// test_run_command(ms, "|cat<<EOF1|cat<<EOF2|", debug);
	// test_run_command(ms, ">>cat<<EOF1|cat<<EOF2<<", debug);
}

void test_arguments(t_minishell *ms, int debug)
{
    test_run_command(ms, "cat hello -o adsld | asd", debug);
    test_run_command(ms, "echo -la rmasd | export -l asd", debug);
    test_run_command(ms, "ls hello test | cat cat", debug);
    test_run_command(ms, "cat -o | ls ls | cat cat cat -cat", debug);
}
