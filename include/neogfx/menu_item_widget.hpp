// menu_item_widget.hpp
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
#include "widget.hpp"
#include "horizontal_layout.hpp"
#include "text_widget.hpp"
#include "image_widget.hpp"
#include "spacer.hpp"
#include "i_menu_item.hpp"
#include "i_mnemonic.hpp"

namespace neogfx
{
	class popup_menu;

	class menu_item_widget : public widget, protected i_mnemonic
	{
	public:
		menu_item_widget(i_menu& aMenu, i_menu_item& aMenuItem);
		menu_item_widget(i_widget& aParent, i_menu& aMenu, i_menu_item& aMenuItem);
		menu_item_widget(i_layout& aLayout, i_menu& aMenu, i_menu_item& aMenuItem);
		~menu_item_widget();
	public:
		i_menu_item& menu_item() const;
	public:
		virtual neogfx::size_policy size_policy() const;
		virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
	public:
		virtual void paint_non_client(graphics_context& aGraphicsContext) const;
		virtual void paint(graphics_context& aGraphicsContext) const;
	public:
		virtual void mouse_entered();
		virtual void mouse_left();
		virtual void mouse_button_pressed(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers);
		virtual void mouse_button_released(mouse_button aButton, const point& aPosition);
		virtual bool key_pressed(scan_code_e aScanCode, key_code_e aKeyCode, key_modifiers_e aKeyModifiers);
	protected:
		virtual std::string mnemonic() const;
		virtual void mnemonic_execute();
		virtual i_widget& mnemonic_widget();
	public:
		point sub_menu_position() const;
	private:
		void init();
		virtual void handle_clicked();
	private:
		dimension iGap = 9.0;
		dimension iIconSize = 16.0;
		i_menu& iMenu;
		i_menu_item& iMenuItem;
		horizontal_layout iLayout;
		image_widget iIcon;
		text_widget iText;
		horizontal_spacer iSpacer;
		text_widget iShortcutText;
		boost::optional<std::unique_ptr<neolib::callback_timer>> iSubMenuOpener;
		mutable boost::optional<std::pair<colour, texture>> iSubMenuArrow;
	};
}