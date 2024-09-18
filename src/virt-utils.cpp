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

#include "virt-utils.hpp"

namespace vir
{

connect_ptr make_connect_ptr(virConnectPtr ptr)
{
	return connect_ptr(ptr, &virConnectClose);
}

connect_ptr make_connect_ptr(const char *name, virConnectAuthPtr auth, unsigned int flags)
{
	return make_connect_ptr(virConnectOpenAuth(name, auth, flags));
}

domain_ptr make_domain_ptr(virDomainPtr ptr)
{
	return domain_ptr(ptr, &virDomainFree);
}

domain_ptr make_domain_ptr(virConnectPtr conn, const char* name)
{
	return make_domain_ptr(virDomainLookupByName(conn, name));
}

}
