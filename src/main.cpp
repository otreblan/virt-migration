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
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#include "virt-utils.hpp"

int main()
{
	auto source = vir::make_connect_ptr("qemu:///system", virConnectAuthPtrDefault, 0);

	VIRT_CHECK(source);

	auto domain = vir::make_domain_ptr(source.get(), "aaaa");

	VIRT_CHECK(domain);

	return EXIT_SUCCESS;
}
