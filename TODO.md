# TODO

* echo $? > valgrind > definitely lost: 6 bytes in 2 blocks > swap (ms_parse_variables.c:51)

* comparer exit status
	* ne pas ecrire et retourner une erreur si seulement heredoc

* segmentation fault
	"|  <  |  >> < > | echo hello"

* clear, top
	* TERM environment variable not set. (The env is ok ?)

* tester chaque commande de test_lists dans bash et comparer result + $? avec minishell