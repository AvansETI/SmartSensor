docker run -d --name smart-influxdb --restart always -p 8086:8086 \
       -v $PWD/data:/var/lib/influxdb2 \
       -v $PWD/config:/etc/influxdb2 \
       -e DOCKER_INFLUXDB_INIT_MODE=setup \
       -e DOCKER_INFLUXDB_INIT_USERNAME=xxxxxxxxx \
       -e DOCKER_INFLUXDB_INIT_PASSWORD=xxxxxxxxx \
       -e DOCKER_INFLUXDB_INIT_ORG=xxxx \
       -e DOCKER_INFLUXDB_INIT_BUCKET=nodedata \
       influxdb:latest
