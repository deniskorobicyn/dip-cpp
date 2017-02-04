#include "commands/dnsdock.h"
#include "dip.h"

dip::Dnsdock::Dnsdock(dip::Dip *dip)
{
	_dip = dip;
}

void dip::Dnsdock::run(std::string args)
{
	if (0 == args.compare(0, 2, "up")) {
		system("docker run --detach --volume /var/run/docker.sock:/var/run/docker.sock:ro --restart always --publish 53:53/udp --name=dnsdock aacebedo/dnsdock:latest-amd64");
	}

	if (0 == args.compare(0, 4, "down")) {
		system("docker stop dnsdock");
		system("docker rm -v dnsdock");
	}
}