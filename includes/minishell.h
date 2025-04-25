#ifndef MINISHELL_H
#define MINISHELL_H


typedef enum t_token_type{
    WORD, // string 
    HERDOC, // <<
    APPEND, // >>
    REDIR_IN, // >
    REDIR_OUT, // <
    PIPE, // |
};

typedef struct s_tokens{
    char *str;
    enum t_token_type type;
    s_tokens *next;
} t_tokens;


//FUNCTION EXECUTION



// FUNCTION PARSING



#endif
