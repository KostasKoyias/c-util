# vector_t API

## Methods Summary

### Basic

| Name         | Description                                                                        |
|--------------|----------------------------------------------------------------------------------------------------------------------------------|
| `vector_init`    | Initialize a vector with an initial capacity of 2, providing all member methods necessary and size in bytes of a particular data type.|
| `vector_insert`  | Insert an instance of the type specified into the **end** of a vector. A pointer to the arguments will be passed to the init function provided. If vector is full then capacity will be increased either by 1 or by a factor 2(i.e vector will double it's size). <br/><span style="color: red">Only increase by 1 if insertions are rare.</span>|
| `vector_remove`  | Remove the element at the specified position in the vector. Shifts any subsequent elements to the left.      |
| `vector_delete`  | Remove the first matching element based on the `vector->seek` method. Shifts any subsequent elements to the left.      |
| `vector_isfull`  | Return 1 if vector is full or else 0.                                                |
| `vector_get`     | Retrieve by index an item from a vector.            |
| `vector_seek`    | Get a pointer to the first matching item of a vector, `vector->seek` member method needs to be provided on initialization. If element exists, position is stored where the last argument points to. |
| `vector_print`   | Display all elements of a vector using the 'print' method provided.                  |
| `vector_shrink`  | Reduce the capacity of the vector to be equal to fit the current positions taken. Use when vector is final.|
| `vector_free`    | Free all resources allocated for this vector, using the 'free_data' to release each node or [free](https://linux.die.net/man/3/free) if none specified.|

### Advanced

| Name         | Description                                                                        |
|--------------|----------------------------------------------------------------------------------------------------------------------------------|
| `vector_reduce`  | Iterate through the vector and update a total value, passed by address from the caller.                                            |
| `vector_qsort`   | Quick sort the vector using the 'cmp' method provided on initialization.                                         |
| `vector_bsearch` | Binary search on the vector using the `cmp` method provided on initialization. Pass arguments for comparison object to be created with `init`. Use only when vector is sorted.                                          |
| `vector_foreach` | Apply a non-modifiable function to each node of the vector.                          |
| `vector_cmp`     | Compare 2 vectors for equality. Two vectors of the same node size, filled positions(not total length) and 'cmp' member methods are equal if 'cmp' returns 0 for all items on same positions.|
| `vector_clone` | Copy a vector's content and meta-data to an **uninitialized** one, which shall later be freed.                          |

## Type methods

| Name             | Description                                                                                                    |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `init(mandatory)`| Initialize an instance. This function will be called by vector_insert passing a `va_list` pointer to all arguments provided.                                 |
| `cmp`            | Compare two instances of the **same class**. Used to sort vectors by comparison. |
| `seek`           | Compare an instance with a value(not necessarily of the same type e.g it can be just an id pointer). Used to seek for a certain item in the vector. |
| `print`          | Display an instance of this type. Called by vector_print for each vector element.                              |
| `clone`          | Given a pointer to an instance of the vector type, initialize it by cloning an other's payload. Used to clone a vector by cloning all items it contains.     |
| `print`          | Display an item of the vector any way you wish, `vector_print` will use this function for each element it contains.                                |
| `destroy`        | De-allocate all resources used for a certain instance of this vector. Those were allocated during 'init'.      |
