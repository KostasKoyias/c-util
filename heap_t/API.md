# heap_t API

## Methods Summary

### Member Methods

| Name          | Description                                                                                                                      |
|---------------|----------------------------------------------------------------------------------------------------------------------------------|
| `heap_init`   | Initialize a heap, providing all member methods necessary for a specific data type.                                              |
| `heap_push`   | Insert an instance of the type specified to the heap. Arguments will be passed to the init function provided. |
| `heap_isempty`| Return 1 if heap is empty or else 0.                                                                          |
| `heap_best`   | Retrieve, without removing though, the root element of this heap.                                             |
| `heap_pop`    | Remove the root element of this heap.                                                                         |
| `heap_sort`   | Sorts elements of the heap by continuously swapping the root with the last element and retaining the heap property right after. |
| `heap_free`   | Free all resources allocated for this heap, using the `heap->destroy` if provided.|
| `hsort`       | A heap_sort wrapper, matching `stdlib.qsort` prototype, sorting an array in-place in O(nlogn) time. No need to initialize a heap before-hand.|

### Type methods

| Name             | Description                                                                                                                                                  |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `init(required)` | Initialize an instance. This function will be get a pointer to the arguments passed to `heap_insert`.                                                         |
| `cmp(required)`  | Compare two instances of the data type the nodes hold. Used to restore the heap property. |
| `destroy`        | De-allocate all resources used for a certain instance of this heap. Those were allocated during `init`.                                                      |
