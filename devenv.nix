{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:
{
  env = {
    LANG = "C.UTF-8";
    LC_ALL = "C.UTF-8";
  };
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
