// infoware - C++ System information Library
//
// Written in 2016-2019 by nabijaczleweli <nabijaczleweli@gmail.com> and ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>


#include "../include/infoware/gpu.hpp"
#include "../include/infoware/version.hpp"
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, R"(F:\bc\monero\xmr\infoware\build\lib\Debug\infowared.lib)")
#else
#pragma comment(lib, R"(F:\bc\monero\xmr\infoware\build\lib\Release\infoware.lib)")
#endif

#pragma comment(lib, "version.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "DXGI.lib")

#include <jlib/util/space.h>

static const char* vendor_name(iware::gpu::vendor_t vendor) noexcept;


int main() {
	std::cout << "Infoware version " << iware::version << '\n';

	{
		const auto device_properties = iware::gpu::device_properties();
		std::cout << "\n"
		             "  Properties:\n";
		if(device_properties.empty())
			std::cout << "    No detection methods enabled\n";
		else
			for(auto i = 0u; i < device_properties.size(); ++i) {
				const auto& properties_of_device = device_properties[i];
				std::cout << "    Device #" << (i + 1) << ":\n"
				          << "      Vendor       : " << vendor_name(properties_of_device.vendor) << '\n'
				          << "      Name         : " << properties_of_device.name << '\n'
				          << "      RAM size     : " << jlib::human_readable_byte_count(properties_of_device.memory_size) << "\n"
				          << "      Cache size   : " << jlib::human_readable_byte_count(properties_of_device.cache_size) << "\n"
				          << "      Max frequency: " << properties_of_device.max_frequency << "Hz\n";
			}
	}

	std::cout << '\n';

	system("pause");
}


static const char* vendor_name(iware::gpu::vendor_t vendor) noexcept {
	switch(vendor) {
		case iware::gpu::vendor_t::intel:
			return "Intel";
		case iware::gpu::vendor_t::amd:
			return "AMD";
		case iware::gpu::vendor_t::nvidia:
			return "NVidia";
		case iware::gpu::vendor_t::microsoft:
			return "Microsoft";
		case iware::gpu::vendor_t::qualcomm:
			return "Qualcomm";
		default:
			return "Unknown";
	}
}
