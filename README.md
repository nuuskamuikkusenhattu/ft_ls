HIVE HELSINKI project ft_ls

In this project I reproduce behavior of command ls with options -latrR, and as a bonus options -fioT1.

The project is written according to 42-Norme, which comes some restrictions (some of the code may look quite odd), such as:
- max 25 lines per function
- max line width (forces to use non-descriptive variable names)
- no for-loops
- no declarations and definitions on the same line

Also, only few library functions were allowed. Therefore I am calling for the self-written ft_strdup() and ft_strcmp() instead of strdup() and strcmp(), for example.

A column output was written as a bonus:

<example pics>

ft_ls was a good opportunity to learn more about Unix-systems, what sort of files there are, and what sort of information a file is attached with. An example of -l output:

