# GigaWidgets

This project allows simple widget-based construction and rendering of a GUI on an Arduino Giga with an attached Giga Display Shield.
It could easily be extended to other displays, but the first and foremost target is the aforementioned.

This project is a WIP and is not currently stable enough for use in other projects.

---

An emulator is available to test sketches and for rapid prototyping of this library. To emulate a sketch, run:

```
./emulate your_sketch.ino
```

Only the GigaWidgets library (and those it relies on) are currently supported for emulation.

`Serial` and `String` are also supported as basic wrappers for `std::cout` and `std::string`, respectively.

---

[The documentation](https://zacharywesterman.github.io/gigawidgets) is automatically generated with Doxygen.
