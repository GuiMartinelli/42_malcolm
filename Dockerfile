FROM ubuntu

WORKDIR /home
COPY . .

RUN apt-get update && apt-get install -y build-essential make git
