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

#pragma once

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#include <cstdlib>
#include <memory>

namespace vir
{

#define VIRT_CHECK(x) { \
	if(!(x)) { \
		fprintf(stderr, "%s\n", virGetLastErrorMessage()); \
		exit(EXIT_FAILURE); \
	} \
}

using connect_ptr = std::unique_ptr<virConnect, decltype(&virConnectClose)>;
using domain_ptr = std::unique_ptr<virDomain, decltype(&virDomainFree)>;

connect_ptr make_connect_ptr(virConnectPtr ptr = nullptr);
connect_ptr make_connect_ptr(const char *name, virConnectAuthPtr auth, unsigned int flags);

domain_ptr make_domain_ptr(virDomainPtr ptr = nullptr);
domain_ptr make_domain_ptr(virConnectPtr conn, const char* name);

};
