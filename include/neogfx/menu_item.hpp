// menu_item.hpp
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
#include "i_menu_item.hpp"

namespace neogfx
{
	class i_menu;

	class menu_item : public i_menu_item
	{
	private:
		typedef i_action* action_pointer;
		typedef std::shared_ptr<i_menu> menu_pointer;
		typedef neolib::variant<action_pointer, menu_pointer> contents;
	public:
		menu_item(i_action& aAction);
		menu_item(i_menu& aSubMenu);
		menu_item(std::shared_ptr<i_menu> aSubMenu);
	public:
		virtual type_e type() const;
		virtual const i_action& action() const;
		virtual i_action& action();
		virtual const i_menu& sub_menu() const;
		virtual i_menu& sub_menu();
	public:
		virtual bool availabie() const;
	private:
		contents iContents;
	};
}