# Build the Psion specific stuff

AS86	=as86 -0
LD86	=ld86 -0

AS	=as
LD	=ld86
LDFLAGS	=-0 -i
CC	=bcc

#########################################################################

AARCHIVES = kernel/akernel.a lib/lib86.a mm/mm.a

ARCHIVES := $(ARCHIVES) $(ARCH_DIR)/kernel/akernel.a \
	$(ARCH_DIR)/lib/lib86.a \
	$(ARCH_DIR)/mm/mm.a

ADRIVERS = drivers/char/chr_drv.a drivers/block/blk_drv.a

DRIVERS := $(DRIVERS) $(ARCH_DIR)/drivers/char/chr_drv.a \
	$(ARCH_DIR)/drivers/block/blk_drv.a

#########################################################################
# general construction rules

.c.s:
	$(CC) $(CFLAGS) \
	-0 -nostdinc -Iinclude -S -o $*.s $<
.s.o:
	$(AS) -0 -I$(MT_DIR)/include -c -o $*.o $<
.S.s:
	gcc -E -traditional -o $*.s $<
.c.o:
	$(CC) $(CFLAGS) \
	2 -nostdinc -Iinclude -c -o $*.o $<

#########################################################################
# arch tools
.PHONY: boot/system

boot/setup: boot/setup.S
	gcc -E -traditional -I$(TOPDIR)/include/ -o boot/setup.s boot/setup.S
	$(AS86) -o boot/setup.o boot/setup.s
	$(LD86) -s -o boot/setup -M boot/setup.o > Setup.map

boot/bootsect: boot/bootsect.S
	gcc -E -traditional -I$(TOPDIR)/include/ -o boot/bootsect.s boot/bootsect.S
	$(AS86) -0 -o boot/bootsect.o boot/bootsect.s
	$(LD86) -0 -s -o boot/bootsect -M boot/bootsect.o > Boot.map

boot/crt1.o: boot/crt1.c

boot/crt0.o: boot/crt0.s
	$(AS86) -0 -o boot/crt0.o boot/crt0.s

tools/build: tools/build.c
	gcc -I $(TOPDIR)/include -o tools/build tools/build.c

boot/system: $(AARCHIVES) $(ADRIVERS) boot/crt1.o boot/crt0.o
	(cd ../.. ; $(LD) $(LDFLAGS) $(ARCH_DIR)/boot/crt0.o \
		$(ARCH_DIR)/boot/crt1.o \
		init/main.o \
		$(ARCHIVES) \
		$(DRIVERS) \
		-t -M -o $(ARCH_DIR)/boot/system > System.map)
	
ifeq ($(CONFIG_286PMODE), y)

Image: boot/bootsect boot/setup 286pmode/pmode286 boot/system tools/build
	tools/build boot/bootsect boot/setup 286pmode/pmode286 boot/system $(ROOT_DEV) > Image
	sync

else

Image: boot/bootsect boot/setup boot/system tools/build
	tools/build boot/bootsect boot/setup boot/system $(ROOT_DEV) > boot/Image
	sync

endif

boot: Image
	dd if=boot/Image of=/dev/fd0 bs=8192

disk: boot

#########################################################################
# library rules
# Build archives and add them to the list of things to link into kernel image
.PHONY: kernel/akernel.a lib/lib86.a mm/mm.a drivers/char/chr_drv.a \
	drivers/block/blk_drv.a 286pmode/pmode286

kernel/akernel.a:
	(cd kernel; make)

lib/lib86.a:
	(cd lib; make)

mm/mm.a:
	(cd mm; make)

drivers/char/chr_drv.a:
	(cd drivers/char; make)

drivers/block/blk_drv.a:
	(cd drivers/block; make)

286pmode/pmode286:
	(cd 286pmode; make)

#########################################################################
# misc
clean:
	rm -f boot/bootsect boot/setup boot/bootsect.s boot/setup.s
	rm -f boot/*~ boot/*.o boot/system boot/Image
	rm -f tools/*~ tools/*.o tools/build
	(cd kernel; make clean)
	(cd lib; make clean)
	(cd mm; make clean)
	(cd drivers/block; make clean)
	(cd drivers/char; make clean)
	(cd 286pmode; make clean)

dep:
	(cd kernel; make dep)
	(cd lib; make dep)
	(cd mm; make dep)
	(cd drivers/block; make dep)
	(cd drivers/char; make dep)
	(cd 286pmode; make dep)