
# 新建本地映像

```

grub-mkrescue /usr/lib/grub/x86_64-efi -o kernel.iso target/x86_64/iso

```

# 第一步:建立本地映像引导:

我们采用uefi引导的方式,



### UEFI 启动过程

EFI 启动过程如下：

- SEC（安全性）阶段：通电，内存未初始化，CPU 只能使用 Cache 来验证 CPU、芯片组和主机驱动；
- PEI（EFI前初始化）阶段：初始化一小部分低地址内存空间，CPU 开始使用此内存初始化CPU、芯片组 和主板，随后EFI驱动载入内存；
- DXE（驱动执行环境）阶段：此阶段内存、CPU（指CPU插槽上的物理CPU,非CPU核心）、PCI、USB、 SATA 和 Shell 都会被初始化；
- BDS（开机设备选择）阶段：此阶段用户可选择从检测到启动设备中选择启动设备；
- TSL（临时系统载入）阶段：此阶段将由启动设备上的系统接手正式进入操作系统， 若 BDS 阶段选择 UEFI Shell则会进入 UEFI 的简单命令行界面，可在此界面做简单维护和诊断。

### 启用 UEFI 的条件

- 电脑主板支持 UEFI；

  2010年后的主板基本都支持。

- 操作系统支持 UEFI；

  64位Windows基本都支持

- 磁盘具有 GUID 分区表（GPT）。

- 磁盘分区表中必须有 FAT 分区。

  特殊标志的 FAT 分区（即 ESP 分区，也叫 EFI 系统分区），该分区要作为第一个磁盘分区（进入系统会自动隐藏）。

- 可启动的 efi 文件，一般为 `\EFI\BOOT\BOOTx64.EFI`

  注，不同平台文件名可能不同。





