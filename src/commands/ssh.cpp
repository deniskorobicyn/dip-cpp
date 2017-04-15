#include <iostream>
#include "commands/ssh.h"
#include "dip.h"
#include <stdlib.h>
#include <fstream>
#include <filesystem>

dip::Ssh::Ssh(Dip *dip)
{
	_dip = dip;
}

void dip::Ssh::run(std::string command, std::string path)
{
	if ("add" == command) {
#ifdef WIN32

		system("docker volume create --name ssh_data");
		system("docker volume create --name ssh_user_data");
		system("docker run -d -v ssh_data:/ssh -v ssh_user_data:/root/.ssh --name=ssh-agent  whilp/ssh-agent");
		system(("docker run --rm -v ssh_data:/ssh -v ssh_user_data:/root/.ssh -v " + path + ":/invalid-ssh whilp/ssh-agent cp /invalid-ssh/* /root/.ssh").c_str());
		system("docker run --rm -v ssh_data:/ssh -v ssh_user_data:/root/.ssh whilp/ssh-agent chmod 0600 /root/.ssh/id_rsa");
		system("docker run --rm -v ssh_data:/ssh -v ssh_user_data:/root/.ssh -it whilp/ssh-agent ssh-add");
#else
		system(("docker build -t ssh-agent-image-tmp -f " + tmp_path + " " + tmp_path.substr(0, tmp_path.find_last_of('\\'))).c_str());
		system("docker volume create --name ssh_data");
		system("docker run --detach --volume ssh_data:/ssh --name=ssh-agent whilp/ssh-agent");
		system("docker run --rm --volume ssh_data:/ssh -v " + path + ":/root/.ssh/id_rsa -it whilp/ssh-agent ssh-add");
#endif // WIN32
	}
	else {
		if ("down" == command) {
			system("docker stop ssh-agent");
			system("docker rm ssh-agent");
			system("docker volume rm ssh_data");
#ifdef WIN32
			system("docker volume rm ssh_user_data");
#endif
		}
	}
}