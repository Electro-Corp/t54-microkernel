{ pkgs }: {
    deps = [
        pkgs.hexedit
        pkgs.nasm
        pkgs.qemu
        pkgs.cdrkit
        pkgs.multiStdenv
        pkgs.clang
    ];
}