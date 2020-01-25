# bmap_t API

## Description

An array of bits, supporting basic operations.

## Methods Summary

| Name          | Description                                                                                                                      |
|---------------|----------------------------------------------------------|
| `bmap_init`   | Initialize a bit-map allocating enough space to hold the given number of bits.|
| `bmap_set`    | Set a bit to 1 by index.                                 |
| `bmap_reset`  | Reset a bit to 0 by index.                               |
| `bmap_toggle` | Toggle a bit(from 0 to 1 and vice-versa) by index.       |
| `bmap_get`    | Get a bit from the map by index.                         |
| `bmap_print`  | Display the bit-map bit-by-bit.                          |
| `bmap_free`   | Free all resources allocated for this bit-map's payload. |
