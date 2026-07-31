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
  ]
  # IDF.py — available only when entering via flake.nix (nix develop / direnv),
  # where the `esp-dev` input is defined. `devenv up` (CLI) does not need it.
  ++ lib.optionals (inputs ? esp-dev) [
    inputs.esp-dev.packages.${pkgs.system}.esp-idf-full
  ];

  # https://devenv.sh/languages/
  languages.c.enable = true;

  languages.python.enable = true;

  # https://devenv.sh/processes/
  # Starts the IOTstack services (Grafana, InfluxDB, Node-RED, Mosquitto, Portainer)
  # together with `devenv up`. Requires Docker to be running on the host.
  processes.docker-services.exec = "docker compose -f docker-services/docker-compose.yml up";

  # See full reference at https://devenv.sh/reference/options/
}
