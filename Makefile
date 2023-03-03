# obj-m += hello_driver.o
obj-m += hello_argument.o

KDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean