// Libvirt migration
// Copyright © 2024 Otreblan
//
// virt-migration is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// virt-migration is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with virt-migration.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <string>

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#include "virt-utils.hpp"

void usage(int exit_code)
{
	std::cout << "virt-migration DOMAIN DIST_URI\n";

	exit(exit_code);
}

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		usage(EXIT_FAILURE);
	}

	std::string domain_name = argv[1];
	std::string dist_uri    = argv[2];

	auto source = vir::make_connect_ptr("qemu:///system", virConnectAuthPtrDefault, 0);

	VIRT_CHECK(source);

	auto domain = vir::make_domain_ptr(source.get(), domain_name.c_str());

	VIRT_CHECK(domain);

	virDomainMigrateToURI(domain.get(), dist_uri.c_str(),
		VIR_MIGRATE_LIVE |
		VIR_MIGRATE_PEER2PEER |
		//VIR_MIGRATE_TUNNELLED |
		VIR_MIGRATE_UNDEFINE_SOURCE |
		VIR_MIGRATE_PERSIST_DEST,
		nullptr, 0);

	return EXIT_SUCCESS;
}
