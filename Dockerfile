FROM ubuntu:22.04

# update apt-get
RUN apt-get update -y && apt-get upgrade -y

#install deps
RUN apt-get install ruby valgrind cppcheck git vim dos2unix build-essential -y
WORKDIR /app
ENTRYPOINT ["/app/run.sh"]