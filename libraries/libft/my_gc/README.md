# A C garbage collector
A custom garbage collector for C.  
**42 norm compliant.**  
> [!TIP]
> **No more memory leaks.**  

> [!NOTE]
>**important**: 
If you chose to use this gc, you shall not use `free()` nor `malloc()` to avoid confusion, redundancy and errors such as double freeing.
This gc already covers all the requirements for memory management, thus no need for the previous functions.
# How to use
## 1. Memory allocation
### Lists
Lists are used to keep track of the allocated memory.
The list structure is the following:
```
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
```
### Basic usage
To allocate memory, use `my_malloc(NULL, list, size)` and pass your list to the function.
The usage is the same as malloc, it will return a pointer to the allocated memory.

You can add already allocated memory to a list with the function `my_addtolist(list, *ptr)`.

You can add an allocated array of any type directly to a list with the function `my_array_addtolist(list, **ptr)`, thus no need to call `my_addtolist()` in a loop.
Note that this array has to be `NULL` terminated.

### List of lists
If you need to use several lists, for example in minishell (a tiny bash), one list was created for each command, and then freed once executed.
To create such a list, 2 sollutions:
1. Add each new list to a given list with `my_addtolist(list_of_list, ptr_to_the_new_list)`.
2. Give the list_of_list directly in parameter to `my_malloc(list_of_list, list, size)`, it will check if the list is already in the list_of_list, if not it will add it, otherwise nothing happens.
A good practice is to create a `list_of_list` that will keep track of each list and can free them all at once with `my_multi_free(list_of_list)`.

### Custom functions
Customs functions are functions that have been adapted to work as intended and add the memory directly to the list.
`my_strdup(list, str)` duplicates the given string, allocate memory and add it to the list, then return a pointer to the new string.

### Errors
No need to check for allocation error, if one occurs, the program will `exit(1)`.
Otherwise, if for example the wrong parameters are given, a NULL pointer will be returned, or nothing will happen.

## 2. Freeing memory
If you do not use `free()` at anytime in your program, double free shall not be possible.
Even if you already freed an element from this list using `my_free_one`, or if you already freed a list, calling again a freeing function over this list will not cause any issue.
So do not hesitate to free all the lists at end of your program using `my_multi_free()` for a full cleaning, even if some were already freed.
Memory can be freed in different ways:
### One list
Using `my_free(list)` to free one list.
### All at once
Using `my_multi_free(list_of_list)` to free all the lists at once.
### One element
In the contrary, you can choose to free only one element of a list using `my_free_one(list, target)`.

# 3. Note
You should include also the files in `./src/` in your Makefile or during compilation if you do not have your own `libft` with the needed functions.