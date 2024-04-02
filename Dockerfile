FROM ubuntu

WORKDIR /home
COPY . ./ft_malcolm/

RUN apt-get update && apt-get install -y build-essential make

CMD exec /bin/bash -c "trap : TERM INT; sleep infinity & wait"
