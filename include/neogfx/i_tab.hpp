// i_tab.hpp
/*
neogfx C++ GUI Library
Copyright(C) 2016 Leigh Johnston

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "neogfx.hpp"
#include "event.hpp"
#include "i_widget.hpp"
#include "i_image.hpp"

namespace neogfx
{
	class i_tab_container;

	class i_tab
	{
	public:
		event<> selected;
		event<> deselected;
	public:
		virtual ~i_tab() {}
	public:
		virtual bool is_selected() const = 0;
		virtual bool is_deselected() const = 0;
		virtual void select() = 0;
		virtual const i_tab_container& container() const = 0;
		virtual i_tab_container& container() = 0;
	public:
		virtual const std::string& text() const = 0;
		virtual void set_text(const std::string& aText) = 0;
		virtual void set_image(const i_texture& aTexture) = 0;
		virtual void set_image(const i_image& aImage) = 0;
	};
}