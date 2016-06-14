// sdl_renderer.hpp
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
#include <set>
#include <map>
#include "opengl_renderer.hpp"
#include "i_basic_services.hpp"
#include "keyboard.hpp"

namespace neogfx
{
	class i_native_surface;

	class sdl_renderer : public opengl_renderer
	{
	public:
		sdl_renderer(i_basic_services& aBasicServices, i_keyboard& aKeyboard);
		~sdl_renderer();
	public:
		virtual void* create_context(i_native_surface& aSurface);
		virtual void destroy_context(i_native_surface& aSurface);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const video_mode& aVideoMode, const std::string& aWindowTitle, window::style_e aStyle);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const video_mode& aVideoMode, const std::string& aWindowTitle, window::style_e aStyle);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle);
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle);
		virtual bool creating_window() const;
		virtual void render_now();
	public:
		virtual bool process_events();
	private:
		i_basic_services& iBasicServices;
		i_keyboard& iKeyboard;
		std::map<i_native_surface*, void*> iContexts;
		uint32_t iCreatingWindow;
	};
}