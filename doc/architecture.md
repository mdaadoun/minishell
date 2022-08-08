# Architecture

TODO : https://draw.42l.fr/


## Workflow steps

**READ > EVALUATE > PRINT > LOOP** (REPL)

### 1) Lexer, lexical analyzer

* Tokenization

### 3) parser -> AST ?

### 3) Executor, printing the result

## Boucle

La boucle générale du programme:

```c
while (1)
{
    display_prompt(); // prompt and readline
    check_input(); // parse and errors
    tokenization_data(); // analysis of input and data structure (AST ?)
    if ( fork() != 0 ) // parent
        wait (NULL); // wait for child
    else
        execve ? // execution du programme child from data
}
```