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
    # Docker  
    pkgs.docker
    pkgs.docker-compose
    
    # Tools to build code
    pkgs.cmake
    pkgs.ninja
    pkgs.go-task
    
    # IDF.py 
    inputs.esp-dev.packages.${pkgs.system}.esp-idf-full
  ];

  # https://devenv.sh/languages/
  languages.c.enable = true;

  languages.python.enable = true; 

  # See full reference at https://devenv.sh/reference/options/
}
