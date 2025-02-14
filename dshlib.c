#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist) {
    char *token;
    char *saveptr;
    char *cmd_copy;
    int cmd_idx = 0;

    memset(clist, 0, sizeof(command_list_t));

    if (strlen(cmd_line) == 0) {
        return WARN_NO_CMDS;
    }

    cmd_copy = strdup(cmd_line);
    if (!cmd_copy) {
        return ERR_CMD_OR_ARGS_TOO_BIG;
    }

    token = strtok_r(cmd_copy, PIPE_STRING, &saveptr);
    while (token) {
        char *cmd_start = token;
        char *args_start;

        if (cmd_idx >= CMD_MAX) {
            free(cmd_copy);
            return ERR_TOO_MANY_COMMANDS;
        }

        while (*cmd_start == SPACE_CHAR) {
            cmd_start++;
        }

        args_start = strchr(cmd_start, SPACE_CHAR);
        if (args_start) {
            *args_start = '\0';
            args_start++; 
            
            while (*args_start == SPACE_CHAR) {
                args_start++;
            }

            if (*args_start != '\0') {
                if (strlen(args_start) >= ARG_MAX) {
                    free(cmd_copy);
                    return ERR_CMD_OR_ARGS_TOO_BIG;
                }
                strcpy(clist->commands[cmd_idx].args, args_start);
            }
        }

        if (strlen(cmd_start) >= EXE_MAX) {
            free(cmd_copy);
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
        strcpy(clist->commands[cmd_idx].exe, cmd_start);
        
        cmd_idx++;
        token = strtok_r(NULL, PIPE_STRING, &saveptr);
    }

    free(cmd_copy);
    clist->num = cmd_idx;
    return cmd_idx > 0 ? OK : WARN_NO_CMDS;
}
