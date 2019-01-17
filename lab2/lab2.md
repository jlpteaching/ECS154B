

### How to interact with memory

There is only one memory in the system (e.g., you are implementing a [Von Neumann architecture](https://en.wikipedia.org/wiki/Von_Neumann_architecture), not a [Harvard architecture](https://en.wikipedia.org/wiki/Harvard_architecture)).
However, to simplify your design, we have provided you with two different *ports* to memory, an instruction port and a data port.
These ports are hidden in the `CoreIO` bundle.
To access the instruction memory, you can use the following code inside your CPU module (e.g., in `cpu.scala`).

```
io.imem.address

io.imem.instructions
```

Similarly, for the data part, you can use the following code inside your CPU module (e.g., in `cpu.scala`).

```
io.dmem.address
io.dmem.writedata
io.dmem.memread
io.dmem.memwrite
io.dmem.maskmode
io.dmem.sext

io.dmem.readdata
```

If you look in the file `src/main/scala/components/memory.scala` you will see two special bundles: `IMemIO` and `DMemIO`.
In the `SingleCycleCPU`, `io.imem` and `io.dmem` are instantiations of these two bundles, respectively.
