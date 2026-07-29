{
  pkgs,
  lib,
  config,
  ...
}:
{
  # https://devenv.sh/packages/
  packages = [
    pkgs.esptool
    pkgs.cargo-espmonitor
    pkgs.go-task
  ];

  # https://devenv.sh/languages/
  languages.c.enable = true;

  # See full reference at https://devenv.sh/reference/options/
}
