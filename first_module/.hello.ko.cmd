cmd_/home/ubuntu/Device_deriver/first_module/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/ubuntu/Device_deriver/first_module/hello.ko /home/ubuntu/Device_deriver/first_module/hello.o /home/ubuntu/Device_deriver/first_module/hello.mod.o;  true
