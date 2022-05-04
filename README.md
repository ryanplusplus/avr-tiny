# avr-tiny
## Setup
Install toolchain with `apt`:
```shell
sudo apt install avr-libc gdb-avr gcc-avr binutils-avr
```

Build from source:
- https://github.com/facchinm/avrdude
- https://github.com/Florin-Popescu/avarice/

## Use
### Compile
```shell
make -f target.mk
```

### Clean
```shell
make -f target.mk clean
```

### Erase via selected tool
```shell
make -f target.mk erase
```

### Flash via selected tool
```shell
make -f target.mk upload
```
