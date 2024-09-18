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

//https://hannes.hauswedell.net/post/2017/12/09/fmv/
#if defined(__x86_64__)
[[gnu::target_clones("default,arch=x86-64-v4")]]
#endif
void f()
{
	std::cout << "Hello\n";
}

int main()
{
	f();
	return 0;
}
