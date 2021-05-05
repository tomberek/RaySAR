let
  pkgs = import <nixpkgs> {} ;
in pkgs.buildFHSUserEnv {
  name = "fhs" ;
  targetPkgs = pkgs: with pkgs; [
    pkgs.glibc.static
    pkgs.zlib.static
    pkgs.libffi
    pkgs.libtool
    pkgs.musl
    pkgs.gcc
  ] ;
}
