# map_t API

## Methods Summary

| Name          | Description                                                                                                                      |
|---------------|----------------------------------------------------------------------------------------------------------------------------------|
| `map_init`    | Initialize a map with an initial capacity of 2, providing all member methods necessary and size in bytes of a particular data type.|
| `map_put`     | Insert an instance of the type specified into the appropriate bucket of a map, based on the key which <span style="font-weight: bold;color: blue;">must be the 1st argument with a total size of 8bytes</span>. A pointer to the arguments will be passed to the init function provided for the instance to be created. If load factor sur-passes a threshold a bucket is split and entries are distributed among the two. If there is already a mapping for that key, the value is replaced.|
| `map_get`     | Retrieve entry by key.            |
| `map_remove`  | Remove entry by key.      |
| `map_print`   | Print meta-data(max load_factor & capacity) of the map, as well as the content, which is a [vector](../vector_t/README.md) having a dynamic [doubly-linked-list](../list_t/README.md) for each bucket.|
| `map_display` | A different printing approach, neglecting the built-in printing methods of the internal data structures, using a much simpler display   .|
| `map_free`    | Free all resources allocated for this map, using the `map->destroy` to release each node, if provided on initialization. |

## Type methods

| Name              | Description                                                                                                           |
|------------------ |-----------------------------------------------------------------------------------------------------------------------|
| `clone(mandatory)`| Initialize an instance. This function will be called by map_put passing a `va_list` pointer to all arguments provided. <span style="font-weight: bold;color: blue;">Key should be of 8 bytes size and come first.</span>|
| `get_key(mandatory)`| This function extracts the key out of an instance of that specific type that the map stores, given a pointer to the it. |
| `cmp`             | Compare an instance with anything. It can be an id, another instance of this class or anything else.                          |
| `print`           | Display an instance of this type. Called by `map_print` for each map element.                                           |
| `destroy`         | De-allocate all resources used for a certain instance of this map. Those were allocated during `clone`.                |
