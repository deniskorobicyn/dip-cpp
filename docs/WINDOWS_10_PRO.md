# Setup for Windows 10 Pro

1. Download latest [release](https://github.com/deniskorobicyn/dip-cpp/releases)
2. Add folder with dip.exe to PATH in system settings (Control Panel -> System -> Advanced System settings -> Environment Variables -> Add to System variable `Path` dip.exe folder)
3. Install docker 1.12.5 - [installer](https://download.docker.com/win/stable/1.12.5.9503/InstallDocker.msi)
4. Download docker-compose 1.10.0 from docker-compose repo - [link](https://github.com/docker/compose/releases/download/1.10.0/docker-compose-Windows-x86_64.exe)
5. Replace docker-compose.exe in docker installation folder (`%DOCKERPATH%\resources\bin\docker-compose.exe`)
6. Start dns `dip dns up`
7. Add `dns: ["172.17.0.1"]` to docker daemon config in docker settings and make sure you share you drive to docker in docker daemon settings
8. Execute in CMD as admin `route -p add 172.16.0.0 MASK 255.240.0.0 10.0.75.2`
9. Add custom DNS in network settings (Control Panel -> Network and Sharing center -> Change adapter settings -> Right clink on you network -> Properties ->  Internet Protocol Version 4 (TCP/IP4) -> Properties -> DNS -> add value `127.0.0.1`)
10. Done! Happy hacking!


If you want to use latest docker version (1.13.0), you'll requeired to run 

```
docker run --rm -ti --privileged --network=none --pid=host justincormack/nsenter1 bin/sh -c "iptables -A FORWARD -j ACCEPT"
```

on every reboot on docker daemon.
