## MIT6.S081 Operating Systems Engineering

### 配置开发环境 Ubuntu 20.04.6 LTS
``` bash
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 
sudo apt-get remove qemu-system-misc
sudo apt-get install qemu-system-misc=1:4.2-3ubuntu6
```

### 获取实验代码
```bash
git clone https://github.com/Staeni92/MIT6.S081.git
```
### 编译执行测试xv6
```bash
# 编译清理
make clean

# 编译xv6并qemu仿真
# 常用调试命令：退出qemu ctrl-a + x 切换qemu控制台和监视器 ctrl-a + c 查看所有进程信息 ctrl-p
make qemu

# 执行测试用例
make grade
```