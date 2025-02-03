## Run the VM
1. Run with Qemu. (keep inline, new lines does not work in windows terminal)
   - Create virtual disk - 'qcow2', 'raw' or other format supported by Qemu (35 GB atleast).

   ```sh
   qemu-system-x86_64
   -accel whpx
   -drive file='Ubuntu Server.qcow2,format=qcow2',if=virtio,discard=unmap
   -cdrom ubuntu-server.iso
   -m 8G
   -smp 10
   -netdev user,id=net0,hostfwd=tcp::2222-:22
   -device virtio-net,netdev=net0
   -vga virtio
   -boot order=c
   -nographic
   -monitor telnet:127.0.0.1:4444,server,nowait
   ```

2. SSH into the VM. (enable SSH via optional-features)

   ```sh
   ssh -p 2222 username@localhost
   ```

## Setup Linux Kernel
1. Clone the Linux kernel.

   ```sh
   git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/torvalds/linux
   ```

   | I thought it would be faster to download from google rather than github —less traffic, maybe? Who knows? :p

2. Copy the source code (optional, to avoid re-downloading if something is misconfigured badly).

   ```sh
   mv linux linux-base
   cp -r linux-base linux
   cd linux
   ```

3. Uncomment the `deb-src` lines and update package lists.

   ```sh
   vim /etc/apt/sources.list
   sudo apt update
   ```

   On Ubuntu, edit `/etc/apt/sources.list.d/ubuntu.sources` instead:

   ```sh
   vim /etc/apt/sources.list.d/ubuntu.sources
   ```

4. Enable source repositories (if missing).

   ```sh
   vi /etc/apt/sources.list.d/ubuntu.sources
   ```

   Add the following if it's missing:

   ```
   Types: deb deb-src
   URIs: http://archive.ubuntu.com/ubuntu
   Suites: noble noble-updates noble-security
   Components: main restricted universe multiverse
   ```

   Update package lists and install kernel build deps:

   ```sh
   sudo apt update
   sudo apt build-dep linux
   ```

5. Install additional deps.

   ```sh
   sudo apt install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libudev-dev libpci-dev libiberty-dev autoconf llvm
   ```

6. Use the current kernel's configuration as a starting point.

   ```sh
   cat /boot/config-$(uname -r) > .config
   ```

7. Configure the kernel using `menuconfig`.

   ```sh
   make menuconfig
   ```

   - Navigate to **General setup →**
   - Select **<Save>** to save the configuration.
   - Select **<Exit>**.

   **Remove Debian-specific configurations:**

   - Go to **Cryptographic API** → **Certificates for signature checking**.
   - Remove `debian/canonical-certs.pem` from:
     ```
     (debian/canonical-certs.pem) Additional X.509 keys for default system keyring
     ```
     Change it to:
     ```
     () Additional X.509 keys for default system keyring
     ```
   - Remove `debian/canonical-revoked-certs.pem` from:

     ```
     (debian/canonical-revoked-certs.pem) X.509 certificates to be preloaded into the system blacklist keyring
     ```

     Change it to:

     ```
     () X.509 certificates to be preloaded into the system blacklist keyring
     ```

   - **Save** and **Exit**.

8. Build the kernel.

   ```sh
   make -j$(nproc)
   ```

   - `-j$(nproc)`: Uses all CPU cores for faster compilation.

   Install stripped kernel modules:

   ```sh
   sudo make INSTALL_MOD_STRIP=1 modules_install
   ```

9. Buildroot (optional)
   - Create 'ext2' image with buildroot.

10. Run the kernel in VM.

   ```sh
   qemu-system-x86_64 -kernel linux/arch/x86/boot/bzImage -drive file=buildroot/output/images/rootfs.ext2,format=raw -append "root=/dev/sda console=ttyS0" -nographic -no-reboot
   ```
