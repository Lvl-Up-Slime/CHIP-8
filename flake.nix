{
  description = "CHIP-8 dev environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs }: {
    devShells.x86_64-linux.default = let
      pkgs = nixpkgs.legacyPackages.x86_64-linux;
    in
    pkgs.mkShell {
      buildInputs = [
        pkgs.bear
        pkgs.gcc
        pkgs.pkg-config
        pkgs.sdl3
        pkgs.fish
      ];
    };
  };
}
