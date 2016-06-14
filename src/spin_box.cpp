// spin_box.cpp
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
#include "spin_box.hpp"
#include "app.hpp"

namespace neogfx
{
	spin_box_impl::spin_box_impl() :
		iNormalizedValue{ 0.0 },
		iPrimaryLayout{ *this },
		iTextBox{ iPrimaryLayout },
		iSecondaryLayout{ iPrimaryLayout },
		iStepUpButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox },
		iStepDownButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox }
	{
		init();
	}

	spin_box_impl::spin_box_impl(i_widget& aParent) :
		framed_widget(aParent),
		iNormalizedValue{ 0.0 },
		iPrimaryLayout{ *this },
		iTextBox{ iPrimaryLayout },
		iSecondaryLayout{ iPrimaryLayout },
		iStepUpButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox },
		iStepDownButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox }
	{
		init();
	}

	spin_box_impl::spin_box_impl(i_layout& aLayout) :
		framed_widget(aLayout),
		iNormalizedValue{ 0.0 },
		iPrimaryLayout{ *this },
		iTextBox{ iPrimaryLayout },
		iSecondaryLayout{ iPrimaryLayout },
		iStepUpButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox },
		iStepDownButton{ iSecondaryLayout, std::string{}, push_button::ButtonStyleSpinBox }
	{
		init();
	}

	spin_box_impl::~spin_box_impl()
	{
		app::instance().current_style_changed.unsubscribe(this);
	}

	colour spin_box_impl::frame_colour() const
	{
		if (app::instance().current_style().colour().similar_intensity(background_colour(), 0.03125))
			return framed_widget::frame_colour();
		return app::instance().current_style().colour().mid(background_colour());
	}

	line_edit& spin_box_impl::text_box()
	{
		return iTextBox;
	}

	void spin_box_impl::set_normalized_value(double aValue, bool aUpdateTextBox)
	{
		aValue = std::max(0.0, std::min(1.0, aValue));
		if (iNormalizedValue != aValue)
		{
			iNormalizedValue = aValue;
			if (aUpdateTextBox)
				iTextBox.set_text(value_to_string());
		}
	}

	void spin_box_impl::init()
	{
		set_margins(neogfx::margins{});
		iPrimaryLayout.set_margins(neogfx::margins{});
		iSecondaryLayout.set_margins(neogfx::margins{});
		iSecondaryLayout.set_spacing(size{});
		iStepUpButton.set_margins(neogfx::margins{});
		iStepUpButton.set_minimum_size(size{15, 8});
		iStepUpButton.set_size_policy(neogfx::size_policy{ neogfx::size_policy::Minimum, neogfx::size_policy::Expanding });
		iStepDownButton.set_margins(neogfx::margins{});
		iStepDownButton.set_minimum_size(size{15, 8});
		iStepDownButton.set_size_policy(neogfx::size_policy{ neogfx::size_policy::Minimum, neogfx::size_policy::Expanding });
		iTextBox.set_style(framed_widget::NoFrame);

		iTextBox.text_changed([this]()
		{
			auto text = iTextBox.text();
			auto newNormalizedValue = string_to_normalized_value(text);
			if (newNormalizedValue)
			{
				if (*newNormalizedValue < 0.0)
					set_normalized_value(0.0);
				else if (*newNormalizedValue > 1.0)
					set_normalized_value(1.0);
				else
					set_normalized_value(*newNormalizedValue);
			}
			else if (!text.empty() && (text != "+" && text != "-" && text.back() != '+' && text.back() != '-' && text.back() != 'e' && text.back() != 'E'))
				iTextBox.set_text("");
		});

		auto step_up = [this]()
		{
			set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() + normalized_step_value())), true);
			iStepper.emplace(app::instance(), [this](neolib::callback_timer& aTimer)
			{
				aTimer.set_duration(125, true);
				aTimer.again();
				set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() + normalized_step_value())), true);
			}, 500);
		};
		iStepUpButton.pressed(step_up);
		iStepUpButton.clicked([this]()
		{
			if (iStepper == boost::none) // key press?
				set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() + normalized_step_value())), true);
		});
		iStepUpButton.double_clicked(step_up);
		iStepUpButton.released([this]()
		{
			iStepper = boost::none;
		});

		auto step_down = [this]()
		{
			set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() - normalized_step_value())), true);
			iStepper.emplace(app::instance(), [this](neolib::callback_timer& aTimer)
			{
				aTimer.set_duration(125, true);
				aTimer.again();
				set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() - normalized_step_value())), true);
			}, 500);
		};
		iStepDownButton.pressed(step_down);
		iStepDownButton.clicked([this]()
		{
			if (iStepper == boost::none) // key press?
				set_normalized_value(std::max(0.0, std::min(1.0, normalized_value() - normalized_step_value())), true);
		});
		iStepDownButton.double_clicked(step_down);
		iStepDownButton.released([this]()
		{
			iStepper = boost::none;
		});

		update_arrows();
		app::instance().current_style_changed([this]()
		{
			update_arrows();
		}, this);
	}

	void spin_box_impl::update_arrows()
	{
		auto ink = app::instance().current_style().text_colour();
		if (iUpArrow == boost::none || iUpArrow->first != ink)
		{
			const uint8_t sUpArrowImagePattern[5][9]
			{
				{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 1, 1, 1, 1, 1, 0, 0 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			};
			iUpArrow = std::make_pair(ink, image{ "neogfx::spin_box_impl::iUpArrow::" + ink.to_string(), sUpArrowImagePattern,{ { 0, colour{} },{ 1, ink } } });
		}
		if (iDownArrow == boost::none || iDownArrow->first != ink)
		{
			const uint8_t sDownArrowImagePattern[5][9]
			{
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 0, 1, 1, 1, 1, 1, 1, 1, 0 },
				{ 0, 0, 1, 1, 1, 1, 1, 0, 0 },
				{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
			};
			iDownArrow = std::make_pair(ink, image{ "neogfx::spin_box_impl::iDownArrow::" + ink.to_string(), sDownArrowImagePattern,{ { 0, colour{} },{ 1, ink } } });
		}
		iStepUpButton.label().set_placement(label_placement::ImageHorizontal);
		iStepDownButton.label().set_placement(label_placement::ImageHorizontal);
		iStepUpButton.image().set_image(iUpArrow->second);
		iStepDownButton.image().set_image(iDownArrow->second);
	}
}

