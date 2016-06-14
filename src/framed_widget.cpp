// framed_widget.cpp
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
#include "framed_widget.hpp"

namespace neogfx
{
	framed_widget::framed_widget(style_e aStyle, dimension aLineWidth) : 
		iStyle(aStyle), iLineWidth(aLineWidth)
	{
	}

	framed_widget::framed_widget(i_widget& aParent, style_e aStyle, dimension aLineWidth) :
		widget(aParent), iStyle(aStyle), iLineWidth(aLineWidth)
	{
	}

	framed_widget::framed_widget(i_layout& aLayout, style_e aStyle, dimension aLineWidth) :
		widget(aLayout), iStyle(aStyle), iLineWidth(aLineWidth)
	{
	}

	framed_widget::~framed_widget()
	{
	}

	rect framed_widget::client_rect(bool aIncludeMargins) const
	{
		rect cr = widget::client_rect(aIncludeMargins);
		cr.x += effective_frame_width();
		cr.y += effective_frame_width();
		cr.cx -= effective_frame_width() * 2.0;
		cr.cy -= effective_frame_width() * 2.0;
		return cr;
	}

	size framed_widget::minimum_size(const optional_size& aAvailableSpace) const
	{
		size result = widget::minimum_size(aAvailableSpace);
		if (!has_minimum_size())
			result += size{ effective_frame_width() * 2.0 };
		return result;
	}

	size framed_widget::maximum_size(const optional_size& aAvailableSpace) const
	{
		size result = widget::maximum_size(aAvailableSpace);
		if (!has_maximum_size())
		{
			if (result.cx != std::numeric_limits<size::dimension_type>::max())
				result.cx += effective_frame_width() * 2.0;
			if (result.cy != std::numeric_limits<size::dimension_type>::max())
				result.cy += effective_frame_width() * 2.0;
		}
		return result;
	}

	bool framed_widget::transparent_background() const
	{
		return false;
	}

	void framed_widget::paint_non_client(graphics_context& aGraphicsContext) const
	{
		colour frameColour = frame_colour();
		widget::paint_non_client(aGraphicsContext);
		switch (iStyle)
		{
		case NoFrame:
		case HiddenFrame:
		default:
			break;
		case DottedFrame:
			break;
		case DashedFrame:
			break;
		case SolidFrame:
			aGraphicsContext.draw_rect(rect(point(0.0, 0.0), window_rect().extents()), pen(frameColour, effective_frame_width()));
			break;
		case ContainerFrame:
			{
				colour midColour = (has_foreground_colour() ? foreground_colour() : container_background_colour());
				colour borderColour = midColour.darker(0x40);
				colour innerBorderColour = midColour.lighter(0x40);
				rect rectBorder = rect(point(0.0, 0.0), window_rect().extents());
				rectBorder.deflate(line_width(), line_width());
				aGraphicsContext.draw_rect(rectBorder, pen(innerBorderColour, line_width()));
				rectBorder.inflate(line_width(), line_width());
				aGraphicsContext.draw_rect(rectBorder, pen(borderColour, line_width()));
			}
			break;
		case DoubleFrame:
			break;
		case GrooveFrame:
			break;
		case RidgeFrame:
			break;
		case InsetFrame:
			break;
		case OutsetFrame:
			break;
		}
	}

	void framed_widget::paint(graphics_context& aGraphicsContext) const
	{
		widget::paint(aGraphicsContext);
	}

	void framed_widget::set_style(style_e aStyle)
	{
		if (iStyle != aStyle)
		{
			iStyle = aStyle;
			if (has_managing_layout())
				managing_layout().layout_items(true);
		}
	}

	colour framed_widget::frame_colour() const
	{
		return (background_colour().dark() ? background_colour().lighter(0x60) : background_colour().darker(0x60));
	}

	dimension framed_widget::line_width() const
	{
		return units_converter(*this).from_device_units(iLineWidth);
	}

	dimension framed_widget::effective_frame_width() const
	{
		switch (iStyle)
		{
		case NoFrame:
		default:
			return 0.0;
		case DottedFrame:
		case DashedFrame:
		case SolidFrame:
			return line_width();
		case ContainerFrame:
			return line_width() * 2.0;
		case DoubleFrame:
		case GrooveFrame:
		case RidgeFrame:
			return line_width() * 3.0;
		case InsetFrame:
		case OutsetFrame:
		case HiddenFrame:
			return line_width();
		}
	}
}