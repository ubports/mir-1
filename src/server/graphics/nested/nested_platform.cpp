/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Eleni Maria Stea <elenimaria.stea@canonical.com>
 */

#include "mir/graphics/nested/nested_platform.h"
#include "mir_toolkit/mir_client_library.h"

#include <string.h>

#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace mg = mir::graphics;
namespace mgn = mir::graphics::nested;
namespace mo = mir::options;
namespace mc = mir::compositor;

static std::string host_socket;

mgn::NestedPlatform::NestedPlatform(std::string const& host,
                                    std::shared_ptr<mg::DisplayReport> const& display_report,
                                    std::shared_ptr<mg::NativePlatform> const& native_platform) :
    native_platform{native_platform},
    display_report{display_report},
    connection{0}
{
    host_socket = host;

    if (!(connection = mir_connect_sync(host_socket.c_str(), "nested_mir")))
        BOOST_THROW_EXCEPTION(std::runtime_error("Nested Mir Platform: Failed to connect!\n"));

    if (!mir_connection_is_valid(connection))
        BOOST_THROW_EXCEPTION(std::runtime_error("Nested Mir Platform: Invalid connection!\n"));

    if (!(strcmp(mir_connection_get_error_message(connection),"") == 0))
        BOOST_THROW_EXCEPTION(std::runtime_error("Nested Mir Platform: Errors occured!\n"));

    BOOST_THROW_EXCEPTION(std::runtime_error("Mir mgn::NestedPlatform::NestedPlatform constructor, established connection, host socket: " + host_socket));
}

std::shared_ptr<mc::GraphicBufferAllocator> mgn::NestedPlatform::create_buffer_allocator(
        std::shared_ptr<mg::BufferInitializer> const& /*buffer_initializer*/)
{
    BOOST_THROW_EXCEPTION(std::runtime_error("Mir mgn::NestedPlatform::create_buffer_allocator is not implemented yet!"));
    return 0;
}

std::shared_ptr<mg::Display> mgn::NestedPlatform::create_display(std::shared_ptr<mg::DisplayConfigurationPolicy> const& /*initial_conf_policy*/)
{
    BOOST_THROW_EXCEPTION(std::runtime_error("Mir mgn::NestedPlatform::create_display is not implemented yet!"));
    return 0;
}

std::shared_ptr<mg::PlatformIPCPackage> mgn::NestedPlatform::get_ipc_package()
{
    BOOST_THROW_EXCEPTION(std::runtime_error("Mir mgn::NestedPlatform::get_ipc_package is not implemented yet!"));
    return 0;
}

std::shared_ptr<mg::InternalClient> mgn::NestedPlatform::create_internal_client()
{
    BOOST_THROW_EXCEPTION(std::runtime_error("Mir mgn::NestedPlatform::create_internal_client is not implemented yet!"));
    return 0;
}


void mgn::NestedPlatform::fill_ipc_package(std::shared_ptr<compositor::BufferIPCPacker> const& /*packer*/,
                                        std::shared_ptr<Buffer> const& /*buffer*/) const
{
    BOOST_THROW_EXCEPTION(std::runtime_error("Mir method mgn::NestedPlatform::fill_ipc_package is not implemented yet!"));
}
