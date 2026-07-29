{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:
{
  # https://devenv.sh/packages/
  packages = [
    pkgs.cmake
    pkgs.ninja
    pkgs.go-task
    inputs.esp-dev.packages.${pkgs.system}.esp-idf-full
  ];

  # https://devenv.sh/languages/
  languages.c.enable = true;

  languages.python.enable = true; 

  # See full reference at https://devenv.sh/reference/options/
}
