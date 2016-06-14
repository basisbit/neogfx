// slider.inl
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

#include "slider.hpp"

namespace neogfx
{
	template <typename T>
	basic_slider<T>::basic_slider(type_e aType) :
		slider_impl(aType), iMinimum{}, iMaximum{}, iStep{}, iValue{}, iSettingNormalizedValue{ false }
	{
	}

	template <typename T>
	basic_slider<T>::basic_slider(i_widget& aParent, type_e aType) :
		slider_impl(aParent, aType), iMinimum{}, iMaximum{}, iStep{}, iValue{}, iSettingNormalizedValue{ false }
	{
	}

	template <typename T>
	basic_slider<T>::basic_slider(i_layout& aLayout, type_e aType) :
		slider_impl(aLayout, aType), iMinimum{}, iMaximum{}, iStep{}, iValue{}, iSettingNormalizedValue{ false }
	{
	}

	template <typename T>
	typename basic_slider<T>::value_type basic_slider<T>::minimum() const
	{
		return iMinimum;
	}

	template <typename T>
	void basic_slider<T>::set_minimum(value_type aMinimum)
	{
		iMinimum = aMinimum;
		constraints_changed.trigger();
		if (iValue < minimum())
			set_value(minimum());
	}

	template <typename T>
	typename basic_slider<T>::value_type basic_slider<T>::maximum() const
	{
		return iMaximum;
	}

	template <typename T>
	void basic_slider<T>::set_maximum(value_type aMaximum)
	{
		iMaximum = aMaximum;
		constraints_changed.trigger();
		if (iValue > maximum())
			set_value(maximum());
	}

	template <typename T>
	typename basic_slider<T>::value_type basic_slider<T>::step() const
	{
		return iStep;
	}

	template <typename T>
	void basic_slider<T>::set_step(value_type aStep)
	{
		iStep = aStep;
		constraints_changed.trigger();
	}

	template <typename T>
	typename basic_slider<T>::value_type basic_slider<T>::value() const
	{
		return iValue;
	}

	template <typename T>
	void basic_slider<T>::set_value(value_type aValue)
	{
		if (iValue != aValue)
		{
			iValue = aValue;
			if (!iSettingNormalizedValue)
				slider_impl::set_normalized_value(normalized_value());
			value_changed.trigger();
		}
	}

	template <typename T>
	double basic_slider<T>::normalized_step_value() const
	{
		auto range = maximum() - minimum();
		if (range == 0)
			return 1.0;
		return static_cast<double>(step()) / range;
	}

	template <typename T>
	double basic_slider<T>::normalized_value() const
	{
		auto range = maximum() - minimum();
		if (range == 0)
			return 1.0;
		return (static_cast<double>(value()) - minimum()) / range;
	}

	template <typename T>
	void basic_slider<T>::set_normalized_value(double aValue)
	{
		aValue = std::max(0.0, std::min(1.0, aValue));
		iSettingNormalizedValue = true;
		auto range = maximum() - minimum();
		auto denormalized = range * aValue + minimum();
		if (std::is_integral<value_type>())
		{
			if (denormalized < 0.0)
				denormalized = std::floor(denormalized + 0.5);
			else if (denormalized > 0.0)
				denormalized = std::ceil(denormalized - 0.5);
		}
		set_value(static_cast<value_type>(denormalized));
		slider_impl::set_normalized_value(aValue);
		iSettingNormalizedValue = false;
	}
}
