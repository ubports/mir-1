/*
 * Copyright © 2018 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#ifndef MIRAL_LAUNCH_APP_H
#define MIRAL_LAUNCH_APP_H

#include <mir/optional_value.h>

#include <string>
#include <vector>

namespace miral
{
void launch_app(std::vector<std::string> const& app,
                mir::optional_value<std::string> const& wayland_display,
                mir::optional_value<std::string> const& mir_socket,
                mir::optional_value<std::string> const& x11_display);
}

#endif //MIRAL_LAUNCH_APP_H
