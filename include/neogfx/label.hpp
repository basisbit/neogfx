// label.hpp
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
#include "grid_layout.hpp"
#include "text_widget.hpp"
#include "image_widget.hpp"

namespace neogfx
{
	enum class label_placement
	{
		TextHorizontal,
		TextVertical,
		ImageHorizontal,
		ImageVertical,
		TextImageHorizontal,
		TextImageVertical,
		ImageTextHorizontal,
		ImageTextVertical,
	};

	class label : public widget
	{
	public:
		struct no_buddy : std::logic_error { no_buddy() : std::logic_error("neogfx::label::no_buddy") {} };
	public:
		label(const std::string& aText = std::string(), bool aMultiLine = false, alignment aAlignment = alignment::Left | alignment::VCentre, label_placement aPlacement = label_placement::ImageTextHorizontal);
		label(i_widget& aParent, const std::string& aText = std::string(), bool aMultiLine = false, alignment aAlignment = alignment::Left | alignment::VCentre, label_placement aPlacement = label_placement::ImageTextHorizontal);
		label(i_layout& aLayout, const std::string& aText = std::string(), bool aMultiLine = false, alignment aAlignment = alignment::Left | alignment::VCentre, label_placement aPlacement = label_placement::ImageTextHorizontal);
	public:
		virtual neogfx::size_policy size_policy() const;
		using widget::set_size_policy;
		virtual void set_size_policy(const optional_size_policy& aSizePolicy, bool aUpdateLayout = true);
	public:
		label_placement placement() const;
		void set_placement(label_placement aPlacement);
		const image_widget& image() const;
		image_widget& image();
		const text_widget& text() const;
		text_widget& text();
		bool has_buddy() const;
		i_widget& buddy() const;
		void set_buddy(i_widget& aBuddy);
		void set_buddy(std::shared_ptr<i_widget> aBuddy);
		void unset_buddy();
	private:
		void init();
		label_placement effective_placement() const;
		void handle_placement_change();
	private:
		alignment iAlignment;
		label_placement iPlacement;
		grid_layout iLayout;
		image_widget iImage;
		text_widget iText;
		std::shared_ptr<i_widget> iBuddy;
	};
}