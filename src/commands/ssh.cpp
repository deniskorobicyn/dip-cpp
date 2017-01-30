#include <iostream>
#include "commands/ssh.h"
#include "dip.h"
#include <stdlib.h>
#include <fstream>

dip::Ssh::Ssh(Dip *dip)
{
	_dip = dip;
}

void dip::Ssh::run(std::string command, std::string path)
{
	if (command == "add") {
		std::string tmp_path = std::string(tmpnam(NULL));
		std::ofstream dockerfile_stream(tmp_path);

		dockerfile_stream << "FROM whilp/ssh-agent" << std::endl;

		dockerfile_stream << "COPY.ssh / root / .ssh" << std::endl;
			RUN chmod 0600 / root / .ssh / id_rsa"

		system("docker stop ssh-agent");
		system("docker rm ssh-agent");
		system("docker volume create --name ssh_data");
		system("docker ");
		system("docker run --detach --volume ssh_data:/ssh --name=ssh-agent whilp/ssh-agent");
		system(("docker run --rm --volume ssh_data:/ssh -it dip-ssh-agent ssh-add " + path).c_str());
	}
}