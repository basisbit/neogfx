// colour.cpp
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
#include <neolib/string_utils.hpp>
#include "colour.hpp"

namespace neogfx
{
	hsv_colour::hsv_colour() :
		iHue(0.0), iSaturation(0.0), iValue(0.0)
	{
	}

	hsv_colour::hsv_colour(double aHue, double aSaturation, double aValue) :
		iHue(aHue), iSaturation(aSaturation), iValue(aValue)
	{
	}

	hsv_colour::hsv_colour(const colour& aColour)
	{
		*this = from_rgb(aColour);
	}

	double hsv_colour::hue() const
	{
		return iHue;
	}

	double hsv_colour::saturation() const
	{
		return iSaturation;
	}

	double hsv_colour::value() const
	{
		return iValue;
	}

	double hsv_colour::brightness() const
	{
		return value();
	}

	void hsv_colour::set_hue(double aHue)
	{
		iHue = aHue;
	}

	void hsv_colour::set_saturation(double aSaturation)
	{
		iSaturation = aSaturation;
	}

	void hsv_colour::set_value(double aValue)
	{
		iValue = aValue;
	}

	void hsv_colour::set_brightness(double aBrightness)
	{
		set_value(aBrightness);
	}

	hsv_colour hsv_colour::with_brightness(double aNewBrightness) const
	{
		return brighter(0.0, aNewBrightness);
	}

	hsv_colour hsv_colour::brighter(double aDelta) const
	{
		return brighter(1.0, aDelta);
	}

	hsv_colour hsv_colour::brighter(double coeffecient, double delta) const
	{
		hsv_colour result = *this;
		result.iValue *= coeffecient;
		result.iValue += delta;
		result.iValue = std::min(std::max(result.iValue, 0.0), 1.0);
		return result;
	}

	colour hsv_colour::to_rgb(double aAlpha) const
	{
		double c = value() * saturation();
		double h2 = hue() / 60.0;
		double x = c * (1.0 - std::abs(std::fmod(h2, 2.0) - 1.0));
		double r, g, b;
		if (hue() == undefined_hue())
			r = g = b = 0.0;
		else if (h2 >= 0.0 && h2 < 1.0)
			r = c, g = x, b = 0.0;
		else if (h2 >= 1.0 && h2 < 2.0)
			r = x, g = c, b = 0.0;
		else if (h2 >= 2.0 && h2 < 3.0)
			r = 0.0, g = c, b = x;
		else if (h2 >= 3.0 && h2 < 4.0)
			r = 0.0, g = x, b = c;
		else if (h2 >= 4.0 && h2 < 5.0)
			r = x, g = 0.0, b = c;
		else if (h2 >= 5.0 && h2 < 6.0)
			r = c, g = 0.0, b = x;
		else
			r = g = b = 0.0;
		double m = value() - c;
		colour result(
			static_cast<colour::component>(std::floor((r + m) * 255.0)),
			static_cast<colour::component>(std::floor((g + m) * 255.0)),
			static_cast<colour::component>(std::floor((b + m) * 255.0)),
			static_cast<colour::component>(std::floor(aAlpha * 255.0)));
		return result;
	}

	hsv_colour hsv_colour::from_rgb(const colour& aColour)
	{
		double hue, saturation, value;
		double r = aColour.red() / 255.0, g = aColour.green() / 255.0, b = aColour.blue() / 255.0;
		double M = std::max(std::max(r, g), b);
		double m = std::min(std::min(r, g), b);
		double c = M - m;
		double h2;
		if (c == 0.0)
			h2 = undefined_hue();
		else if (M == r)
			h2 = std::fmod((g - b) / c, 6.0);
		else if (M == g)
			h2 = (b - r) / c + 2.0;
		else if (M == b)
			h2 = (r - g) / c + 4.0;
		else
			h2 = undefined_hue();
		if (h2 != undefined_hue())
		{
			hue = 60.0 * h2;
			if (hue < 0.0)
				hue += 360.0;
		}
		else
			hue = undefined_hue();
		value = M;
		value = std::max(std::min(value, 1.0), 0.0);
		if (c == 0.0)
			saturation = 0.0;
		else
			saturation = c / value;
		saturation = std::max(std::min(saturation, 1.0), 0.0);
		return hsv_colour(hue, saturation, value);
	}

	double hsv_colour::undefined_hue()
	{
		return -std::numeric_limits<double>::max();
	}
}