// i_rendering_engine.hpp
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
#include "window.hpp"
#include "i_native_window.hpp"
#include "i_font_manager.hpp"
#include "i_texture_manager.hpp"

namespace neogfx
{
	class i_surface_manager;
	class i_native_window_event_handler;

	class i_screen_metrics : public i_device_metrics
	{
	public:
		enum subpixel_format_e
		{
			SubpixelFormatUnknown,
			SubpixelFormatRGBHorizontal,
			SubpixelFormatBGRHorizontal,
			SubpixelFormatRGBVertical,
			SubpixelFormatBGRVertical
		};
	public:
		virtual subpixel_format_e subpixel_format() const = 0;
	};

	class i_rendering_engine
	{
	public:
		class i_shader_program
		{
		public:
			struct variable_not_found : std::logic_error { variable_not_found() : std::logic_error("neogfx::i_rendering_engine::i_shader_program::variable_not_found") {} };
		public:
			virtual void* handle() const = 0;
			virtual void* variable(const std::string& aVariableName) const = 0;
			virtual void set_uniform_variable(const std::string& aName, double aValue) = 0;
			virtual void set_uniform_variable(const std::string& aName, int aValue) = 0;
			virtual void set_uniform_variable(const std::string& aName, double aValue1, double aValue2) = 0;
		};
	public:
		virtual ~i_rendering_engine() {}
	public:
		struct failed_to_initialize : std::runtime_error { failed_to_initialize() : std::runtime_error("neogfx::i_rendering_engine::failed_to_initialize") {} };
		struct context_exists : std::logic_error { context_exists() : std::logic_error("neogfx::i_rendering_engine::context_exists") {} };
		struct context_not_found : std::logic_error { context_not_found() : std::logic_error("neogfx::i_rendering_engine::context_not_found") {} };
		struct failed_to_create_shader_program : std::runtime_error { failed_to_create_shader_program(const std::string& aReason) : std::runtime_error("neogfx::i_rendering_engine::failed_to_create_shader_program: " + aReason) {} };
		struct no_shader_program_active : std::logic_error { no_shader_program_active() : std::logic_error("neogfx::i_rendering_engine::no_shader_program_active") {} };
		struct shader_program_not_found : std::logic_error { shader_program_not_found() : std::logic_error("neogfx::i_rendering_engine::shader_program_not_found") {} };
		struct shader_program_error : std::runtime_error { shader_program_error(const std::string& aError) : std::runtime_error("neogfx::i_rendering_engine::shader_program_error: " + aError) {} };
	public:
		virtual void initialize() = 0;
		virtual void* create_context(i_native_surface& aSurface) = 0; 
		virtual void destroy_context(i_native_surface& aSurface) = 0;
		virtual const i_screen_metrics& screen_metrics() const = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const video_mode& aVideoMode, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const video_mode& aVideoMode, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual std::unique_ptr<i_native_window> create_window(i_surface_manager& aSurfaceManager, i_native_window_event_handler& aEventHandler, i_native_surface& aParent, const point& aPosition, const size& aDimensions, const std::string& aWindowTitle, window::style_e aStyle = window::Default) = 0;
		virtual bool creating_window() const = 0;
		virtual i_font_manager& font_manager() = 0;
		virtual i_texture_manager& texture_manager() = 0;
		virtual void activate_shader_program(i_shader_program& aProgram) = 0;
		virtual void deactivate_shader_program() = 0;
		virtual const i_shader_program& active_shader_program() const = 0;
		virtual i_shader_program& active_shader_program() = 0;
		virtual const i_shader_program& monochrome_shader_program() const = 0;
		virtual i_shader_program& monochrome_shader_program() = 0;
		virtual const i_shader_program& subpixel_shader_program() const = 0;
		virtual i_shader_program& subpixel_shader_program() = 0;
		virtual void render_now() = 0;
	public:
		virtual bool process_events() = 0;
	};
}