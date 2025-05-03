#include "../includes/minishell.h"

void    *ft_memcpy(void *dst, const void* src, size_t n)
{
    size_t i;
    unsigned char *dest;
    const char *srrc;
    
    i = 0;
    dest = (unsigned char *) dst;
    srrc = (const char *) src;
    if (dest == (NULL) && srrc == (NULL))
    return (dest);
    while (i < n)
    {
        dest[i] = srrc[i];
        i++;
    }
    return (dest);
    
}
// #include<stdio.h>
// int main()
// {

//     char c[]= "abcde";
//     ft_memcpy(c, c + 4, 5 * sizeof (char));
//     for(int i = 0 ; i < 6 ; i++)  
//         printf("%c\n", c[i]);
// }
