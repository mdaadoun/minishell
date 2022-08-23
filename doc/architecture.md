# Architecture

## Workflow steps

**READ > EVALUATE > PRINT > LOOP** (REPL)

### 1) parser -> Tokenization

### 2) analyzer, lexical analyzer

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