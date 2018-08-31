/*
 * Copyright © 2018 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3,
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
 * Authored By: William Wold <william.wold@canonical.com>
 */

#include "event.h"

Event::Event(xmlpp::Element const& node, std::string const& class_name, bool is_global, int opcode)
    : Method{node, class_name, is_global},
      opcode{opcode}
{
}

// TODO: Decide whether to resolve wl_resource* to wrapped types (ie: Region, Surface, etc).
Emitter Event::prototype() const
{
    return {"void send_", name, "_event(", mir_args(), ");"};
}

// TODO: Decide whether to resolve wl_resource* to wrapped types (ie: Region, Surface, etc).
Emitter Event::impl() const
{
    return {"void mfw::", class_name, "::send_", name, "_event(", mir_args(), ")",
        Block{
            mir2wl_converters(),
            {"wl_resource_post_event(", wl_call_args(), ");"},
        }
    };
}

Emitter Event::mir2wl_converters() const
{
    std::vector<Emitter> thunk_converters;
    for (auto const& arg : arguments)
    {
        if (auto converter = arg.converter())
            thunk_converters.push_back(converter.value());
    }
    return Lines{thunk_converters};
}

Emitter Event::mir_args() const
{
    std::vector<Emitter> mir_args;
    if (is_global)
    {
        mir_args.push_back("struct wl_resource* resource");
    }
    for (auto& i : arguments)
    {
        mir_args.push_back(i.mir_prototype());
    }
    return List{mir_args, ", "};
}

Emitter Event::wl_call_args() const
{
    std::vector<Emitter> call_args{"resource", std::to_string(opcode)};
    for (auto& arg : arguments)
        call_args.push_back(arg.wl_call_fragment());
    return List{call_args, ", "};
}
