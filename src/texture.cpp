// texture.cpp
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
#include "texture.hpp"
#include "texture_manager.hpp"
#include "i_native_texture.hpp"

namespace neogfx
{
	texture::texture()
	{
	}

	texture::texture(const i_texture& aTexture) :
		iNativeTexture(!aTexture.is_empty() ? aTexture.native_texture() : std::shared_ptr<i_native_texture>())
	{
	}

	texture::texture(const i_image& aImage) :
		iNativeTexture(app::instance().rendering_engine().texture_manager().create_texture(aImage))
	{
	}

	texture::~texture()
	{
	}

	bool texture::is_empty() const
	{
		return iNativeTexture == nullptr;
	}

	size texture::extents() const
	{
		if (is_empty())
			return size{};
		return native_texture()->extents();
	}

	size texture::storage_extents() const
	{
		if (is_empty())
			return size{};
		return native_texture()->storage_extents();
	}

	std::shared_ptr<i_native_texture> texture::native_texture() const
	{
		if (is_empty())
			throw texture_empty();
		return iNativeTexture;
	}
}