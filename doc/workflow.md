
## Workflow steps

**READ > EVALUATE > PRINT > LOOP** (REPL)

### 1) Lexer, lexical analyser

* Tokenization

### 3) parser -> AST ?

### 3) Executor, printing the result

## Boucle

La boucle générale du programme:

```c
while (1)
{
    display_prompt();
    read_input(); // parse and analysis of input
    if ( fork() != 0 ) // parent
        wait (NULL);
    else
        execve ? // execution du programme
}
```