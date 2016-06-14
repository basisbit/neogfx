// popup_menu.hpp
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
#include "window.hpp"
#include "i_menu.hpp"
#include "vertical_layout.hpp"

namespace neogfx
{
	class popup_menu : public window
	{
	public:
		popup_menu(const point& aPosition, i_menu& aMenu);
		popup_menu(i_widget& aParent, const point& aPosition, i_menu& aMenu);
		~popup_menu();
	public:
		virtual void resized();
	public:
		virtual bool can_dismiss(const i_widget* aClickedWidget) const;
	public:
		virtual neogfx::size_policy size_policy() const;	
		virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
		virtual size maximum_size(const optional_size& aAvailableSpace = optional_size()) const;
	public:
		virtual colour background_colour() const;
	public:
		virtual void set_capture();
	public:
		virtual bool key_pressed(scan_code_e aScanCode, key_code_e aKeyCode, key_modifiers_e aKeyModifiers);
	public:
		i_menu& menu() const;
	private:
		void init();
		void close_sub_menu();
	private:
		i_widget* iParentWidget;
		i_menu& iMenu;
		vertical_layout iLayout;
		std::unique_ptr<popup_menu> iOpenSubMenu;
		bool iOpeningSubMenu;
	};
}