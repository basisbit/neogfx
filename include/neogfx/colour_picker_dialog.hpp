// colour_picker_dialog.hpp
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
#include "dialog.hpp"
#include "label.hpp"
#include "radio_button.hpp"
#include "spin_box.hpp"

namespace neogfx
{
	class colour_picker_dialog : public dialog
	{
	public:
		enum mode_e
		{
			ModeHSV,
			ModeRGB,
			ModeCMYK
		};
	private:
		class colour_box : public framed_widget
		{
		public:
			colour_box(colour_picker_dialog& aParent, const colour& aColour);
		public:
			virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
			virtual size maximum_size(const optional_size& aAvailableSpace = optional_size()) const;
		public:
			virtual void paint(graphics_context& aGraphicsContext) const;
		private:
			colour_picker_dialog& iParent;
			colour iColour;
		};
		class x_picker : public framed_widget
		{
		public:
			x_picker(colour_picker_dialog& aParent);
		public:
			virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
			virtual size maximum_size(const optional_size& aAvailableSpace = optional_size()) const;
		public:
			virtual void paint(graphics_context& aGraphicsContext) const;
		private:
			colour_picker_dialog& iParent;
		};
		class yz_picker : public framed_widget
		{
		public:
			yz_picker(colour_picker_dialog& aParent);
		public:
			virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
			virtual size maximum_size(const optional_size& aAvailableSpace = optional_size()) const;
		public:
			virtual void paint(graphics_context& aGraphicsContext) const;
		private:
			colour_picker_dialog& iParent;
		};
		class colour_selection : public framed_widget
		{
		public:
			colour_selection(colour_picker_dialog& aParent);
		public:
			virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
			virtual size maximum_size(const optional_size& aAvailableSpace = optional_size()) const;
		public:
			virtual void paint(graphics_context& aGraphicsContext) const;
		private:
			colour_picker_dialog& iParent;
		};
	public:
		colour_picker_dialog();
		colour_picker_dialog(i_widget& aParent);
		~colour_picker_dialog();
	public:
		mode_e mode() const;
		void set_mode(mode_e aMode);
		colour current_colour() const;
		colour selected_colour() const;
	private:
		void init();
	private:
		mode_e iMode;
		colour iCurrentColour;
		colour iSelectedColour;
		vertical_layout iLayout;
		horizontal_layout iLayout2;
		vertical_layout iLeftLayout;
		vertical_layout iRightLayout;
		horizontal_layout iRightTopLayout;
		horizontal_layout iRightBottomLayout;
		colour_selection iColourSelection;
		grid_layout iChannelLayout;
		label iBasicColoursLabel;
		grid_layout iBasicColoursLayout;
		vertical_spacer iSpacer;
		label iCustomColoursLabel;
		grid_layout iCustomColoursLayout;
		yz_picker iYZPicker;
		x_picker iXPicker;
		std::pair<radio_button, spin_box> iH;
		std::pair<radio_button, spin_box> iS;
		std::pair<radio_button, spin_box> iV;
		std::pair<radio_button, spin_box> iR;
		std::pair<radio_button, spin_box> iG;
		std::pair<radio_button, spin_box> iB;
		std::pair<radio_button, spin_box> iA;
		std::pair<label, line_edit> iRgb;
		push_button iAddToCustomColours;
	};
}