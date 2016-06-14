// button.hpp
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
#include "label.hpp"
#include "horizontal_layout.hpp"
#include "event.hpp"
#include "i_mnemonic.hpp"

namespace neogfx
{
	class button : public widget, protected i_mnemonic
	{
	public:
		event<> pressed;
		event<> clicked;
		event<> double_clicked;
		event<> released;
	public:
		event<> checked;
		event<> unchecked;
		event<> indeterminate;
	public:
		enum checkable_e
		{
			NotCheckable,
			BiState,
			TriState
		};
	public:
		struct not_tri_state_checkable : public std::logic_error { not_tri_state_checkable() : std::logic_error("neogfx::button::not_tri_state_checkable") {} };
	public:
		button(const std::string& aText = std::string(), alignment aAlignment = alignment::Left | alignment::VCentre);
		button(i_widget& aParent, const std::string& aText = std::string(), alignment aAlignment = alignment::Left | alignment::VCentre);
		button(i_layout& aLayout, const std::string& aText = std::string(), alignment aAlignment = alignment::Left | alignment::VCentre);
		~button();
	public:
		virtual neogfx::size_policy size_policy() const;
		virtual neogfx::margins margins() const;
	public:
		checkable_e checkable() const;
		void set_checkable(checkable_e aCheckable = BiState);
		bool is_checked() const;
		bool is_unchecked() const;
		bool is_indeterminate() const;
		void check();
		void uncheck();
		void set_indeterminate();
		void set_checked(bool aChecked);
		void toggle();
	public:
		const neogfx::label& label() const;
		neogfx::label& label();
		const image_widget& image() const;
		image_widget& image();
		const text_widget& text() const;
		text_widget& text();
	protected:
		virtual void mouse_button_pressed(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers);
		virtual void mouse_button_double_clicked(mouse_button aButton, const point& aPosition, key_modifiers_e aKeyModifiers);
		virtual void mouse_button_released(mouse_button aButton, const point& aPosition);
	protected:
		virtual bool key_pressed(scan_code_e aScanCode, key_code_e aKeyCode, key_modifiers_e aKeyModifiers);
	protected:
		virtual void handle_clicked();
	protected:
		virtual const boost::optional<bool>& checked_state() const;
		virtual bool set_checked_state(const boost::optional<bool>& aCheckedState);
	protected:
		virtual std::string mnemonic() const;
		virtual void mnemonic_execute();
		virtual i_widget& mnemonic_widget();
	private:
		void init();
	private:
		checkable_e iCheckable;
		boost::optional<bool> iCheckedState;
		horizontal_layout iLayout;
		neogfx::label iLabel;
	};
}