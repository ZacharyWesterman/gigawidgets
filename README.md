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
- The "Arduino Community Edition" VS Code extension, if uploading with VS Code.
- The following Arduino libraries:
  - `Arduino_GigaDisplayTouch`
  - `Arduino_GigaDisplay_GFX`

---

An emulator is available to test sketches and for rapid prototyping of this library. To emulate a sketch, run:

```
./emulate your_sketch.ino
```

Only the GigaWidgets library (and those it relies on) are currently supported for emulation.

`Serial` and `String` are also supported as basic wrappers for `std::cout` and `std::string`, respectively.

---

[The documentation](https://zacharywesterman.github.io/gigawidgets) is automatically generated with Doxygen.
