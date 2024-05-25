# Naming Convention for Function Pointer Types and Variables
This document covers the naming convention for function pointer type definitions and related

## Naming Convention for Function Pointer Type Definitions
Function Pointer types, as most names in Muzzle, should begin with the `mz_` prefix. Alongside this prefix,
function pointer types should end with `_fn`. Ensure it is no other abbrivation or shorthand for `function`.
`_fun`, `_func`, `_function`, `_fptr`, etc... are not acceptable to be used instead of `_fn`

## Naming Convention for Function Pointer Variables
The naming convention for function pointer variables are more loose than the type definitions. If in the global
namespace, begin with the `mz_` prefix. For all namespaces, the suffix of `_func` is optional and up to
personal discretion. Consider how the clear the fact that the variable is a function pointer is with and
without the `_func` suffix. **HOWEVER,** just because it is optional does not mean:

 1. It is not up to review and change by contributors
 2. You may use a suffix other than `_func`.

## Naming Convention Reminder
None of these naming conventions are necessarily final and the project is open to further discussion,
critique, and recommendations. Remember to follow our [Code of Conduct](https://github.com/PikoStudios/Muzzle/blob/main/CODE_OF_CONDUCT.md)
and remain civil and provide constructive criticism.

#### Naming Convention Discussion Page
As of current, the Github Discussion Page for the Naming Convention is located [here](https://github.com/PikoStudios/Muzzle/discussions/41)
