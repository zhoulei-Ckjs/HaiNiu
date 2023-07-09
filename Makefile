BUILD:=./build

HD_IMG_NAME:= "hd.img"

all: ${BUILD}/boot/boot.o ${BUILD}/boot/setup.o
	$(shell rm -rf $(HD_IMG_NAME))
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(HD_IMG_NAME)
	dd if=${BUILD}/boot/boot.o of=$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=${BUILD}/boot/setup.o of=$(HD_IMG_NAME) bs=512 seek=1 count=2 conv=notrunc

${BUILD}/boot/%.o: oskernel/boot/%.asm
	$(shell mkdir -p ${BUILD}/boot)
	nasm $< -o $@

clean:
	$(shell rm -rf ${BUILD})

bochs: all
	bochs -q -f bochsrc

qemug: all
	qemu-system-x86_64 -m 32M -hda hd.img -S -s
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