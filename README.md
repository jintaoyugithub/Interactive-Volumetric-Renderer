# Interactive Volumetric Renderer

## Quick Start

### Dependices

- [bgfx.cmake](https://github.com/bkaradzic/bgfx)

- [glfw](https://github.com/glfw/glfw)

- [glm](https://github.com/g-truc/glm)

## Build

## Quick Q&A

1. Undefined symbol _main_

Place the definition following in the end of your main file:

```cpp
int _main_(int _argc, char** _argv) {return 0;};
```

2. Why link lib example-common?

We use the example framework of bgfx as it abstract the input callback, window management and other useful utilities for us. Therefore it's necessary to link example-common lib.


