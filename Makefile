BUILD:=./build

CFLAGS:= -m32 # 32 位的程序
CFLAGS+= -masm=intel
CFLAGS+= -fno-builtin	# 不需要 gcc 内置函数
CFLAGS+= -nostdinc		# 不需要标准头文件
CFLAGS+= -fno-pic		# 不需要位置无关的代码  position independent code
CFLAGS+= -fno-pie		# 不需要位置无关的可执行程序 position independent executable
CFLAGS+= -nostdlib		# 不需要标准库
CFLAGS+= -fno-stack-protector	# 不需要栈保护
CFLAGS:=$(strip ${CFLAGS})

DEBUG:= -g

HD_IMG_NAME:= "hd.img"

all: ${BUILD}/boot/boot.o ${BUILD}/boot/setup.o ${BUILD}/system.bin
	$(shell rm -rf $(HD_IMG_NAME))
	$(shell rm -rf hd.img.lock)
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(HD_IMG_NAME)
	dd if=${BUILD}/boot/boot.o of=$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=${BUILD}/boot/setup.o of=$(HD_IMG_NAME) bs=512 seek=1 count=2 conv=notrunc
	dd if=${BUILD}/system.bin of=$(HD_IMG_NAME) bs=512 seek=3 count=60 conv=notrunc

${BUILD}/system.bin: ${BUILD}/kernel.bin
	objcopy -O binary ${BUILD}/kernel.bin ${BUILD}/system.bin
	nm ${BUILD}/kernel.bin | sort > ${BUILD}/system.map

${BUILD}/kernel.bin: ${BUILD}/boot/head.o \
	${BUILD}/init/main.o
	ld -m elf_i386 $^ -o $@ -Ttext 0x10000

${BUILD}/init/main.o: oskernel/init/main.c
	$(shell mkdir -p ${BUILD}/init)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

${BUILD}/boot/head.o: oskernel/boot/head.asm
	nasm -f elf32 -g $< -o $@

${BUILD}/boot/%.o: oskernel/boot/%.asm
	$(shell mkdir -p ${BUILD}/boot)
	nasm $< -o $@

clean:
	$(shell rm -rf ${BUILD})
	$(shell rm -rf hd.img)

bochs: all
	bochs -q -f bochsrc

qemug: all
	qemu-system-i386 \
    	-m 32M \
    	-boot c \
    	-hda ./hd.img \
    	-s -S
	#qemu-system-x86_64 -m 32M -hda hd.img -S -s
	# -m 32M	虚拟机内存32M
	# -S 		启动后暂停服务
	# -s		开启调试选项 -gdb tcp::1234 的缩写

qemu: all
	qemu-system-i386 \
    -m 32M \
    -boot c \
    -hda ./hd.img

# 增加VM Virtual Box使用的虚拟机
vmdk: $(BUILD)/master.vmdk

$(BUILD)/master.vmdk: hd.img
	qemu-img convert -O vmdk $< $@