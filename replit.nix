{ pkgs }: {
    deps = [
        pkgs.busybox
        pkgs.hexedit
        pkgs.nasm
        pkgs.qemu
        pkgs.cdrkit
        pkgs.multiStdenv
        pkgs.clang
    ];
}