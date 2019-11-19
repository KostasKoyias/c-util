# list_t API

## Methods Summary

| Name         | Description                                                                                                                      |
|--------------|----------------------------------------------------------------------------------------------------------------------------------|
| `list_init`    | Initialize a list, providing all member methods necessary for a specific data type.                                              |
| `list_push`   | Insert an instance of the type specified to the **beginning** of a list. Arguments will be passed to the init function provided. |
| `list_insert`  | Insert an instance of the type specified into the **end** of a list. Arguments will be passed to the init function provided.     |
| `list_isempty` | Return 1 if list is empty or else 0.                                                                                             |
| `list_isfull`  | Return 1 if list is full or else 0.                                                                                              |
| `list_peek`    | Retrieve, without remove though, the head (first element) of this list.                                                          |
| `list_pop`     | Remove the head (first element) of this list.                                                                                    |
| `list_delete`  | Delete the requesting item. Member method 'cmp' needs to be provided.                                                            |
| `list_search`  | Return a pointer to an item or NULL if none matches the criteria. Member method 'cmp' needs to be provided.                      |
| `list_print`   | Display all elements of a list using the 'print' method provided.                                                                |
| `list_free`    | Free all resources allocated for this list, using the 'free_data' to release each node or [free](https://linux.die.net/man/3/free) if none specified.|
| `list_reduce`  | Iterate through the list and update a total value, passed by address from the caller.                                            |
| `list_foreach` | Apply a non-modifiable function to each node of the list.                                                                        |
| `list_map`     | Apply a value-modifying function to each node of the list.                                                                       |
| `list_best`    | Retrieve the maximum or minimum valued element of the list. Member method 'cmp' needs to be provided.                            |

## Type methods

| Name             | Description                                                                                                                                                  |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `init(mandatory)` | Initialize an instance. On node addition(front or end), this function will be called by list_insert.                                                         |
| `cmp`              | Compare an instance with a value(not necessarily of the same type e.g it can be just an id pointer). Used to find a certain instance or the 'best'(min or max)  one. |
| `print`            | Display an instance of this type. Called by list_print for each list element.                                                                                |
| `destroy`        | De-allocate all resources used for a certain instance of this list. Those were allocated during 'init'.                                                      |
