{ pkgs }: {
    deps = [
        pkgs.nasm
        pkgs.qemu
        pkgs.cdrkit
        pkgs.multiStdenv
        pkgs.clang
    ];
}