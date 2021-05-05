let
  pkgs = import <nixpkgs> {} ;
in pkgs.stdenv.mkDerivation {
  name = "povtool" ;
  src = ./.;
  configureFlags=["COMPILED_BY=tom@rebelliondefense.com"];
  enableParallelBuilding=true;
  installPhase = ''
    install -D -m755 unix/povray $out/bin/povray
    '';
  # targetPkgs = pkgs: with pkgs; [
    # pkgs.glibc.static
    # pkgs.zlib.static
    # pkgs.libffi
    # pkgs.libtool
    # pkgs.musl
    # pkgs.gcc
  # ] ;
}
