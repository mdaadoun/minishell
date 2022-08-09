

valgrind --suppressions=.valgrind_ignore_readline --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./minishell


## Commentaires style

```
/*
 * description function steps
 * @param		nom param: description param
 * @return		description return value
*/
void *function(param)
{
    step 1
    step 2
    return (value)
}
```

* [tutorial](https://github.com/hilmi-yilmaz/blogs/tree/main/)unit-testing-C
* [library](https://github.com/ThrowTheSwitch/Unity)
    * [intro](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityGettingStartedGuide.md)

* [example](https://github.com/alelievr/libft-unit-test)

* https://jera.com/techinfo/jtns/jtn002

## Testing single quote

Bash manual:
> 3.1.2.2 Single Quotes  
> Enclosing characters in single quotes (‘’’) preserves the literal value of each character within
the quotes. A single quote may not occur between single quotes, even when preceded by a
backslash.


## Testing double quote

Bash manual:
> 3.1.2.3 Double Quotes  
> Enclosing characters in double quotes (‘"’) preserves the literal value of all characters within
the quotes, with the exception of ‘$’, ‘‘’, ‘\’, and, when history expansion is enabled, ‘!’.
When the shell is in posix mode (see Section 6.11 [Bash POSIX Mode], page 102), the ‘!’
has no special meaning within double quotes, even when history expansion is enabled. The
characters ‘$’ and ‘‘’ retain their special meaning within double quotes (see Section 3.5
[Shell Expansions], page 22). The backslash retains its special meaning only when followed
by one of the following characters: ‘$’, ‘‘’, ‘"’, ‘\’, or newline. Within double quotes,
backslashes that are followed by one of these characters are removed. Backslashes preceding
characters without a special meaning are left unmodified. A double quote may be quoted
within double quotes by preceding it with a backslash. If enabled, history expansion will
be performed unless an ‘!’ appearing in double quotes is escaped using a backslash. The
backslash preceding the ‘!’ is not removed.
The special parameters ‘*’ and ‘@’ have special meaning when in double quotes (see
Section 3.5.3 [Shell Parameter Expansion], page 25).

Note: for the minishell we don't deal with the escape character \