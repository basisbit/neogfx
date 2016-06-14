// text_widget.cpp
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

#include "neogfx.hpp"
#include "app.hpp"
#include "text_widget.hpp"
#include "graphics_context.hpp"

namespace neogfx
{
	text_widget::text_widget(const std::string& aText, bool aMultiLine) : 
		widget(), iText(aText), iGlyphTextCache(font()), iMultiLine(aMultiLine), iAlignment(neogfx::alignment::Centre | neogfx::alignment::VCentre)
	{
		set_margins(neogfx::margins(0.0));
		set_ignore_mouse_events(true);
	}

	text_widget::text_widget(i_widget& aParent, const std::string& aText, bool aMultiLine) :
		widget(aParent), iText(aText), iGlyphTextCache(font()), iMultiLine(aMultiLine), iAlignment(neogfx::alignment::Centre | neogfx::alignment::VCentre)
	{
		set_margins(neogfx::margins(0.0));
		set_ignore_mouse_events(true);
	}

	text_widget::text_widget(i_layout& aLayout, const std::string& aText, bool aMultiLine) :
		widget(aLayout), iText(aText), iGlyphTextCache(font()), iMultiLine(aMultiLine), iAlignment(neogfx::alignment::Centre | neogfx::alignment::VCentre)
	{
		set_margins(neogfx::margins(0.0));
		set_ignore_mouse_events(true);
	}

	neogfx::size_policy text_widget::size_policy() const
	{
		if (widget::has_size_policy())
			return widget::size_policy();
		return neogfx::size_policy::Minimum;
	}

	size text_widget::minimum_size(const optional_size& aAvailableSpace) const
	{
		if (widget::has_minimum_size())
			return widget::minimum_size(aAvailableSpace);
		else
		{
			size result = units_converter(*this).to_device_units(text_extent() + margins().size());
			result.cx = std::ceil(result.cx);
			result.cy = std::ceil(result.cy);
			return units_converter(*this).from_device_units(result);
		}
	}

	void text_widget::paint(graphics_context& aGraphicsContext) const
	{
		scoped_mnemonics sm(aGraphicsContext, app::instance().keyboard().is_key_pressed(ScanCode_LALT) || app::instance().keyboard().is_key_pressed(ScanCode_RALT));
		if (iGlyphTextCache.font() != font())
		{
			iTextExtent = boost::none;
			iGlyphTextCache = glyph_text(font());
		}
		aGraphicsContext.set_glyph_text_cache(iGlyphTextCache);
		size textSize = text_extent();
		point textPosition;
		switch (iAlignment & neogfx::alignment::Horizontal)
		{
		case neogfx::alignment::Left:
		case neogfx::alignment::Justify:
			textPosition.x = 0.0;
			break;
		case neogfx::alignment::Centre:
			textPosition.x = std::floor((client_rect().width() - textSize.cx) / 2.0);
			break;
		case neogfx::alignment::Right:
			textPosition.x = std::floor((client_rect().width() - textSize.cx));
			break;
		}
		switch (iAlignment & neogfx::alignment::Vertical)
		{
		case neogfx::alignment::Top:
			textPosition.y = 0.0;
			break;
		case neogfx::alignment::VCentre:
			textPosition.y = std::floor((client_rect().height() - textSize.cy) / 2.0);
			break;
		case neogfx::alignment::Bottom:
			textPosition.y = std::floor((client_rect().height() - textSize.cy));
			break;
		}
		colour ink = text_colour();
		if (effectively_disabled())
		{
			aGraphicsContext.set_monochrome(true);
			ink.set_alpha(ink.alpha() / 2);
		}
		if (multi_line())
			aGraphicsContext.draw_multiline_text(textPosition, text(), font(), textSize.cx, ink, alignment::Centre, true);
		else
			aGraphicsContext.draw_text(textPosition, text(), font(), ink, true);
		aGraphicsContext.set_monochrome(false);
	}

	void text_widget::set_font(const optional_font& aFont)
	{
		widget::set_font(aFont);
		iTextExtent = boost::none;
		iGlyphTextCache = glyph_text(font());
	}

	const std::string& text_widget::text() const
	{
		return iText;
	}

	void text_widget::set_text(const std::string& aText)
	{
		if (iText != aText)
		{
			size oldSize = minimum_size();
			iText = aText;
			iTextExtent = boost::none;
			iGlyphTextCache = glyph_text(font());
			text_changed.trigger();
			if (oldSize != minimum_size() && has_managing_layout())
				managing_layout().layout_items(true);
			update();
		}
	}

	bool text_widget::multi_line() const
	{
		return iMultiLine;
	}

	neogfx::alignment text_widget::alignment() const
	{
		return iAlignment;
	}

	void text_widget::set_alignment(neogfx::alignment aAlignment, bool aUpdateLayout)
	{
		if (iAlignment != aAlignment)
		{
			iAlignment = aAlignment;
			if (aUpdateLayout)
				ultimate_ancestor().layout_items(true);
		}
	}

	bool text_widget::has_text_colour() const
	{
		return iTextColour != boost::none;
	}

	colour text_widget::text_colour() const
	{
		if (has_text_colour())
			return *iTextColour;
		optional_colour textColour;
		const i_widget* w = 0;
		do
		{
			if (w == 0)
				w = this;
			else
				w = &w->parent();
			if (w->has_background_colour())
			{
				textColour = w->background_colour().to_hsl().lightness() >= 0.5f ? colour::Black : colour::White;
				break; 
			}
			else if (w->has_foreground_colour())
			{
				textColour = w->foreground_colour().to_hsl().lightness() >= 0.5f ? colour::Black : colour::White;
				break;
			}
		} while (w->has_parent());
		colour defaultTextColour = app::instance().current_style().text_colour();
		if (textColour == boost::none || textColour->similar_intensity(defaultTextColour))
			return defaultTextColour;
		else
			return *textColour;
	}

	void text_widget::set_text_colour(const optional_colour& aTextColour)
	{
		iTextColour = aTextColour;
		update();
	}

	size text_widget::text_extent() const
	{
		if (iGlyphTextCache.font() != font())
		{
			iTextExtent = boost::none;
			iGlyphTextCache = glyph_text(font());
		}
		if (iTextExtent != boost::none)
			return *iTextExtent;
		if (!has_surface())
			return size{};
		graphics_context gc(*this);
		scoped_mnemonics sm(gc, app::instance().keyboard().is_key_pressed(ScanCode_LALT) || app::instance().keyboard().is_key_pressed(ScanCode_RALT));
		gc.set_glyph_text_cache(iGlyphTextCache);
		if (iMultiLine)
		{
			if (has_minimum_size() && widget::minimum_size().cx != 0 && widget::minimum_size().cy == 0)
				return *(iTextExtent = gc.multiline_text_extent(iText, font(), widget::minimum_size().cx - margins().size().cx, true));
			else
				return *(iTextExtent = gc.multiline_text_extent(iText, font(), true));
		}
		else
			return *(iTextExtent = gc.text_extent(iText, font(), true));
	}
}