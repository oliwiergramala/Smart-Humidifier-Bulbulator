# reference argument - omitted defaults to latest
ARG DOCKERHUB_TAG=latest

# Download base image
FROM nodered/node-red:${DOCKERHUB_TAG}

# reference argument - omitted defaults to null
ARG EXTRA_PACKAGES

# default user is node-red - need to be root to install packages
USER root

# install packages
RUN apk add --no-cache eudev-dev ${EXTRA_PACKAGES}

# switch back to default user
USER node-red

# add-on nodes follow
