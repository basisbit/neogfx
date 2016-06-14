// text_widget.hpp
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

namespace neogfx
{
	class text_widget : public widget
	{
	public:
		event<> text_changed;
	public:
		text_widget(const std::string& aText = std::string(), bool aMultiLine = false);
		text_widget(i_widget& aParent, const std::string& aText = std::string(), bool aMultiLine = false);
		text_widget(i_layout& aLayout, const std::string& aText = std::string(), bool aMultiLine = false);
	public:
		virtual neogfx::size_policy size_policy() const;
		virtual size minimum_size(const optional_size& aAvailableSpace = optional_size()) const;
	public:
		virtual void paint(graphics_context& aGraphicsContext) const;
	public:
		virtual void set_font(const optional_font& aFont);
	public:
		const std::string& text() const;
		void set_text(const std::string& aText);
		bool multi_line() const;
		neogfx::alignment alignment() const;
		void set_alignment(neogfx::alignment aAlignment, bool aUpdateLayout = true);
		bool has_text_colour() const;
		colour text_colour() const;
		void set_text_colour(const optional_colour& aTextColour);
	protected:
		size text_extent() const;
	private:
		std::string iText;
		mutable glyph_text iGlyphTextCache;
		mutable optional_size iTextExtent;
		bool iMultiLine;
		neogfx::alignment iAlignment;
		optional_colour iTextColour;
	};
}