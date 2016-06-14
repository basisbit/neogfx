// cursor.hpp
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
#include <neolib/variant.hpp>
#include "event.hpp"
#include "geometry.hpp"
#include "colour.hpp"

namespace neogfx
{
	class i_document;

	class cursor
	{
	public:
		event<> position_changed;
		event<> anchor_changed;
		event<> appearance_changed;
	public:
		enum move_operation_e
		{
			None,
			StartOfDocument,
			StartOfParagraph,
			StartOfLine,
			StartOfWord,
			EndOfDocument,
			EndOfParagraph,
			EndOfLine,
			EndOfWord,
			PreviousParagraph, 
			PreviousLine,
			PreviousWord,
			PreviousCharacter,
			NextParagraph,
			NextLine,
			NextWord,
			NextCharacter,
			Up,
			Down,
			Left,
			Right
		};
		typedef std::size_t position_type;
		typedef neolib::variant<neogfx::colour, neogfx::gradient> colour_type;
	public:
		struct no_document : std::logic_error { no_document() : std::logic_error("neogfx::cursor::no_document") {} };
	public:
		cursor();
		cursor(i_document& aDocument);
	public:
		bool has_document() const;
		i_document& document() const;
		void move(move_operation_e aMoveOperation);
		position_type position() const;
		void set_position(position_type aPosition, bool aMoveAnchor = true);
		position_type anchor() const;
		void set_anchor(position_type aAnchor);
		const colour_type& colour() const;
		void set_colour(const colour_type& aColour);
		dimension width() const;
		void set_width(dimension aWidth);
	private:
		i_document* iDocument;
		position_type iPosition;
		position_type iAnchor;
		colour_type iColour;
		dimension iWidth;
	};
}