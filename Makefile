# obj-m += hello_driver.o
# obj-m += hello_argument.o
# obj-m += static_major_minor.o
obj-m += dynamic_major_minor.o

KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean