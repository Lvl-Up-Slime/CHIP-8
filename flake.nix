{
  description = "CHIP-8 Bin";

  outputs = { self, nixpkgs }: {
    devShells.default = nixpkgs.lib.mkShell {
      buildInputs = [
        nixpkgs.SDL3
        nixpkgs.pkg-config
        nixpkgs.gcc
        nixpkgs.clang
        nixpkgs.gdb
      ];
    };
  };
}

