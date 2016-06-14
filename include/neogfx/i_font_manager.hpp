// i_font_manager.hpp
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
#include "geometry.hpp"
#include "font.hpp"
#include "i_font_texture.hpp"

namespace neogfx
{
	class i_native_font;
	class i_native_font_face;

	class i_font_manager
	{
	public:
		virtual const font_info& default_system_font_info() const = 0;
		virtual const font_info& default_fallback_font_info() const = 0;
		virtual std::unique_ptr<i_native_font_face> create_default_font(const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> create_fallback_font(const i_native_font_face& aExistingFont) = 0;
		virtual std::unique_ptr<i_native_font_face> create_font(const std::string& aFamilyName, font::style_e aStyle, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> create_font(const std::string& aFamilyName, const std::string& aStyleName, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> create_font(const font_info& aInfo, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> create_font(i_native_font& aFont, font::style_e aStyle, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> create_font(i_native_font& aFont, const std::string& aStyleName, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual bool is_font_file(const std::string& aFileName) const = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_file(const std::string& aFileName, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_file(const std::string& aFileName, font::style_e aStyle, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_file(const std::string& aFileName, const std::string& aStyleName, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_memory(const void* aData, std::size_t aSizeInBytes, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_memory(const void* aData, std::size_t aSizeInBytes, font::style_e aStyle, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual std::unique_ptr<i_native_font_face> load_font_from_memory(const void* aData, std::size_t aSizeInBytes, const std::string& aStyleName, font::point_size aSize, const i_device_resolution& aDevice) = 0;
		virtual i_font_texture& allocate_glyph_space(const size& aSize, rect& aResult) = 0;
	};
}