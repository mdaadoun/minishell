/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaadoun <mdaadoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:48:48 by mdaadoun          #+#    #+#             */
/*   Updated: 2022/08/02 17:15:19 by mdaadoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * Free memory related to the last command.
*/
void ms_free_last_command(t_minishell *ms)
{
    if (ms)
    {
        if (ms->line)
            free(ms->line);
        ms_free_all_tokens(ms);
    }
}

/*
 * @params:
 *      err: the error key
 * @return:
 *      the message related to the error key
*/
char *get_err_msg(int err_key)
{
    char *str;
    
    if (err_key == ERROR_PARAMS)
        str = MSG_ERROR_PARAMS;
    else if (err_key == ERROR_ALLOC)
        str = MSG_ERROR_ALLOC;
    else
        str = MSG_ERROR_UNKNOWN;
    return (str);
}

/*
 *  Free all the process allocated memory and print err message.
 *  
 * @params:
 *      ms  :   the main minishell data structure to free.
 *      err :   the error object containing key and msg.
 * @return:
 *      EXIT_SUCCESS or EXIT_FAILURE depending err.
*/
int    ms_free_before_exit(t_minishell *ms, int err_key)
{
    char *msg;
    int  i;

    i = 0;
    ft_printf("exit\n");
    msg = get_err_msg(err_key);
    if (ms)
    {
        if (ms->cwd_path)
            free(ms->cwd_path);
        if (ms->bin_paths)
        {
            while(ms->bin_paths[i])
            {
                free(ms->bin_paths[i]);
                i++;
            }
            free(ms->bin_paths);
        }
        ms_free_last_command(ms);
        free(ms);
    }
    if (err_key == SUCCESS)
        return (EXIT_SUCCESS);
    else
    {
        ft_printf("%s", msg);
        return (EXIT_FAILURE);
    }
}
