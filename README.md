# psymandl
Psychedelic Mandelbrot on PC DOS/MS-DOS.
You can download the `EXE` file from [itch.io](https://xms0g.itch.io/psymandl).

<img src="RES/psymandl.gif" alt="image" width="700" height="auto">

## Prerequisites
- **Turbo C++** (`TCC.EXE`) version 3.0 or later  
- **Turbo Assembler** (`TASM.EXE`) version 4.1 or later  
- **Turbo Linker** (`TLINK.EXE`) version 5.0 or later  
- **DOSBox** emulator or a real MS-DOS-compatible computer

## Building
```bash
C:\>MAKE.EXE
```
or
```bash
C:\>TASM /ml VGA.ASM
C:\>TASM /ml IO.ASM
C:\>TCC.EXE -oKEYBRD.OBJ -c KEYBRD.C
C:\>TCC.EXE PSYMANDL.C VGA.OBJ IO.OBJ KEYBRD.OBJ
```

## Run
```bash
C:\>PSYMANDL.EXE
```

## License
This project is licensed under the MIT License. See the LICENSE file for details.
