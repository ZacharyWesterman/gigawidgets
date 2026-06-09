# GigaWidgets

This project allows simple widget-based construction and rendering of a GUI on an Arduino Giga with an attached Giga Display Shield.
It could easily be extended to other displays, but the first and foremost target is the aforementioned.

This project is a WIP and is not currently stable enough for use in other projects.

## Requirements

### Emulation requirements
Emulation is only *officially* supported on Linux. If you can get it running on Windows, power to you!

- `rsync`
- A C++ compiler (if not `g++`, you'll have to tweak `emulate` to add the `CC=<your_compiler>` flag to the `make command`)

### Real hardware upload requirements
These are also required when emulating.

- The "Arduino Community Edition" VS Code extension, if uploading with VS Code.
- The following Arduino libraries are required:
  - `Arduino_GigaDisplayTouch`
  - `Arduino_GigaDisplay_GFX`
- The following Arduino libraries are optional, but recommended. They are enabled by default, but you can disable whichever formats you don't want to support by editing `src/ui/core/renderable/image_file/<FILE_FORMAT>.hpp`.
  - `JPEGDEC`
  - `BMPdec`
    - **WARNING:** Only non-interlaced PNG images are supported. Interlaced PNG will not render correctly!

---

An emulator is available to test sketches and for rapid prototyping of this library. To emulate a sketch, run:

```
./emulate your_sketch.ino
```

Only the GigaWidgets library (and those it relies on) are currently supported for emulation.

`Serial` and `String` are also supported as basic wrappers for `std::cout` and `std::string`, respectively.

**Warning:** If you used the emulator, it's a good idea to run `./emulate --wipe` before uploading,
to prevent emulator code from affecting the arduino code cache. It won't hurt anything to have it there,
but the action of uploading, then running the emulator is highly likely to trigger a *full rebuild* on
the next upload, which is very very slow.

---

[The documentation](https://zacharywesterman.github.io/gigawidgets) is automatically generated with Doxygen.

Be sure and check out [the examples](https://github.com/zacharywesterman/gigawidgets/treen/main/examples) for some simple UI examples.
