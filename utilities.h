#ifndef SON_UTILITIES_H
#define SON_UTILITIES_H
#endif //SON_UTILITIES_H

#include <iostream>
#include <cstdlib>

int	ft_strlen(const char* str){ // RETURNS LENGTH OF THE STRING THAT CREATED AS CHAR POINTER
    int	i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}

bool ft_is_word_valid(char* word){ // CHECKS VALIDITY OF THE WORD
    if (ft_strlen(word) < 1) return false;
    while (*word)
        if ((*word >= 'a' && *word <= 'z') || (*word >= 'A' && *word <= 'Z') || *word == 39)// 39 = '
            word++;
        else return false;
    return true;
}

static int	ft_char_in_set(char c, char const* set){ // STATIC BECAUSE ONLY USED IN THIS HEADER FILE
    size_t	i;
    i = 0;
    while (set[i]){
        if (set[i] == c) return (1);
        i++;
    }
    return (0);
}

char* ft_strtrim(char const* str, char const* set){ // TRIMS NOT ALFEBETICAL CHARACTERS FROM START AND END OF WORD
    char* res;
    size_t	i;
    size_t	start;
    size_t	end;
    start = 0;
    while (str[start] && ft_char_in_set(str[start], set))
        start++;
    end = ft_strlen(str);
    while (end > start && ft_char_in_set(str[end - 1], set))
        end--;
    res = (char*)malloc(sizeof(char) * (end - start + 1));
    if (!res) return (nullptr);
    i = 0;
    while (start < end)
        res[i++] = str[start++];
    res[i] = '\0';
    return (res);
}

int  ft_atoi(char* str){ // ARRAY TO INTEGER
    int sum;
    int sign;
    int found;
    sum = 0;
    sign = 1;
    found = 1;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
        str++;
    if (*str == '-') sign = -1;
    if (*str == '-' || *str == '+') str++;
    while (str && found){
        if (*str >= '0' && *str <= '9') sum = sum * 10 + *str - '0';
        else found = 0;
        str++;
    }
    return (sign * sum);
}

void ft_to_lower(std::string& index){ // CONVERTS UPPERCASE LETTERS TO LOWERCASE
    size_t length = index.length();
    char x;
    for (size_t i = 0; i < length; i++) {
        x = index[i];
        if (x >= 65 && x <= 90) {
            x += 32;
            index[i] = x;
        }
    }
}
