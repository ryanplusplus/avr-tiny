# avr-tiny
## Setup
Build from source:
- https://github.com/facchinm/avrdude
- https://github.com/Florin-Popescu/avarice/

```shell
make -f target.mk install_toolchain
```

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
