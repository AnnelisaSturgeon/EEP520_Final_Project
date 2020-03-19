# EEP520_Final_Project

ENVIRO: The multi-agent, multi-user, multi-everything simulator
===

Dockerhub Images
===

To start the docker image environment, do
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.1 bash
```
This will start a bash promt from which you can build new projects and run the enviro server.
